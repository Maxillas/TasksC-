#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

#include <QFont>
#include <QPen>
#include <QPainter>
#include <QGraphicsScene>
#include "../../../Core/field_controller.h"

class Cell : public QGraphicsRectItem
{
public:
    Cell(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr)
        : QGraphicsRectItem(x, y, width, height, parent)
    {
        m_textItem = new QGraphicsTextItem(this);
        m_textItem->setDefaultTextColor(Qt::red);
    }

    bool isWall = false;
    bool visited = false;
    int row = -1;
    int column = -1;
    Cell* parent = nullptr;

    void setCellText(QString text) {
        m_textItem->setPlainText(text);
        updateFontSize();
        centerText();
    };

    // // Устанавливаем целевую ячейку для рисования линии
    // void setTargetCell(Cell* target) {
    //     m_targetCell = target;
    //     update(); // Обновляем отрисовку
    // }
    // void clearTargetCell() {
    //     m_targetCell = nullptr; // Удаляем ссылку на целевую ячейку
    //     update(); // Перерисовываем ячейку
    // }

protected:
    // Переопределяем метод paint для рисования линии
    // void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override {
    //     // Вызываем стандартную отрисовку QGraphicsRectItem
    //     QGraphicsRectItem::paint(painter, option, widget);

    //     // Если целевая ячейка задана, рисуем линию
    //     if (m_targetCell) {
    //         //clearLines(scene());
    //         // Получаем текущий прямоугольник ячейки
    //         QRectF cellRect = rect();
    //         // Вычисляем относительные размеры
    //         qreal lineWidth = qMax(1.0, cellRect.width() * 0.05); // Толщина линии = 5% от ширины ячейки
    //         // Координаты центра текущей ячейки
    //         QPointF start = this->mapToParent(cellRect.center());//cellRect.center();
    //         // Координаты центра целевой ячейки относительно текущей
    //         QPointF end = m_targetCell->mapToParent(m_targetCell->rect().center());


    //         // // Получаем текущий прямоугольник ячейки
    //         // QRectF cellRect = rect();
    //         // // Вычисляем относительные размеры
    //         // qreal lineWidth = cellRect.width() * 0.05; // Толщина линии = 10% от ширины ячейки

    //         // // Координаты центра текущей ячейки
    //         // QPointF start = rect().center();
    //         // // Координаты центра целевой ячейки относительно текущей
    //         // QPointF end = mapFromItem(m_targetCell, m_targetCell->rect().center());

    //         // painter->setPen(QPen(Qt::red, lineWidth)); // Красная линия толщиной 2 пикселя

    //         // //qDebug() << "startX = " << start.x() << "endX = " << end.x();
    //         // //qDebug() << "startY = " << start.y() << "endY = " << end.y();
    //         // if(start.x() < end.x()) {
    //         //     qDebug() << "THIS";
    //         //     //end.setX(end.x() / 2);
    //         //     painter->drawLine(end, start);
    //         // } else {
    //         //     painter->drawLine(start, end);
    //         // }
    //         // // Рисуем линию



    // //m_targetCell->rect().center(); //mapFromItem(this, m_targetCell->rect().center());

    //         // qDebug() << "start = " << start;
    //         // qDebug() << "end = " << end;
    //         // qDebug() << "_________________;";
    //         // Устанавливаем цвет и толщину линии

    //         // if(start.x() < end.x()) {

    //         // }

    //         // // Отладочный вывод координат
    //         // // qDebug() << "target: " << m_targetCell->row << ", " << m_targetCell->column;
    //         // // qDebug() << "this: " << this->row << ", " << this->column;

    //         // // Рисуем линию от центра текущей ячейки к центру целевой ячейки
    //         QGraphicsLineItem* lineItem = new QGraphicsLineItem(start.x(), start.y(), end.x(), end.y());

    //         // Устанавливаем стиль линии
    //         lineItem->setPen(QPen(Qt::red, 2));

    //         // Устанавливаем высокое значение ZValue
    //         lineItem->setZValue(1000);

    //         // Добавляем линию на сцену
    //         scene()->addItem(lineItem);
    //         //m_lines.append(lineItem);
    //         // painter->setPen(QPen(Qt::red, lineWidth));
    //         // painter->drawLine(start, end);

    //     }
    // }


    //CellController controller; //объект для использования сигналов

private:

    QGraphicsTextItem* m_textItem;
    //Cell* m_targetCell = nullptr; // Целевая ячейка для рисования линии


    void centerText() {
        QRectF rect = this->rect();
        QRectF textRect = m_textItem->boundingRect();
        m_textItem->setPos(rect.center() - textRect.center());
    }

    void updateFontSize() {
        QRectF rect = this->rect();
        qreal minSide = qMin(rect.width(), rect.height());
        int fontSize = static_cast<int>(minSide * 0.4);

        QFont font = m_textItem->font();
        font.setPointSize(fontSize);
        m_textItem->setFont(font);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {

        // Получаем координаты клика относительно ячейки
        QPointF clickPos = event->pos();

        // Определяем отступ (например, 5% от размера ячейки)
        qreal padding = this->boundingRect().width() * 0.1;

        // Создаем уменьшенный прямоугольник для проверки
        QRectF innerRect = this->boundingRect().adjusted(padding, padding, -padding, -padding);

        // Проверяем, что клик попал в центральную область ячейки
        if (innerRect.contains(clickPos)) {
            FieldController::getInstance().onCellClicked(this);
        }

        QGraphicsRectItem::mousePressEvent(event);
    }
};

#endif // CELL_H

