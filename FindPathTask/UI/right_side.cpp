#include "right_side.h"
#include "../Core/pathfinder.h"

#include <QMessageBox>

RightSide::RightSide(QWidget *parent)
    : QWidget{parent}
{
    m_layout = new QVBoxLayout(this);
    m_generateBtn = new QPushButton(this);
    m_generateBtn->setText("Генерировать");
    m_generateBtn->setFixedHeight(75);
    m_generateBtn->setStyleSheet(
        "QPushButton {"
        "   font-size: 20px;"
        "   color: black;"
        "   background-color: white;"
        "   border: 3px solid black;"
        "   border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #5dade2;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #2c81ba;"
        "}"

    );

    m_layout->addWidget(m_generateBtn);
    m_layout->setAlignment(Qt::AlignTop);
    this->setLayout(m_layout);
    this->setFixedSize(200, 710);
    connect(m_generateBtn, &QPushButton::clicked, this, &RightSide::generateField);
}

void RightSide::generateField()
{
    const uint16_t& width = PathFinder::getInstance().getWidth();
    const uint16_t& height = PathFinder::getInstance().getHeight();

    if(width == 0 && height == 0) {
        QMessageBox::warning(this, "Ошибка", "Некорректная ширина и высота!");
        return;
    }
    if(width == 0) {
        QMessageBox::warning(this, "Ошибка", "Некорректная ширина!");
        return;
    }
    if(height == 0) {
        QMessageBox::warning(this, "Ошибка", "Некорректная высота!");
        return;
    }

    emit PathFinder::getInstance().generateField(width, height);
}

