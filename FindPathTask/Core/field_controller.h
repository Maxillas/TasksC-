#ifndef FIELD_CONTROLLER_H
#define FIELD_CONTROLLER_H

#include <QObject>

#include "../UI/blocks/field/cell.h"

class FieldController : public QObject
{
    Q_OBJECT
public:
    FieldController(const FieldController&) = delete;
    FieldController& operator=(const FieldController&) = delete;

    static FieldController& getInstance() {
        static FieldController instance;
        return instance;
    }
    void setWidth(const uint16_t& newWidth);
    uint16_t getWidth() const;

    void setHeight(const uint16_t& newHeight);
    uint16_t getHeight() const;

    void setStartCell(Cell* startCell);


    void clean();

signals:
    void generateField(uint16_t width, uint16_t height);

private:
    explicit FieldController(QObject *parent = nullptr);

    uint16_t m_height;
    uint16_t m_width;

    Cell* m_startCell = nullptr;
    Cell* m_endCell = nullptr;

};

#endif // FIELD_CONTROLLER_H
