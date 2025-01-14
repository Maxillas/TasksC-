#include "size_setting.h"

SizeSetting::SizeSetting(QWidget *parent)
    : QWidget{parent}
{
    m_layout = new QHBoxLayout(this);
    m_widthEdit = new QLineEdit(this);
    m_heightEdit = new QLineEdit(this);
    m_widthLabel = new QLabel(this);
    m_heightLabel = new QLabel(this);

    m_widthEdit->setFixedSize(150, 100);


    m_heightEdit->setFixedSize(150, 100);


    m_widthLabel->setFixedSize(150, 100);
    m_widthLabel->setFont(QFont("Arial", 18, QFont::Bold));
    m_widthLabel->setText("W");

    m_heightLabel->setFixedSize(150, 100);
    m_heightLabel->setText("H");

    m_layout->addWidget(m_widthLabel);
    m_layout->addWidget(m_widthEdit);
    m_layout->addWidget(m_heightLabel);
    m_layout->addWidget(m_heightEdit);

    this->setLayout(m_layout);
    this->setFixedSize(725, 120);

}
