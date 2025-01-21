#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    m_left = new LeftSide(this);
    m_right = new RightSide(this);

    m_layout->setContentsMargins(20,20,20,20);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_left);
    m_layout->addWidget(m_right);

    this->setLayout(m_layout);
    this->setObjectName("mainWindow");
    this->setStyleSheet("#mainWindow {background-color: white; border: 3px solid black;}");
    this->setFixedSize(1024, 768);
    this->show();

    m_settings = new QSettings("ProSoft", "FindPathTask", this);
    restoreGeometry(m_settings->value("geometry").toByteArray());
}

MainWindow::~MainWindow()
{
    m_settings->setValue("geometry", saveGeometry());
}

