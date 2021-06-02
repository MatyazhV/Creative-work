#define _USE_MATH_DEFINES
#include "str.h"
#include <cmath>
str::str(circle* f, circle* s, int l, QGraphicsItem* pr) : QGraphicsItem(pr)
{
    first = f;
    second = s;
    len = l;
    setFlag(QGraphicsItem::ItemIsFocusable);
}

str::str(const str& r){
    first = r.first;
    second = r.second;
    len = r.len;
    setFlag(QGraphicsItem::ItemIsFocusable);
}

QRectF str::boundingRect() const {
    return QRectF(0, 0, 30, 30);
}
void str::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    qreal fx = first->pos().x() + 25;
    qreal fy = first->pos().y() + 25;
    qreal sx = second->pos().x() + 25;
    qreal sy = second->pos().y() + 25;
    qreal angle = -atan(abs(sy - fy) / abs(sx - fx));
    if (sx - fx < 0) {
        if (sy - fy < 0) {
            angle += M_PI;
        } else {
            angle = M_PI - angle;
        }
    } else if (sy - fy < 0) {
        angle = -angle;
    }
    qreal del1, del2;del1 = 15 * sin(angle);del2 = 15 * cos(angle);
    QLineF line = QLineF(fx - del1, fy - del2, sx - del1, sy - del2);
    QLineF vector = line.unitVector();vector.setLength(20);
    QPointF point1 = vector.p2();vector.setLength(line.length() - 20);
    QPointF point2 = vector.p2();painter->drawLine(QLineF(point1, point2));vector.setLength(line.length() - 30);
    QLineF arrow_1 = QLineF(point2, vector.p2());
    QLineF arrow_2 = QLineF(point2, vector.p2());arrow_1.setAngle(arrow_1.angle() - 30);arrow_2.setAngle(arrow_2.angle() + 30);
    painter->drawLine(arrow_1);painter->drawLine(arrow_2);
    QFontMetrics fm(painter->font());
    QString ln = QString::number(len);int tw = fm.width(ln);
    qreal rotate_angle = -line.angle();
    QPointF center = line.center();
    qreal text_x = center.x() * cos(M_PI * rotate_angle / 180) + center.y() * sin(M_PI * rotate_angle / 180);
    qreal text_y = -center.x() * sin(M_PI * rotate_angle / 180) + center.y() * cos(M_PI * rotate_angle / 180);painter->rotate(rotate_angle);
    painter->drawText(text_x - tw/2, text_y - 5, ln);painter->rotate(-rotate_angle);
}
