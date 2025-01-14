#ifndef RIGHT_SIDE_H
#define RIGHT_SIDE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class RightSide : public QWidget
{
    Q_OBJECT
public:
    explicit RightSide(QWidget *parent = nullptr);

private:
    QVBoxLayout* m_layout = nullptr;
    QPushButton* m_generateBtn = nullptr;
};

#endif // RIGHT_SIDE_H
