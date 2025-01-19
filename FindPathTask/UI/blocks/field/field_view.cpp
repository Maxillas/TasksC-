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
    // Выводим координаты мыши
    //qDebug() << "Mouse moved to:" << event->pos();
    QGraphicsItem* item = this->itemAt(event->pos());

    if (item) {
        Cell* cell = dynamic_cast<Cell*>(item);
        if (cell && FieldController::getInstance().isSearchStarted() && !cell->isWall) {
            // Выводим информацию о ячейке
            //qDebug() << "Mouse over cell at row:" << cell->row << "column:" << cell->column;

            //FieldController::getInstance().onCellClicked(cell);
            // Пример: изменяем цвет ячейки при наведении
            //cell->setBrush(QBrush(Qt::yellow));
        }
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
   QMessageBox::warning(this, "Ошибка", "Путь не может быть найден!");
}

void Field::onFoundPath(QVector<Cell *> path)
{
    for (Cell* cell : path) {
        cell->setCellText("P"); // Помечаем ячейки пути
        //qDebug() << "Path cell: " << cell->row << ", " << cell->column;
    }
}
