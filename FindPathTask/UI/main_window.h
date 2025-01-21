#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "left_side.h"
#include "right_side.h"

#include <QWidget>
#include <QSettings>


class MainWindow : public QWidget
{
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QHBoxLayout* m_layout = nullptr;
    LeftSide* m_left = nullptr;
    RightSide* m_right = nullptr;
    QSettings* m_settings = nullptr;
};

#endif // MAIN_WINDOW_H


