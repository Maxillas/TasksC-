#include "field_wrapper.h"

FieldWrapper::FieldWrapper(QWidget *parent)
    : QWidget{parent}
{
    m_layout = new QVBoxLayout(this);
    m_field = new Field();

    m_layout->addWidget(m_field);

    this->setLayout(m_layout);
    this->setStyleSheet("background-color: white;""border: none");
}
