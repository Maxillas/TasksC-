#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>
//#include "../UI/blocks/field/cell.h"

class PathFinder : public QObject
{
    Q_OBJECT
public:
    PathFinder(const PathFinder&) = delete;
    PathFinder& operator=(const PathFinder&) = delete;

    static PathFinder& getInstance() {
        static PathFinder instance;
        return instance;
    }


signals:


private:
    explicit PathFinder(QObject *parent = nullptr);

};

#endif // PATHFINDER_H
