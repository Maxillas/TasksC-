#ifndef FIELD_WRAPPER_H
#define FIELD_WRAPPER_H

#include <QWidget>
#include <QVBoxLayout>

#include "field.h"

class FieldWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit FieldWrapper(QWidget *parent = nullptr);

private:
    QVBoxLayout* m_layout = nullptr;
    Field* m_field = nullptr;
signals:
};

#endif // FIELD_WRAPPER_H
