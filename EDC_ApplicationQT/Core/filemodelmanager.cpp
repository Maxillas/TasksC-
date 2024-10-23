#include "filemodelmanager.h"

FileModelManager::FileModelManager(QObject *parent)
    : QObject{parent}
{
    m_directory.setPath(DIR_PATH);

    if (!m_directory.exists()) {
        qWarning() << "Директория не существует:";
        return;
    }

    m_list_model = new QStringListModel(this);
    m_fileSystemWatcher = new QFileSystemWatcher(this);

    updateModel();

    m_fileSystemWatcher->addPath(DIR_PATH);
    connect(m_fileSystemWatcher, &QFileSystemWatcher::directoryChanged,
            this, &FileModelManager::updateModel);
}

bool FileModelManager::createFile()
{
    QFile newFile(fileNameGenerator());
    if (newFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&newFile);
        out << "CODE!\n";
        newFile.close();
        return true;
    }
    return false;
}

ERRORS FileModelManager::downloadFile(QModelIndex index)
{    
    if(m_selectedIndex == index) {
        return ERRORS::CURRENT_FILE;
    }
    unloadFile();
    m_selectedIndex = index;
    m_prevFileName = m_selectedIndex.data().toString();
    m_list_model->setData(m_selectedIndex,
                          m_selectedIndex.data().toString() + "\t" + "***ЗАГРУЖЕНО***");

    m_downloadedFile.setFileName(static_cast<QString>(DIR_PATH) + "/" + m_prevFileName);

    if(m_downloadedFile.open(QIODevice::ReadOnly)) {
        return ERRORS::SUCCESS;
    } else {
        return ERRORS::SOME_ERROR;
    }
}

ERRORS FileModelManager::unloadFile()
{
    if(!(m_selectedIndex.isValid())) {
        return ERRORS::CURRENT_FILE;
    }
    m_list_model->setData(m_selectedIndex, m_prevFileName);
    m_selectedIndex = QModelIndex();

    if(m_downloadedFile.isOpen()) {
        m_downloadedFile.close();
        return ERRORS::SUCCESS;
    } else {
        return ERRORS::SOME_ERROR;
    }
}

ERRORS FileModelManager::deleteFile(QModelIndex index)
{
    if(m_selectedIndex.isValid()) {
        return ERRORS::CURRENT_FILE;
    }
    QString searchedFileName = static_cast<QString>(DIR_PATH) + "/" + index.data().toString();
    QFile searchedFile(searchedFileName);
    QFileInfo fileInfo(searchedFileName);

    if (!(searchedFile.exists()) || fileInfo.isDir()) {
        return ERRORS::SOME_ERROR ;
    }
    searchedFile.remove();
    updateModel();
    return ERRORS::SUCCESS;
}

QStringListModel* FileModelManager::getModelRef()
{
    return m_list_model;
}

QString FileModelManager::fileNameGenerator()
{
    QString fileName = "Key_" +
                        QDateTime::currentDateTime().toString("dd.MM.yyyy_hh.mm.ss") + ".txt";
    return (static_cast<QString>(DIR_PATH) + "/" + fileName);
}

void FileModelManager::updateModel()
{
    m_list_model->setStringList(m_directory.entryList(QDir::Files));
}
