#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>

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
    void print();

    void setWidth(const uint16_t& newWidth);
    uint16_t getWidth() const;

    void setHeight(const uint16_t& newHeight);
    uint16_t getHeight() const;

signals:
    void generateField(uint16_t width, uint16_t height,
                       uint16_t cellSize);

private:
    explicit PathFinder(QObject *parent = nullptr);

    uint16_t m_height;
    uint16_t m_width;

signals:
};

#endif // PATHFINDER_H
