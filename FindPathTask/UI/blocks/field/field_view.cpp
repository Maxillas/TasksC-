#include <QWheelEvent>
#include <QMessageBox>
#include <QRandomGenerator>

#include "field_view.h"
#include "../../../Core/field_controller.h"


Field::Field(QGraphicsView *parent):
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this))
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setScene(m_scene);
    this->setFixedSize(750, 550);
    this->show();

    connect(&FieldController::getInstance(), &FieldController::generateField,
            this, &Field::generateField);
    connect(&FieldController::getInstance(), &FieldController::dontFindPath,
            this, &Field::onDontFindPath);
    connect(&FieldController::getInstance(), &FieldController::foundPath,
            this, &Field::onFoundPath);
    connect(&FieldController::getInstance(), &FieldController::cleanField,
            this, &Field::clearLines);
    connect(&FieldController::getInstance(), &FieldController::searchCompleted,
            this, &Field::onSearchCompleted);
}

void Field::wheelEvent(QWheelEvent *event)
{
    QPointF scenePos = mapToScene(event->position().toPoint());
    qreal currentScale = transform().m11();

    if (event->angleDelta().y() > 0) {
        if(transform().m11() >= 30) {return;}
        scale(1.1, 1.1);
    } else {
        if(transform().m11() <= 0.9) {return;}
        scale(0.9, 0.9);

    }

    qreal newScale = transform().m11();

    QPointF delta = scenePos - mapToScene(viewport()->rect().center());
    QPointF offset = delta * (newScale / currentScale - 1);

    centerOn(scenePos - offset);
    event->accept();
}

