#include "UI/main_window.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    return a.exec();
}
