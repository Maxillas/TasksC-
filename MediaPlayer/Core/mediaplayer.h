#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QMediaPlayer>

class MediaPlayer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged FINAL)

public:
    explicit MediaPlayer(QObject *parent = nullptr);

    bool isPlaying() const;

public slots:
    void play();
    void stop();
    void repeat();
    void next();
    void prev();
signals:

    void isPlayingChanged();

private:
    QMediaPlayer* m_mediaPlayer;
    QAudioOutput* m_audioOutput;

    bool m_isPlaying;

};

#endif // MEDIAPLAYER_H
