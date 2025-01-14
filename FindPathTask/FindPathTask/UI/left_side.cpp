#include "left_side.h"

LeftSide::LeftSide(QWidget *parent)
    : QWidget{parent}
{
    m_layout = new QVBoxLayout(this);
    m_fieldWrapper = new FieldWrapper(this);
    m_sizeSetting = new SizeSetting(this);

    m_layout->addWidget(m_fieldWrapper);
    m_layout->addWidget(m_sizeSetting);
    m_layout->setSpacing(20);
    m_layout->setAlignment(Qt::AlignTop);

    this->setLayout(m_layout);
    this->setFixedSize(780, 728);
}
