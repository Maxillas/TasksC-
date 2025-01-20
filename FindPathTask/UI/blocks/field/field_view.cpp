#include "field_view.h"
#include "../../../Core/field_controller.h"

//#include "../../../Core/cell_controller.h"
#include <QWheelEvent>
#include <QMessageBox>
#include <QRandomGenerator>

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
    // Получаем все элементы, которые пересекаются с позицией мыши
    QList<QGraphicsItem*> items = this->items(event->pos());

    // Ищем первую ячейку в списке
    Cell* newCell = nullptr;
    for (QGraphicsItem* item : items) {
        newCell = dynamic_cast<Cell*>(item);
        if (newCell) {
            break; // Нашли ячейку
        }
    }

    // Проверяем, что newCell не nullptr и отличается от текущей ячейки
    if (newCell && newCell != m_currentCell) {
        m_currentCell = newCell; // Обновляем текущую ячейку
        FieldController::getInstance().onMouseMove(m_currentCell);
    } else if (!newCell) {
        m_currentCell = nullptr;
    }

    // Вызываем базовую реализацию, если нужно
    QGraphicsView::mouseMoveEvent(event);
}

void Field::generateField(const uint16_t& width, const uint16_t& height)
{
    //TODO перенести в отдельный поток генерацию поля, т.к. зависает при больших значениях
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
        if(cell == startCell) {
            cell->setCellText("A");
            continue;
        }

        if (!cell || !cell->parent || !startCell || !m_scene) {
            return;
        }

        QPointF start = cell->mapToScene(cell->rect().center());
        QPointF end = cell->parent->mapToScene(cell->parent->rect().center());

        QGraphicsLineItem* lineItem = new QGraphicsLineItem(start.x(), start.y(), end.x(), end.y());
        qreal lineWidth = qMax(1.0, cell->rect().width() * 0.05);
        lineItem->setPen(QPen(Qt::red, lineWidth));
        lineItem->setZValue(1000);

        // Добавляем линию на сцену и в контейнер
        m_scene->addItem(lineItem);
        m_lines.append(lineItem);

    }
}

void Field::clearLines()
{
    // Удаляем все линии из сцены
    for (auto* line : m_lines) {
        m_scene->removeItem(line);
        delete line; // Освобождаем память
    }
    m_lines.clear(); // Очищаем контейнер
}
