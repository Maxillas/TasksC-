#include "playlistmanager.h"

PlaylistManager::PlaylistManager(QObject *parent)
    : QObject(parent)
{

}

PlaylistModel &PlaylistManager::playList()
{
    return m_playlist;
}

void PlaylistManager::addTrack()
{
    QString newTrack = "SSSSDDAAAA";
    m_playlist.addTrack(newTrack);
    qDebug() << "NEEEWWW";


}
