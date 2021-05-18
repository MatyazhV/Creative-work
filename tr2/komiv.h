#ifndef KOMIV_H
#define KOMIV_H
#include <QMainWindow>
#include "city.h"
#include <QGraphicsView>
#include <vector>
#include "road.h"
#include "mygraph.h"
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
    city* s;
    vector<city*> cit;
    vector<vector<double>> res;
public:
    myGraphicsScene* scene;
    vector<city*> cities;
    vector<vector<double>> result;
};
#endif // KOMIV_H
