#include "field_view.h"
#include "../../../Core/pathfinder.h"
#include <QWheelEvent>
#include <QRandomGenerator>

Field::Field(QGraphicsView *parent):
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this))
{
    //this->verticalScrollBar();
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
    this->setFixedSize(750, 550);
    this->show();

    connect(&PathFinder::getInstance(), &PathFinder::generateField, this, &Field::generateField);
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

void Field::generateField(uint16_t width, uint16_t height)
{
    m_scene->clear();
    this->resetTransform();

    int cellWidth = (viewport()->width() - 2) / width;
    int cellHeight = (viewport()->height() - 2) / height;
    int cellSize = cellWidth <= cellHeight ? cellWidth : cellHeight;

    m_grid.clear();
    m_grid.resize(height, QVector<Cell*>(width));

    qreal wallProbability = 0.15;

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {

            Cell* cell = new Cell(col * cellSize, row * cellSize, cellSize, cellSize);
            cell->setPen(QPen(Qt::black));
            cell->setBrush(QBrush(Qt::white));
            cell->row = row;
            cell->column = col;

            //connect(cell, &Cell::mousePressed, this, &Field::onMouseClicked);

            m_scene->addItem(cell); //сцена управляет жизнью cell => delete не нужен
            m_grid[row][col] = cell;

            if (QRandomGenerator::global()->generateDouble() < wallProbability) {
                cell->setBrush(QBrush(Qt::black));
                m_grid[row][col]->isWall = true;
            } else {
                cell->setBrush(QBrush(Qt::white));
                m_grid[row][col]->isWall = false;
            }
        }
    }
    this->setSceneRect(0, 0, width * cellSize, height * cellSize);
    this->centerOn(width * cellSize / 2, height * cellSize / 2);
}

