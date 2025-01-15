#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>


class Field : public QGraphicsView
{
    Q_OBJECT

public:
    Field(QGraphicsView *parent = nullptr);


private:
    QGraphicsScene* m_scene = nullptr;
    QGraphicsRectItem* m_rect = nullptr;

    void generateField(uint16_t width, uint16_t height);

};
#endif // FIELD_H
