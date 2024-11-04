#include "mediaplayer.h"
#include <QAudioOutput>
#include <QQmlEngine>
#include <QTimer>

MediaPlayer::MediaPlayer(QObject *parent)
    : QObject{parent}
{
    qDebug() << "CREATE PLAYER";
    m_mediaPlayer = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
   // m_audioOutput->setDevice()
    m_mediaPlayer->setAudioOutput(m_audioOutput);

    m_mediaPlayer->setSource(QString("Try.mp3"));

    QJSEngine::setObjectOwnership(this, QJSEngine::ObjectOwnership::CppOwnership);

}

void MediaPlayer::play()
{
    if(m_mediaPlayer->isPlaying()) {
        m_mediaPlayer->pause();
    } else {
        m_mediaPlayer->play();
    }
    emit isPlayingChanged();
}

void MediaPlayer::stop()
{
    m_mediaPlayer->stop();
}

void MediaPlayer::repeat()
{
    //m_mediaPlayer->p
}

void MediaPlayer::next()
{

}

void MediaPlayer::prev()
{

}

bool MediaPlayer::isPlaying() const
{
    return m_mediaPlayer->isPlaying();
}

// PlaylistModel &MediaPlayer::playList()
// {
//     return m_playListManager.playList();
// }

PlaylistManager& MediaPlayer::playListManager()
{
    return m_playListManager;
}

