#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "circle.h"

class QGraphicsSceneMouseEvent;
class QPointF;
class QColor;

class Scene :  public QGraphicsScene
{
    Q_OBJECT
    QPen* pen;
    QBrush* brush;
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *m) override;
public:
    explicit Scene(QObject *pr = 0);
};

#endif
