#include "edcwatcher.h"

#include <QMenu>
#include <QCloseEvent>
#include <QApplication>
#include <QMessageBox>


EDCWatcher::EDCWatcher(QWidget *parent)
    : QWidget(parent)
{
    // Initialize GUI
    setFixedWidth(400);
    setFixedHeight(600);

    m_layout =      new QVBoxLayout(this);
    m_listView =    new QListView(this);

    m_btnCreate =   new QPushButton(this);
    m_btnCreate->setText("Создать новый ключ");

    m_btnDownload = new QPushButton(this);
    m_btnDownload->setText("Загрузить ключ для работы");

    m_btnUnload =   new QPushButton(this);
    m_btnUnload->setText("Выгрузить загруженный ключ");

    m_btnDelete =   new QPushButton(this);
    m_btnDelete->setText("Удалить ключ");

    m_layout->addWidget(m_listView);
    m_layout->addWidget(m_btnCreate);
    m_layout->addWidget(m_btnDownload);
    m_layout->addWidget(m_btnUnload);
    m_layout->addWidget(m_btnDelete);

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon("../../UI/Resources/system_tray_icon.svg"));
    QMenu* trayMenu = new QMenu(this);
    QAction* showAction = new QAction("Развернуть", this);
    QAction* quitAction = new QAction("Выход", this);

    trayMenu->addAction(showAction);
    trayMenu->addAction(quitAction);

    m_trayIcon->setContextMenu(trayMenu);

    connect(showAction, &QAction::triggered, this, &EDCWatcher::showApp);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &EDCWatcher::onTrayIconActivated);

    // End Gui Initialize

    m_fileManager = new FileModelManager(this);
    m_listView->setModel(m_fileManager->getModelRef());
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_listView->setCurrentIndex(QModelIndex());

    connect(m_btnCreate, &QPushButton::clicked, this, &EDCWatcher::createNewFile);
    connect(m_btnDownload, &QPushButton::clicked, this, &EDCWatcher::downloadCurrentFile);
    connect(m_btnUnload, &QPushButton::clicked, this, &EDCWatcher::unloadCurrentFile);
    connect(m_btnDelete, &QPushButton::clicked, this, &EDCWatcher::deleteCurrentFile);
}

void EDCWatcher::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange) {
       QWindowStateChangeEvent *stateEvent = static_cast<QWindowStateChangeEvent*>(event);

        if (this->windowState() == Qt::WindowMinimized) {
            m_trayIcon->show();
        }
        else if (stateEvent->oldState() == Qt::WindowMinimized) {
            showApp();
            this->setWindowState(Qt::WindowNoState);
        }
    }

    QWidget::changeEvent(event);
}

void EDCWatcher::closeEvent(QCloseEvent *event)
{
    m_trayIcon->show();
    hide();
    event->ignore();
}

void EDCWatcher::showApp()
{
    m_trayIcon->hide();
    show();
    activateWindow();
    this->setWindowState(Qt::WindowNoState);
}

void EDCWatcher::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
#ifdef Q_OS_WIN
    if(reason == QSystemTrayIcon::ActivationReason::DoubleClick) {
        qDebug() << "AAAA";
        showApp();
    }
#elif defined(Q_OS_LINUX)
        showApp();
#endif

}

void EDCWatcher::createNewFile()
{
    if(!(m_fileManager->createFile())) {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать ключ!");
    }
}

void EDCWatcher::deleteCurrentFile()
{  
    switch (m_fileManager->deleteFile(m_listView->currentIndex())) {

    case ERRORS::SOME_ERROR:
        QMessageBox::warning(this, "Ошибка", "Выберите удаляемый файл!");
        break;
    case ERRORS::CURRENT_FILE:
        QMessageBox::warning(this, "Ошибка", "Необходимо выгрузить ключ!\n");
        break;
    case ERRORS::SUCCESS:
        break;
    default:
        QMessageBox::warning(this, "Ошибка", "Неизвестная ошибка");
        break;
    }
}

void EDCWatcher::downloadCurrentFile()
{
    switch (m_fileManager->downloadFile(m_listView->currentIndex())) {

    case ERRORS::SOME_ERROR:
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить ключ");
        break;
    case ERRORS::CURRENT_FILE:
        QMessageBox::warning(this, "Ошибка", "Данный ключ уже загружен или не выбран ключ\n");
        break;
    case ERRORS::SUCCESS:
        break;
    default:
        QMessageBox::warning(this, "Ошибка", "Неизвестная ошибка");
        break;
    }
}

void EDCWatcher::unloadCurrentFile()
{
    switch (m_fileManager->unloadFile()) {

    case ERRORS::SOME_ERROR:
        QMessageBox::warning(this, "Ошибка", "Не удалось выгрузить ключ");
        break;
    case ERRORS::CURRENT_FILE:
        QMessageBox::warning(this, "Ошибка", "Нечего выгружать");
        break;
    case ERRORS::SUCCESS:
        break;
    default:
        QMessageBox::warning(this, "Ошибка", "Неизвестная ошибка");
        break;
    }
    m_listView->setCurrentIndex(QModelIndex());
}
