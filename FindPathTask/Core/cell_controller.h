#ifndef CELL_CONTROLLER_H
#define CELL_CONTROLLER_H

#include <QObject>

class CellController : public QObject
{
    Q_OBJECT

signals:
    void onCellPressed();
};

#endif // CELL_CONTROLLER_H
