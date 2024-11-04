#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "Core/mediaplayer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;

    MediaPlayer audioPlayer;

    view.engine()->rootContext()->setContextProperty("AudioPlayer", &audioPlayer);

    view.engine()->rootContext()->setContextProperty("PlayListManager", &audioPlayer.playListManager());
    view.engine()->rootContext()->setContextProperty("PlayList", &audioPlayer.playListManager().playList());

    //view.engine()->rootContext()->setContextProperty("PlayList", &audioPlayer.playList());

    view.setSource(QStringLiteral("qrc:/MediaPlayer/UI/Main.qml"));

    QObject::connect(view.engine(), &QQmlEngine::quit, &view,
        []() {
            qApp->quit();
        });

    view.show();
    return app.exec();
}
