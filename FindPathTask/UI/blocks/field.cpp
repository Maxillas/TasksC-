#include "field.h"

Field::Field(QGraphicsView *parent):
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this))
{

    m_rect = m_scene->addRect(0, 0, 100, 100);
    m_rect->setPos(150,50);
    m_rect->setBrush(Qt::blue);

    this->setScene(m_scene);
    this->setWindowTitle("Find Path");
    this->setFixedSize(725, 568);
    this->show();
}
