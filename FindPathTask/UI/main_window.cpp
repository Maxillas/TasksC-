#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    // Initialize GUI
    m_layout = new QHBoxLayout(this);
    m_left = new LeftSide(this);
    m_right = new RightSide(this);

    m_layout->setContentsMargins(20,20,20,20);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_left);
    m_layout->addWidget(m_right);

    this->setLayout(m_layout);
    // End GUI Initialize

    this->setObjectName("mainWindow");
    this->setStyleSheet("#mainWindow {background-color: white; border: 3px solid black;}");
    this->setFixedSize(1024, 768);

    this->show();

}

