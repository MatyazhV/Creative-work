#ifndef CIRCLE_H
#define CIRCLE_H
#include <QGraphicsItem>
#include <string>
#include <vector>
#include <QPainter>
class circle : public QGraphicsItem
{
    int p1;
    int p2;
    QColor color;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
public:
    circle(QGraphicsItem* pr = nullptr);
    circle(QString, int, int, QGraphicsItem* pr = nullptr);
    circle(const circle&);
    QString name;

};

#endif
