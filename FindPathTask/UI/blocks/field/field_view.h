#ifndef FIELD_H
#define FIELD_H

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

    QGraphicsScene* m_scene = nullptr;
    QGraphicsRectItem* m_rect = nullptr;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

};
#endif // FIELD_H
