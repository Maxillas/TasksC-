#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;

    view.setSource(QStringLiteral("qrc:/MediaPlayer/UI/Main.qml"));


    QObject::connect(view.engine(), &QQmlEngine::quit,
        []() {
            qApp->quit();
        });

    view.show();
    return app.exec();
}
