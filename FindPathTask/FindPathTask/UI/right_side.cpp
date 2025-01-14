#include "right_side.h"

RightSide::RightSide(QWidget *parent)
    : QWidget{parent}
{
    m_layout = new QVBoxLayout(this);
    m_generateBtn = new QPushButton(this);
    m_generateBtn->setText("Генерировать");

    //m_layout->setContentsMargins(0,5,0,0);
    m_layout->addWidget(m_generateBtn);
    m_layout->setAlignment(Qt::AlignTop);
    this->setLayout(m_layout);

    this->setStyleSheet("background-color: lightblue;");
    //this->setFixedSize(200, 728);
    this->setFixedSize(200, 710);
}
