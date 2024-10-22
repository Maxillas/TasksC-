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
    void downloadFile();
    void unloadFile();
    void deleteFile();


private:
    QStringListModel* m_list_model = nullptr;
    QStringListModel* getModelRef();

    size_t currentIndex;


    QFileSystemWatcher m_fileSystemWatcher;
    QDir m_directory;

};

#endif // FILEMODELMANAGER_H
