#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

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

private:
    //добавить QObject cell_controller, который будет содержать и вызывать сигналы.

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {

        qDebug() << "Mouse pressed on CustomRectItem at:" << row << ".." << column;
        qDebug() << "isWall = " << isWall;
        //emit mousePressed();

    }
};

#endif // CELL_H
