#include "edcwatcher.h"

//DEBUG
#include <QStringListModel>

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
    // End Gui Initialize

    m_fileManager = new FileModelManager(this);
    m_listView->setModel(m_fileManager->getModelRef());

    // QStringList dataList;
    // dataList << "Alice" << "Bob" << "Charlie" << "David";
    // QStringListModel *model = new QStringListModel();
    // model->setStringList(dataList);


    connect(m_btnCreate, &QPushButton::clicked, m_fileManager, &FileModelManager::createFile);
    connect(m_btnDownload, &QPushButton::clicked, m_fileManager, &FileModelManager::downloadFile);
    connect(m_btnUnload, &QPushButton::clicked, m_fileManager, &FileModelManager::unloadFile);
    connect(m_btnDelete, &QPushButton::clicked, m_fileManager, &FileModelManager::deleteFile);


}

EDCWatcher::~EDCWatcher() {
}
