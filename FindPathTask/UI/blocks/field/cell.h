#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
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

    void setCellText(const QString& text) {
        m_textItem->setPlainText(text);
        updateFontSize();
        centerText();
    };

private:
    QGraphicsTextItem* m_textItem;

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
        //уменьшаем область клика для того, чтобы не срабатывало на границе
        QPointF clickPos = event->pos();
        qreal padding = this->boundingRect().width() * 0.1;
        QRectF innerRect = this->boundingRect().adjusted(padding, padding, -padding, -padding);

        if (innerRect.contains(clickPos)) {
            FieldController::getInstance().onCellClicked(this);
        }

        QGraphicsRectItem::mousePressEvent(event);
    }
};

#endif // CELL_H

