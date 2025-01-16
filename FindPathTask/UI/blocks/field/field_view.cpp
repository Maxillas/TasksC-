#include "field_view.h"
#include "../../../Core/pathfinder.h"
#include <QWheelEvent>

Field::Field(QGraphicsView *parent):
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this))
{
    this->verticalScrollBar();
    // this->setStyleSheet(
    //     "QScrollBar:vertical {"
    //     "   background: #f0f0f0;"
    //     "   width: 15px;"
    //     "}"
    //     "QScrollBar::handle:vertical {"
    //     "   background: #a0a0a0;"
    //     "   min-height: 20px;"
    //     "}"
    //     "QScrollBar::add-line:vertical {"
    //     "   background: none;"
    //     "}"
    //     "QScrollBar::sub-line:vertical {"
    //     "   background: none;"
    //     "}"
    //     "QScrollBar:horizontal {"
    //     "   background: #f0f0f0;"
    //     "   height: 15px;"
    //     "}"
    //     "QScrollBar::handle:horizontal {"
    //     "   background: #a0a0a0;"
    //     "   min-width: 20px;"
    //     "}"
    //     "QScrollBar::add-line:horizontal {"
    //     "   background: none;"
    //     "}"
    //     "QScrollBar::sub-line:horizontal {"
    //     "   background: none;"
    //     "}"
    //     );
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setScene(m_scene);
    this->setWindowTitle("Find Path");
    this->setFixedSize(750, 568);
    this->show();

    connect(&PathFinder::getInstance(), &PathFinder::generateField, this, &Field::generateField);
}

void Field::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) {
        scale(1.1, 1.1);
    } else {
        scale(0.9, 0.9);
    }
    event->accept();
}

void Field::generateField(uint16_t width, uint16_t height, uint16_t cellSize)
{
    m_scene->clear();
    this->resetTransform();
    this->centerOn(0,0);
    // Параметры поля
    int cellWidth = viewport()->width() / width;
    int cellHeight = viewport()->height() / height;
    int cellSize2 = cellWidth <= cellHeight ? cellWidth : cellHeight;

    // Создаем поле 10x10
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            // Создаем прямоугольник (клетку)
            QGraphicsRectItem *cell = new QGraphicsRectItem(col * cellSize2, row * cellSize2, cellSize2, cellSize2);
            cell->setPen(QPen(Qt::black));  // Граница клетки
            cell->setBrush(QBrush(Qt::white));  // Заливка клетки

            // Добавляем клетку на сцену
            m_scene->addItem(cell);
        }
    }
    this->centerOn(0,0);
}
