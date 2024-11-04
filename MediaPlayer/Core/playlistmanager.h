#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include "playlistmodel.h"

class PlaylistManager : public QObject
{
    Q_OBJECT
public:
    PlaylistManager(QObject *parent = nullptr);

    PlaylistModel& playList();

    Q_INVOKABLE void addTrack();


    PlaylistModel m_playlist;
};

#endif // PLAYLISTMANAGER_H
