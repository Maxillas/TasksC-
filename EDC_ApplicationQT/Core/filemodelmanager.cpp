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
    QString newFileName = static_cast<QString>(DIR_PATH) + "/" + "Key" +
                          QString::number(m_list_model->rowCount() + 1) + ".txt";
    QFile newFile(newFileName);
    if (newFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&newFile);
        out << "CODE!\n";
        newFile.close();
    }
    m_list_model->setStringList(m_directory.entryList(QDir::Files));
}

void FileModelManager::downloadFile()
{

}

void FileModelManager::unloadFile()
{

}

void FileModelManager::deleteFile()
{

}

QStringListModel* FileModelManager::getModelRef()
{
    return m_list_model;
}
