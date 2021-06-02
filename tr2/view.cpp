#include "view.h"

Scene::Scene(QObject *pr) : QGraphicsScene(pr){
    pen = new QPen(Qt::red);
    brush = new QBrush(Qt::red);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *m) {
    QGraphicsScene::update();
    QGraphicsScene::mouseMoveEvent(m);
}

