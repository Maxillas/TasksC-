#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVector>

#include "cell.h"

class Field : public QGraphicsView
{

public:
    enum class ArrowDirection {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };
    Field(QGraphicsView *parent = nullptr);

private:
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void generateField(uint16_t width, uint16_t height);
    void onDontFindPath();
    void onFoundPath(const QVector<Cell*>& path);
    void clearLines();
    void onSearchCompleted(Cell* endCell);
    void drawArrows(Cell* сell, ArrowDirection direction);

    ArrowDirection directionCalculation(int thisRow, int thisCol, int parentRow, int parentCol);

    QGraphicsScene* m_scene = nullptr;
    QGraphicsRectItem* m_rect = nullptr;
    Cell* m_currentCell = nullptr;
    QList<QGraphicsLineItem*> m_lines;
    QVector<QGraphicsLineItem*> m_arrowsLines;
};
#endif // FIELD_H
