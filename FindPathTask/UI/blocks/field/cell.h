#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QBrush>
#include "../../../Core/cell_controller.h"

class Cell : public QGraphicsRectItem
{
public:
    Cell(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr)
        : QGraphicsRectItem(x, y, width, height, parent) {}

    bool isWall = false;
    bool visited = false;
    int row = -1;
    int column = -1;
    Cell* parent = nullptr;

    CellController controller; //объект для использования сигналов

private:

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        emit controller.onCellPressed();
        qDebug() << "Mouse pressed on CustomRectItem at:" << row << ".." << column;
        qDebug() << "isWall = " << isWall;
        setBrush(QBrush(Qt::black));

    }
};

#endif // CELL_H
