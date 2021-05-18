#include "city.h"

city::city(QGraphicsItem* parent): QGraphicsItem(parent) {
    name = "";
    pos_x = 0;
    pos_y = 0;
    color = QColor(rand()/255, rand()/255, rand()/255, 127);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

city::city(QString n, int x, int y, QGraphicsItem* parent) : QGraphicsItem(parent) {
    name = n;
    pos_x = x;
    pos_y = y;
    color = QColor(rand()/255, rand()/255, rand()/255,127);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

city::city(const city& c){
    name = c.name;
    pos_x = c.pos_x;
    pos_y = c.pos_y;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

QRectF city::boundingRect() const {
    return QRectF(pos_x, pos_y, 50, 50);
}

void city::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(color);
    painter->drawEllipse(pos_x, pos_y, 50, 50);
    QFontMetrics fm(painter->font());
    int tw = fm.width(name);
    painter->drawText(pos_x + 25 - tw/2, pos_y + 30, name);
}

bool operator== (const city &c1, const city &c2) {
    return c1.name == c2.name;
}
