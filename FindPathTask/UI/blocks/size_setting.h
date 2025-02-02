#ifndef SIZE_SETTING_H
#define SIZE_SETTING_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

class SizeSetting : public QWidget
{
    Q_OBJECT
public:
    explicit SizeSetting(QWidget *parent = nullptr);

    void setWidth();
    void setHeight();

private:
    static constexpr size_t MAX_WIDTH = 100;
    static constexpr size_t MAX_HEIGHT = 100;

    QHBoxLayout* m_layout = nullptr;
    QLineEdit* m_widthEdit = nullptr;
    QLineEdit* m_heightEdit = nullptr;
    QLabel* m_widthLabel = nullptr;
    QLabel* m_heightLabel = nullptr;
};

#endif // SIZE_SETTING_H
