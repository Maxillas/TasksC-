#include <QUrl>

#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_data.append(QString("Grib.flac"));
    m_data.append(QString("Try.mp3"));

}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.size();

}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole) {
        int row = index.row();
        return m_data[row];
    }

    return QVariant();
}

void PlaylistModel::addTrack(QString newTrack)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(QString(newTrack));
    endInsertRows();
}
