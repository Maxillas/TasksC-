#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>

class PlaylistModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PlaylistModel(QObject *parent = nullptr);

    // Header:
    // QVariant headerData(int section,
    //                     Qt::Orientation orientation,
    //                     int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addTrack(QString newTrack);

private:
    QVector<QString> m_data;
};

#endif // PLAYLISTMODEL_H
