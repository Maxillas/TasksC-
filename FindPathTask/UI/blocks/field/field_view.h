#ifndef FIELD_H
#define FIELD_H

#include "cell.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVector>


class Field : public QGraphicsView
{

public:
    Field(QGraphicsView *parent = nullptr);

private:
    void generateField(const uint16_t& width, const uint16_t& height);
    void onDontFindPath();
    void onFoundPath(QVector<Cell*> path);
    void clearLines();


    QGraphicsScene* m_scene = nullptr;
    QGraphicsRectItem* m_rect = nullptr;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    Cell* m_currentCell = nullptr;
    QList<QGraphicsLineItem*> m_lines;

};
#endif // FIELD_H
