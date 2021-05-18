#include "komiv.h"
#include "road.h"
#include "ui_komiv.h"
#include <vector>
using namespace std;
komiv::komiv(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::komiv)
{
    ui->setupUi(this);
    scene = new myGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    connect(ui->addcityButton, &QPushButton::released, this, &komiv::add_city);
    connect(ui->addroadButton, &QPushButton::released, this, &komiv::deletec);
    connect(ui->calc,SIGNAL(clicked()),this,SLOT(calculate()));
    connect(ui->create,SIGNAL(clicked()),this,SLOT(create()));
}

void komiv::add_city() {
    if(!result.empty())
    {
    int k = cities.size() - 1;
    QString q = QString::number((cities[k]->name).toInt() + 1);
    city *new_city = new city(q, 0, 0);
    for (auto i : cities){
        if (*new_city == *i) {
            delete new_city;
            return;
        }
    }
    cities.push_back(new_city);
    scene->addItem(new_city);
    scene->QGraphicsScene::update();
    vector<double>t;
    for (int j = 0; j < result.size() + 1; j++)
        {
         if (result.size() == j)
              t.push_back(-1);
         else
             {
              int in;
              in = rand()/1000 + 1;
              t.push_back(in);
             }
        }
    result.push_back(t);
    for (int j = 0; j < result.size()-1; j++)
    {
        int in;
        in = rand()/1000 + 1;
        result[j].push_back(in);
    }
    k = cities.size() - 1;
    city* k1 =cities[k];
    int q1 = (cities[k]->name).toInt();
    for(int j = 0;j<cities.size();j++)
    {
        if(k!=j)
        {
    city* kj = cities[j];
    int qj = (cities[j]->name).toInt();
    double sj = result[q1 - 1][qj - 1];
    road* new_road = new road(k1, kj, sj);
    scene->addItem(new_road);
    ui->statusbar->clearMessage();
    scene->QGraphicsScene::update();
        }
    }
    for(int j = 0;j<cities.size();j++)
    {
        if(k!=j)
        {
    city* kj = cities[j];
    int qj = (cities[j]->name).toInt();
    double sj = result[qj - 1][q1 - 1];
    road* new_road = new road(kj, k1, sj);
    scene->addItem(new_road);
    ui->statusbar->clearMessage();
    scene->QGraphicsScene::update();
        }
    }
    }
}

void komiv::deletec() {
    scene -> clear();
    scene->QGraphicsScene::update();
    cities.clear();
    result.clear();
}

struct Edge
{
    int from;
    int to;
};

void reductCol(vector<vector<double>>& matrix) {
      for (int i = 0; i < matrix.size(); i++) {
           int min = INT_MAX;
          for (int j = 0; j < matrix[0].size(); j++) {
                if (min > matrix[i][j] && matrix[i][j] >= 0)
                     min = matrix[i][j];
          }
           if (min != INT_MAX) {
               for (int j = 0; j < matrix[0].size(); j++) {
                   if (matrix[i][j] >= 0)
                  matrix[i][j] -= min;
               }
           }
      }
}
void reductRow(vector<vector<double>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        int min = INT_MAX;
        for (int j = 0; j < matrix[0].size(); j++) {
            if (min > matrix[j][i] && matrix[j][i] >= 0)
                min = matrix[j][i];
        }
        if (min != INT_MAX) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[j][i] >= 0)
                    matrix[j][i] -= min;
            }
        }
    }
}
int findMinCol(vector<vector<double>>& matrix, int i, int j)
{
    int min = 100000;
    for (int k = 0; k < matrix.size(); k++)
    {
        if (min > matrix[i][k] && matrix[i][k]>=0 && k != j)
        {
            min = matrix[i][k];
        }
    }
    return min;
}
int findMinRow(vector<vector<double>>& matrix, int i, int j)
{
    int min = 100000;
    for (int k = 0; k < matrix.size(); k++)
    {
        if (min > matrix[k][j] && matrix[k][j] >= 0 && k != i)
        {
            min = matrix[k][j];
        }
    }
    return min;
}
Edge FindEdge(vector<vector<double>>& matrix) {
    int max = -1;
    Edge edge{ 0, 0 };

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == 0) {
                int t = findMinCol(matrix, i,j) + findMinRow(matrix, i,j);
                if (t > max) {
                    max = t;
                    edge.from = i;
                    edge.to = j;
                }
            }
        }
    }
    matrix[edge.to][edge.from] = -1;
    for (int i = 0; i < matrix.size(); i++) {
        matrix[edge.from][i] = -1;
        matrix[i][edge.to] = -1;
    }
    return edge;
}
int getLength(vector<vector<double>> matrix, vector<Edge> solution) {
     int len = 0;
      Edge current = solution[0];
      int count = 0;
      while (count < solution.size()) {
           for (int i = 0; i < solution.size(); i++) {
                Edge next = solution[i];
                if (current.to == next.from) {
                     count++;
                     len += matrix[current.from][current.to];
                     current = next;
                   break;
                }
           }
      }
      return len;
}
void komiv :: create()
{
    ui->statusbar->showMessage("Введите кол-во городов");
    int n = ui->city->text().toInt();
    if(n!=0)
    {
       ui->statusbar->clearMessage();
       ui->city->clear();
       for (int i = 0; i < n; i++)
           {
           city *new_city = new city(QString::number(i + 1), 0, i);
           for (auto i : cities){
               if (*new_city == *i) {
                   delete new_city;
                   return;
               }
           }
           cities.push_back(new_city);
           scene->addItem(new_city);
           scene->QGraphicsScene::update();
            vector<double> t;
            for (int j = 0; j < n; j++)
                {
                 if (i == j)
                      t.push_back(-1);
                 else
                     {
                      int in;
                      in = rand()/1000 + 1;
                      t.push_back(in);
                     }
                }
            result.push_back(t);
           }
 for(int i = 0;i<cities.size();i++)
 {
    city* k1 =cities[i];
    int q1 = (cities[i]->name).toInt();
    for(int j = 0;j<cities.size();j++)
    {
        if(i!=j)
        {
    city* kj = cities[j];
    int qj = (cities[j]->name).toInt();
    double sj = result[q1 - 1][qj - 1];
    road* new_road = new road(k1, kj, sj);
    scene->addItem(new_road);
    ui->statusbar->clearMessage();
    scene->QGraphicsScene::update();
        }
    }
 }
    }
}
QString getSolutionPath(vector<Edge> solution) {
     QString result = "";
        Edge current = solution[0];
        result += QString::number(current.from + 1) + "->" + QString::number(current.to + 1);
      int count = 0;
      while (count < solution.size()) {
           for (int i = 0; i < solution.size(); i++) {
                Edge next = solution[i];
                if (current.to == next.from) {
                     count++;
                         result += "->" + QString::number(next.to + 1);
                current = next;
                     break;
            }

        }

    }
      if(solution.size() > 4)
     result.chop(3);
      else
      {
        QString  r = result.right(result.size() - 3);
        result = r;
      }
     return result;

}
void komiv :: calculate()
{
    if(!result.empty())
    {
 vector<vector<double>> matrix = result;
 vector<Edge> r;
      int i = 0;
      while (i != matrix.size()) {
      reductCol(matrix);
      reductRow(matrix);
      r.push_back(FindEdge(matrix));
      i++;
      }
  int sum = getLength(result, r);
  ui->ss->setText(getSolutionPath(r));
  ui->label->setText(QString::number(sum));
    }
}
komiv::~komiv()
{
    delete ui;
}

