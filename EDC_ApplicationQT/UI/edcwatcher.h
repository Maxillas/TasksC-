#ifndef EDCWATCHER_H
#define EDCWATCHER_H

#include "../Core/filemodelmanager.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>

class EDCWatcher : public QWidget
{
    Q_OBJECT

public:
    EDCWatcher(QWidget *parent = nullptr);
    ~EDCWatcher();
signals:


private:
    QVBoxLayout* m_layout = nullptr;
    QPushButton* m_btnCreate = nullptr;
    QPushButton* m_btnDownload = nullptr;
    QPushButton* m_btnUnload = nullptr;
    QPushButton* m_btnDelete = nullptr;
    QListView* m_listView = nullptr;

    FileModelManager* m_fileManager = nullptr;

    void deleteCurrentFile();
    void downloadCurrentFile();

};
#endif // EDCWATCHER_H
