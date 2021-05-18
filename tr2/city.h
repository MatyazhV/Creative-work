#ifndef CITY_H
#define CITY_H

#include <QGraphicsItem>
#include <string>
#include <vector>
#include <QPainter>

class city : public QGraphicsItem
{
public:
    city(QGraphicsItem* parent = nullptr);
    city(QString, int, int, QGraphicsItem* parent = nullptr);
    city(const city&);
    QString name;
    friend bool operator== (const city&, const city&);
private:
    int pos_x;
    int pos_y;
    QColor color;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};

#endif // CITY_H
