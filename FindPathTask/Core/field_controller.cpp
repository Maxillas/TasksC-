#include "field_controller.h"

FieldController::FieldController(QObject *parent)
    : QObject{parent},
    m_height(0),
    m_width(0)
{}

void FieldController::setStartCell(Cell* startCell)
{
    m_startCell = startCell;
}

void FieldController::clean()
{
    m_startCell = nullptr; //объект не трогаем, т.к. он управляется сценой
    m_endCell = nullptr;
}

void FieldController::setWidth(const uint16_t& newWidth)
{
    if(m_width == newWidth) {
        return;
    }
    m_width = newWidth;
}

uint16_t FieldController::getWidth() const
{
    return m_width;
}

void FieldController::setHeight(const uint16_t& newHeight)
{
    if(m_height == newHeight) {
        return;
    }
    m_height = newHeight;
}

uint16_t FieldController::getHeight() const
{
    return m_height;
}
