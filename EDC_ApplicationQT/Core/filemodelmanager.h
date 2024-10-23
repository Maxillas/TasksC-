#ifndef FILEMODELMANAGER_H
#define FILEMODELMANAGER_H

#include <QFileSystemWatcher>
#include <QDir>

#include <QStringListModel>

enum class ERRORS {
    SUCCESS,
    CURRENT_FILE,
    SOME_ERROR
};

class FileModelManager : public QObject
{
    Q_OBJECT

    friend class EDCWatcher;
public:
    static constexpr char const * DIR_PATH = "../../Keys";

    FileModelManager(QObject *parent = nullptr);

public slots:
    bool createFile();
    ERRORS downloadFile(QModelIndex index);
    ERRORS unloadFile();
    ERRORS deleteFile(QModelIndex index);


private:
    QStringListModel* m_list_model = nullptr;
    QStringListModel* getModelRef();

    QString fileNameGenerator();

    void updateModel();

    QModelIndex m_selectedIndex;
    QString m_prevFileName;
    QFile m_downloadedFile;

    QFileSystemWatcher* m_fileSystemWatcher = nullptr;
    QDir m_directory;

};

#endif // FILEMODELMANAGER_H
