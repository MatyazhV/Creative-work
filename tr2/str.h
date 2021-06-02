#ifndef STR_H
#define STR_H

#include <QGraphicsItem>
#include "circle.h"

class str : public QGraphicsItem
{
public:
    str(circle*, circle*, int, QGraphicsItem* pr = nullptr);
    str(const str&);
    circle* first;
    circle* second;
    int len;
protected:
    void paint(QPainter *pr, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};

#endif
