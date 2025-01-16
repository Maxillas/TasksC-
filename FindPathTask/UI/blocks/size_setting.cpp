#include "size_setting.h"
#include "../../Core/field_controller.h"

#include <QIntValidator>
#include <QMessageBox>

SizeSetting::SizeSetting(QWidget *parent)
    : QWidget{parent}
{
    m_layout = new QHBoxLayout(this);
    m_widthEdit = new QLineEdit(this);
    m_heightEdit = new QLineEdit(this);
    m_widthLabel = new QLabel(this);
    m_heightLabel = new QLabel(this);

    m_widthEdit->setFixedSize(150, 115);
    m_widthEdit->setFont(QFont("Arial", 30, QFont::Normal));
    m_widthEdit->setStyleSheet("color: black; border: 3px solid black; background-color: white");
    m_widthEdit->setValidator(new QIntValidator(1, 100, m_heightEdit));
    m_widthEdit->setAlignment(Qt::AlignCenter);

    m_heightEdit->setFixedSize(150, 115);
    m_heightEdit->setFont(QFont("Arial", 30, QFont::Normal));
    m_heightEdit->setStyleSheet("color: black; border: 3px solid black; background-color: white");
    m_heightEdit->setValidator(new QIntValidator(1, 100, m_heightEdit));
    m_heightEdit->setAlignment(Qt::AlignCenter);

    m_widthLabel->setFixedSize(40, 115);
    m_widthLabel->setFont(QFont("Arial", 30, QFont::Bold));
    m_widthLabel->setStyleSheet("color: black; border: 3px white;");
    m_widthLabel->setText("W");

    m_heightLabel->setFixedSize(40, 115);
    m_heightLabel->setFont(QFont("Arial", 30, QFont::Bold));
    m_heightLabel->setStyleSheet("color: black; border: 3px white");
    m_heightLabel->setText("H");

    m_layout->setContentsMargins(150, 0, 0, 0);
    m_layout->setAlignment(Qt::AlignLeft);
    m_layout->addWidget(m_widthLabel);
    m_layout->addWidget(m_widthEdit);
    m_layout->addSpacing(100);
    m_layout->addWidget(m_heightLabel);
    m_layout->addWidget(m_heightEdit);

    this->setLayout(m_layout);

    connect(m_heightEdit, &QLineEdit::textChanged, this, &SizeSetting::setHeight);
    connect(m_widthEdit, &QLineEdit::textChanged, this, &SizeSetting::setWidth);

}

void SizeSetting::setWidth()
{
    if(m_widthEdit->text().isEmpty()) {
        return;
    }
    uint width = m_widthEdit->text().toUInt();

    if(width > MAX_WIDTH) {
        QMessageBox::warning(this, "Ошибка", "Ширина должна быть не больше 100!");
        m_widthEdit->clear();
        FieldController::getInstance().setWidth(0);
        return;
    }
    if(width == 0) {
        QMessageBox::warning(this, "Ошибка", "Ширина не может быть равна 0!");
        m_widthEdit->clear();
    }
    FieldController::getInstance().setWidth(width);
}

void SizeSetting::setHeight()
{
    if(m_heightEdit->text().isEmpty()) {
        return;
    }

    uint height = m_heightEdit->text().toUInt();

    if(height > MAX_HEIGHT) {
        QMessageBox::warning(this, "Ошибка", "Высота должна быть не больше 100!");
        m_heightEdit->clear();
        FieldController::getInstance().setHeight(0);
        return;
    }
    if(height == 0) {
        QMessageBox::warning(this, "Ошибка", "Высота не может быть равна 0!");
        m_heightEdit->clear();
    }
    FieldController::getInstance().setHeight(height);
}