void Field::mouseMoveEvent(QMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->items(event->pos());

    Cell* newCell = nullptr;
    for (QGraphicsItem* item : items) {
        newCell = dynamic_cast<Cell*>(item);
        if (newCell) {break;}
    }

    if (newCell && newCell != m_currentCell) {
        m_currentCell = newCell;
        FieldController::getInstance().onMouseMove(m_currentCell);
    } else if (!newCell) {
        m_currentCell = nullptr;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Field::generateField(const uint16_t& width, const uint16_t& height)
{
    FieldController::getInstance().clean();
    m_scene->clear();
    this->resetTransform();

    int cellWidth = (viewport()->width() - 2) / width;
    int cellHeight = (viewport()->height() - 2) / height;
    int cellSize = cellWidth <= cellHeight ? cellWidth : cellHeight;

    FieldController::getInstance().initiateGrid(height, width);

    qreal wallProbability = 0.15;

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {

            Cell* cell = new Cell(col * cellSize, row * cellSize, cellSize, cellSize);
            cell->setPen(QPen(Qt::black));
            cell->setBrush(QBrush(Qt::white));
            cell->row = row;
            cell->column = col;

            m_scene->addItem(cell); //сцена управляет жизнью cell => delete не нужен
            FieldController::getInstance().addItemInGrid(row, col, cell);

            if (QRandomGenerator::global()->generateDouble() < wallProbability) {
                cell->setBrush(QBrush(Qt::black));
                FieldController::getInstance().setWall(row, col, true);
            } else {
                cell->setBrush(QBrush(Qt::white));
                FieldController::getInstance().setWall(row, col, false);
            }
        }
    }
    this->setSceneRect(0, 0, width * cellSize, height * cellSize);
    this->centerOn(width * cellSize / 2, height * cellSize / 2);
}

void Field::onDontFindPath()
{
   QMessageBox::warning(nullptr, "Ошибка", "Путь не может быть найден!");
}

void Field::onFoundPath(QVector<Cell *> path)
{
    clearLines();
    Cell* startCell = FieldController::getInstance().getStartCell();
    for (Cell* cell : path) {

        if(cell == startCell && cell) {
            cell->setCellText("A");
            continue;
        }

        if (!cell || !cell->parent || !startCell || !m_scene) {
            return;
        }

        QPointF start = cell->mapToScene(cell->rect().center());
        QPointF end = cell->parent->mapToScene(cell->parent->rect().center());

        if(cell->parent == startCell) {

            ArrowDirection direction = directionCalculation(cell->row, cell->column,
                                                            cell->parent->row, cell->parent->column);

            switch (direction) {
            case ArrowDirection::RIGHT:
                end = cell->parent->mapToScene(cell->parent->rect().center() + QPointF(cell->rect().width() / 4, 0));
                break;

            case ArrowDirection::LEFT:
                end = cell->parent->mapToScene(cell->parent->rect().center() - QPointF(cell->rect().width() / 4, 0));
                break;

            case ArrowDirection::DOWN:
                end = cell->parent->mapToScene(cell->parent->rect().center() + QPointF(0, cell->rect().width() / 4));
                break;

            case ArrowDirection::UP:
                end = cell->parent->mapToScene(cell->parent->rect().center() - QPointF(0, cell->rect().width() / 4));
                break;
            default:
                break;
            }
        }

        QGraphicsLineItem* lineItem = new QGraphicsLineItem(start.x(), start.y(), end.x(), end.y());
        qreal lineWidth = qMax(0.5, cell->rect().width() * 0.05);
        lineItem->setPen(QPen(Qt::red, lineWidth));

        m_scene->addItem(lineItem);
        m_lines.append(lineItem);
    }
}

void Field::clearLines()
{
    for (auto* line : m_lines) {
        m_scene->removeItem(line);
        delete line;
    }
    m_lines.clear();

    for (auto* arrow : m_arrowsLines) {
        m_scene->removeItem(arrow);
        delete arrow;
    }
    m_arrowsLines.clear();
}

void Field::onSearchCompleted(Cell* endCell)
{
    if (!endCell || !m_scene || !endCell->parent || m_lines.isEmpty()) {
        return;
    }

    QGraphicsLineItem* lastLine = m_lines.last();
    if (!lastLine) {return;}

    QLineF line = lastLine->line();
    QPointF start = line.p1();
    QPointF end = line.p2();

    ArrowDirection direction = directionCalculation(endCell->row, endCell->column,
                                                    endCell->parent->row, endCell->parent->column);

    switch (direction) {
    case ArrowDirection::RIGHT:
        lastLine->setLine(QLineF(start - QPointF(endCell->rect().width() / 4, 0), end));
        break;

    case ArrowDirection::LEFT:
        lastLine->setLine(QLineF(start + QPointF(endCell->rect().width() / 4, 0), end));
        break;

    case ArrowDirection::DOWN:
        lastLine->setLine(QLineF(start - QPointF(0, endCell->rect().width() / 4), end));
        break;

    case ArrowDirection::UP:
        lastLine->setLine(QLineF(start + QPointF(0, endCell->rect().width() / 4), end));
        break;
    default:
        break;
    }

    drawArrows(endCell, direction);
}

Field::ArrowDirection Field::directionCalculation(int thisRow, int thisCol, int parentRow, int parentCol)
{
    if (thisRow < 0 || thisCol < 0 || parentRow < 0 || parentCol < 0) {
        return ArrowDirection::NONE;
    }

    if(thisRow == parentRow && thisCol > parentCol) {
        return ArrowDirection::RIGHT;
    }

    if(thisRow == parentRow && thisCol < parentCol) {
        return ArrowDirection::LEFT;
    }

    if(thisRow < parentRow && thisCol == parentCol) {
        return ArrowDirection::UP;
    }

    if(thisRow > parentRow && thisCol == parentCol) {
        return ArrowDirection::DOWN;
    }
    return ArrowDirection::NONE;
}

void Field::drawArrows(Cell* сell, ArrowDirection direction)
{
    qreal first_dx1 = 0; // Смещение по оси X для старта первой линии
    qreal first_dy1 = 0;  // Смещение по оси Y для старта первой линии
    qreal first_dx2 = 0; // Смещение по оси X для конца первой линии
    qreal first_dy2 = 0;  // Смещение по оси Y для конца первой линии

    qreal second_dx1 = 0; // Смещение по оси X для старта второй линии
    qreal second_dy1 = 0;  // Смещение по оси Y для старта второй линии
    qreal second_dx2 = 0; // Смещение по оси X для конца второй линии
    qreal second_dy2 = 0;  // Смещение по оси Y для конца второй линии

    switch (direction) {
    case ArrowDirection::DOWN:
        first_dx1 = 0;
        first_dy1 = -сell->rect().width() / 4;
        first_dx2 = -сell->rect().width() + сell->rect().width() / 4;
        first_dy2 = -сell->rect().width();

        second_dx1 = 0;
        second_dy1 = -сell->rect().width() / 4;
        second_dx2 = -сell->rect().width() / 4;
        second_dy2 = 0;

        break;
    case ArrowDirection::LEFT:
        first_dx1 = сell->rect().width() / 4;
        first_dy1 = 0;
        first_dx2 = 0;
        first_dy2 = -сell->rect().width() / 4;

        second_dx1 = сell->rect().width() / 4;
        second_dy1 = 0;
        second_dx2 = 0;
        second_dy2 = сell->rect().width() / 4;

        break;
    case ArrowDirection::RIGHT:
        first_dx1 = -сell->rect().width() / 4;
        first_dy1 = 0;
        first_dx2 = -сell->rect().width();
        first_dy2 = -сell->rect().width() / 4;

        second_dx1 = -сell->rect().width() / 4;
        second_dy1 = 0;
        second_dx2 = -сell->rect().width();
        second_dy2 = сell->rect().width() / 4;
        break;
    case ArrowDirection::UP:
        first_dx1 = 0;
        first_dy1 = сell->rect().height() / 4;
        first_dx2 = -сell->rect().height() + сell->rect().height() / 4;
        first_dy2 = 0;

        second_dx1 = 0;
        second_dy1 = сell->rect().height() / 4;
        second_dx2 = -сell->rect().height() / 4;
        second_dy2 = сell->rect().height();
        break;
    default:
        first_dx1 = 0;
        first_dy1 = 0;
        first_dx2 = 0;
        first_dy2 = 0;

        second_dx1 = 0;
        second_dy1 = 0;
        second_dx2 = 0;
        second_dy2 = 0;
        break;
    }

    qreal lineWidth = qMax(0.5, сell->rect().width() * 0.05);

    QPointF firstLineStart = сell->mapToScene(сell->rect().center()) + QPointF(first_dx1, first_dy1);
    QPointF firstLineEnd = сell->mapToScene(сell->rect().bottomRight()) + QPointF(first_dx2, first_dy2);

    QGraphicsLineItem* firstLine = new QGraphicsLineItem(firstLineStart.x(), firstLineStart.y(),
                                                         firstLineEnd.x(), firstLineEnd.y());
    firstLine->setPen(QPen(Qt::red, lineWidth));
    m_scene->addItem(firstLine);
    m_arrowsLines.append(firstLine);

    QPointF secondLineStart = сell->mapToScene(сell->rect().center()) + QPointF(second_dx1, second_dy1);
    QPointF secondLineEnd = сell->mapToScene(сell->rect().topRight()) + QPointF(second_dx2, second_dy2);

    QGraphicsLineItem* secondLine = new QGraphicsLineItem(secondLineStart.x(), secondLineStart.y(),
                                                          secondLineEnd.x(), secondLineEnd.y());

    secondLine->setPen(QPen(Qt::red, lineWidth));
    m_scene->addItem(secondLine);
    m_arrowsLines.append(secondLine);
}
