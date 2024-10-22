#ifndef FILEMODELMANAGER_H
#define FILEMODELMANAGER_H

#include <QFileSystemWatcher>
#include <QDir>

#include <QStringListModel>


class FileModelManager : public QObject
{
    Q_OBJECT

    friend class EDCWatcher;
public:
    static constexpr char const * DIR_PATH = "../../Keys";

    FileModelManager(QObject *parent = nullptr);

public slots:
    void createFile();
    void downloadFile(QModelIndex index);
    void unloadFile();
    void deleteFile(QModelIndex index);


private:
    QStringListModel* m_list_model = nullptr;
    QStringListModel* getModelRef();

    QString fileNameGenerator();

    QModelIndex m_selectedIndex;
    QString m_prevFileName;
    QFile m_downloadedFile;

    QFileSystemWatcher m_fileSystemWatcher;
    QDir m_directory;

};

#endif // FILEMODELMANAGER_H
