#include "circle.h"

circle::circle(QGraphicsItem* pr): QGraphicsItem(pr) {
    name = "";p1 = 0;p2 = 0;
    color = QColor(rand()/255, rand()/255, rand()/255, 127);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(color);painter->drawEllipse(p1, p2, 50, 50);
    QFontMetrics fm(painter->font());
    int tw = fm.width(name);painter->drawText(p1 + 25 - tw/2, p2 + 30, name);
}
circle::circle(QString n, int x, int y, QGraphicsItem* pr) : QGraphicsItem(pr) {
    name = n;p1 = x;p2 = y;
    color = QColor(rand()/255, rand()/255, rand()/255,127);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

circle::circle(const circle& c){
    name = c.name;p1 = c.p1;p2 = c.p2;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}
QRectF circle::boundingRect() const {
    return QRectF(p1, p2, 50, 50);
}

