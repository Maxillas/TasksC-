#include "pathfinder.h"
#include <QDebug>

PathFinder::PathFinder(QObject *parent)
    : QObject{parent},
    m_height(0),
    m_width(0)
{}

void PathFinder::print()
{
    qDebug() << "YAHHHHA BLYA";
}

void PathFinder::setWidth(const uint16_t& newWidth)
{
    if(m_width == newWidth) {
        return;
    }
    m_width = newWidth;
    qDebug() << m_width;
}

uint16_t PathFinder::getWidth() const
{
    return m_width;
}

void PathFinder::setHeight(const uint16_t& newHeight)
{
    if(m_height == newHeight) {
        return;
    }
    m_height = newHeight;
    qDebug() << m_height;
}

uint16_t PathFinder::getHeight() const
{
    return m_height;
}
