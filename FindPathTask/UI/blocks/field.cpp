#include "field.h"
#include "../../Core/pathfinder.h"

Field::Field(QGraphicsView *parent):
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this))
{

    this->setScene(m_scene);
    this->setWindowTitle("Find Path");
    //this->setFixedSize(725, 568);
    this->setFixedSize(780, 568);
    this->show();

    connect(&PathFinder::getInstance(), &PathFinder::generateField, this, &Field::generateField);
}

void Field::generateField(uint16_t width, uint16_t height)
{
    m_scene->clear();
    // Параметры поля
    int cellSize = 40;  // Размер клетки (ширина и высота)

    // Создаем поле 10x10
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            // Создаем прямоугольник (клетку)
            QGraphicsRectItem *cell = new QGraphicsRectItem(col * cellSize, row * cellSize, cellSize, cellSize);
            cell->setPen(QPen(Qt::black));  // Граница клетки
            cell->setBrush(QBrush(Qt::white));  // Заливка клетки

            // Добавляем клетку на сцену
            m_scene->addItem(cell);
        }
    }
}
