#ifndef KOMIV_H
#define KOMIV_H
#include <QMainWindow>
#include "circle.h"
#include <QGraphicsView>
#include <vector>
#include "str.h"
#include "view.h"
#include <QKeyEvent>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class komiv; }
QT_END_NAMESPACE

class komiv : public QMainWindow
{
    Q_OBJECT

public:
    komiv(QWidget *parent = nullptr);
    ~komiv();
public slots:
    void calculate();
    void add_city();
    void create();
    void deletec();
private:
    Ui::komiv *ui;
public:
    Scene* sc;
    vector<circle*> circles;
    vector<vector<int>> result;
};
#endif
