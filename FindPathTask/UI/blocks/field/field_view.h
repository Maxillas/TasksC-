#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVector>

#include "cell.h"


class Field : public QGraphicsView
{
    Q_OBJECT

public:
    Field(QGraphicsView *parent = nullptr);


private:
    //void onMouseClicked();

    QGraphicsScene* m_scene = nullptr;
    QGraphicsRectItem* m_rect = nullptr;
    void wheelEvent(QWheelEvent *event) override;

    void generateField(uint16_t width, uint16_t height);

    QVector<QVector<Cell*>> m_grid;
};
#endif // FIELD_H
