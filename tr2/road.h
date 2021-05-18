#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsItem>
#include "city.h"

class road : public QGraphicsItem
{
public:
    road(city*, city*, double, QGraphicsItem* parent = nullptr);
    road(const road&);
    city* first_city;
    city* second_city;
    double length;
    friend bool operator== (const road&, const road&);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    QString double_to_str(double);
};

#endif // ROAD_H
