#ifndef FIELD_CONTROLLER_H
#define FIELD_CONTROLLER_H

#include <QObject>

class FieldController : public QObject
{
    Q_OBJECT
public:
    explicit FieldController(QObject *parent = nullptr);

signals:
};

#endif // FIELD_CONTROLLER_H
