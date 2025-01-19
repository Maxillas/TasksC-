#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QBrush>
#include <QFont>
#include "../../../Core/cell_controller.h"
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

    //CellController controller; //объект для использования сигналов

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
        int fontSize = static_cast<int>(minSide * 0.5);

        QFont font = m_textItem->font();
        font.setPointSize(fontSize);
        m_textItem->setFont(font);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        //emit controller.onCellPressed();
        FieldController::getInstance().onCellClicked(this);
        qDebug() << "Mouse pressed on CustomRectItem at:" << row << ".." << column;
        // qDebug() << "isWall = " << isWall;
        //setCellText("2");

        //setBrush(QBrush(Qt::black));
        QGraphicsRectItem::mousePressEvent(event);
    }
};

#endif // CELL_H

