#ifndef LEFT_SIDE_H
#define LEFT_SIDE_H

#include "blocks/size_setting.h"
#include "blocks/field_wrapper.h"

#include <QWidget>

class LeftSide : public QWidget
{
    Q_OBJECT
public:
    explicit LeftSide(QWidget *parent = nullptr);

private:
    QVBoxLayout* m_layout = nullptr;
    FieldWrapper* m_fieldWrapper = nullptr;
    SizeSetting* m_sizeSetting = nullptr;
};

#endif // LEFT_SIDE_H
