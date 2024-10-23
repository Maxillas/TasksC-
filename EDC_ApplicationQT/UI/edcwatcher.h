#ifndef EDCWATCHER_H
#define EDCWATCHER_H

#include "../Core/filemodelmanager.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QSystemTrayIcon>

class EDCWatcher : public QWidget
{
    Q_OBJECT

public:
    EDCWatcher(QWidget *parent = nullptr);

private:
    QVBoxLayout* m_layout = nullptr;
    QPushButton* m_btnCreate = nullptr;
    QPushButton* m_btnDownload = nullptr;
    QPushButton* m_btnUnload = nullptr;
    QPushButton* m_btnDelete = nullptr;
    QListView* m_listView = nullptr;
    QSystemTrayIcon* m_trayIcon = nullptr;

    FileModelManager* m_fileManager = nullptr;

    void changeEvent(QEvent* event) override;
    void closeEvent(QCloseEvent *event) override;

    void showApp();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

    void createNewFile();
    void deleteCurrentFile();
    void downloadCurrentFile();
    void unloadCurrentFile();

};
#endif // EDCWATCHER_H
