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
    m_list_model->setStringList(m_directory.entryList(QDir::Files));


}

void FileModelManager::createFile()
{
    QFile newFile(fileNameGenerator());
    if (newFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&newFile);
        out << "CODE!\n";
        newFile.close();
    }
    m_list_model->setStringList(m_directory.entryList(QDir::Files));
}

void FileModelManager::downloadFile(QModelIndex index)
{    
    if(m_selectedIndex == index) {
        return;
    }

    unloadFile();
    m_selectedIndex = index;
    m_prevFileName = m_selectedIndex.data().toString();
    m_list_model->setData(m_selectedIndex, m_selectedIndex.data().toString() + "\t" + "***ЗАГРУЖЕНО***");
    m_downloadedFile.setFileName(static_cast<QString>(DIR_PATH) + "/" + m_prevFileName);

    if(m_downloadedFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Файл загружен";
    } else {
        qDebug() << "Ошибка загрузки файла";
    }
}

void FileModelManager::unloadFile()
{
    if(!(m_selectedIndex.isValid())) {
        return;
    }
    m_list_model->setData(m_selectedIndex, m_prevFileName);
    m_selectedIndex = QModelIndex();

    if(m_downloadedFile.isOpen()) {
        m_downloadedFile.close();
        qDebug() << "Файл выгружен";
    } else {
        qDebug() << "Файл не открыт!";
    }
}

void FileModelManager::deleteFile(QModelIndex index)
{
    QFile searchedFile(static_cast<QString>(DIR_PATH) + "/" + index.data().toString());
    if (searchedFile.exists()) {
        searchedFile.remove();
    }
    m_list_model->setStringList(m_directory.entryList(QDir::Files));
}

QStringListModel* FileModelManager::getModelRef()
{
    return m_list_model;
}

QString FileModelManager::fileNameGenerator()
{
    QString fileName = "Key_" + QDateTime::currentDateTime().toString("dd:mm:yyyy_hh:mm:ss") + ".txt";
    return (static_cast<QString>(DIR_PATH) + "/" + fileName);
}
