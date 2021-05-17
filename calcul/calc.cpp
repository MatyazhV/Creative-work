#include "calc.h"
#include "ui_calc.h"
#include <stack>
#include <math.h>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <queue>
#include <QMessageBox>
using namespace std;
calc::calc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calc)
{
    ui->setupUi(this);
    connect(ui->button0,SIGNAL(clicked()),this,SLOT(digit_number()));
    connect(ui->button1,SIGNAL(clicked()),this,SLOT(digit_number()));
    connect(ui->button2,SIGNAL(clicked()),this,SLOT(digit_number()));
    connect(ui->button3,SIGNAL(clicked()),this,SLOT(digit_number()));
    connect(ui->button4,SIGNAL(clicked()),this,SLOT(digit_number()));
    connect(ui->button5,SIGNAL(clicked()),this,SLOT(digit_number()));
    connect(ui->button6,SIGNAL(clicked()),this,SLOT(digit_number()));
    connect(ui->button7,SIGNAL(clicked()),this,SLOT(digit_number()));
    connect(ui->button8,SIGNAL(clicked()),this,SLOT(digit_number()));
    connect(ui->button9,SIGNAL(clicked()),this,SLOT(digit_number()));
    connect(ui->spaceb,SIGNAL(clicked()),this,SLOT(space()));
    connect(ui->plus,SIGNAL(clicked()),this,SLOT(mathoper()));
    connect(ui->minus,SIGNAL(clicked()),this,SLOT(mathoper()));
    connect(ui->div,SIGNAL(clicked()),this,SLOT(mathoper()));
    connect(ui->mult,SIGNAL(clicked()),this,SLOT(mathoper()));
    connect(ui->equally,SIGNAL(clicked()),this,SLOT(on_equally_clicked()));
    connect(ui->deg,SIGNAL(clicked()),this,SLOT(mathoper()));
    connect(ui->point,SIGNAL(clicked()),this,SLOT(set_point()));
    connect(ui->clear,SIGNAL(clicked()),this,SLOT(clean()));
    connect(ui->clear_2,SIGNAL(clicked()),this,SLOT(clean2()));
    connect(ui->br1,SIGNAL(clicked()),this,SLOT(set_br1()));
    connect(ui->br2,SIGNAL(clicked()),this,SLOT(set_br2()));
}

calc::~calc()
{
    delete ui;
}

deque<QString> reverse_polish_notation(QString s){
    deque<QString> result;
    stack<QString> tmp;
    tmp.push("b");
    unordered_map<string, int> d =
    {{"bb", 4}, {"b+", 1}, {"b*", 1}, {"b/", 1}, {"b(", 1}, {"b)", 5}, {"++", 2}, {"+*", 1}, {"+/", 1},
     {"+b", 2}, {"+(", 1}, {"+)", 2}, {"*b", 2}, {"*+", 2}, {"**", 2}, {"*/", 2}, {"*(", 1}, {"*)", 2},
     {"/b", 2}, {"/+", 2}, {"/*", 2}, {"//", 2}, {"/(", 1}, {"/)", 2}, {"(b", 5}, {"(+", 1}, {"(*", 1},
     {"(/", 1}, {"((", 1}, {"()", 3}, {"-b", 2}, {"-+", 2}, {"--", 2}, {"-*", 1}, {"-/", 1}, {"-(", 1},
     {"-)", 2}, {"b-", 1}, {"+-", 2}, {"*-", 2}, {"/-", 2}, {"(-", 1}};
    s.replace("(","( ");
    s.replace(")"," )");
    s.append(" b");
    auto sl = s.split(" ");
    bool stop = false;
    while (!stop){
        auto i = sl.front();
        sl.pop_front();
        bool is_number;
        i.toDouble(&is_number);
        if (is_number){
            result.push_back(i);
        }
        else{
            auto com = tmp.top();
            tmp.pop();
            auto t = d.find((com + i).toStdString());
            switch (t->second) {
            case 1:
                tmp.push(com);
                tmp.push(i);
                break;
            case 2:
                result.push_back(com);
                sl.push_front(i);
                break;
            case 4:
                stop = true;
                break;
            case 5:
                throw std::invalid_argument("Не коректный ввод");
            }
        }
    }
    return result;
}
void calc :: clean2()
{
    if(answered == false)
    {
    QString s = ui->result_show->text();
    if(s.size() != 0)
    {
    s.chop(1);
    ui->result_show->setText(s);
    if(operation_is_entered == true)
    {
        operation_is_entered = false;
    }
    else if(space_is_entered == true)
    {
        space_is_entered = false;
    }
    else if(point_is_entered == true)
        point_is_entered = false;
    }
    }
}
void calc:: clean()
{
    ui->result_show->setText("");
    point_is_entered = false;
    answered = false;
    operation_is_entered = true;
    space_is_entered = false;
}
void calc :: set_point()
{
    if(answered == false && point_is_entered == false)
    {
    QPushButton* button = (QPushButton*)sender();
    QString s = ui->result_show->text() + button->text();
    ui->result_show->setText(s);
    point_is_entered = true;
    }
}
void calc :: set_br1()
{
    if(!ui->checkBox->isChecked() && !answered)
    {
    QPushButton* button = (QPushButton*)sender();
    QString s = ui->result_show->text() + button->text();
    ui->result_show->setText(s);
    }
}
void calc :: set_br2()
{

    if(!ui->checkBox->isChecked() && !answered)
    {
    QPushButton* button = (QPushButton*)sender();
    QString s = ui->result_show->text() + button->text();
    ui->result_show->setText(s);
    }
}
void calc :: digit_number()
{
    if(answered == false)
    {
    QPushButton* button = (QPushButton*)sender();
    QString s = ui->result_show->text() + button->text();
    ui->result_show->setText(s);
    operation_is_entered = false;
    space_is_entered = false;
    }
}
void calc :: space()
{
    if(answered == false && space_is_entered == false)
    {
    QString s = ui->result_show->text() + " ";
    ui->result_show->setText(s);
    space_is_entered = true;
    point_is_entered = false;
    }
}
void calc :: mathoper()
{
    if(answered == false)
    {
    QPushButton* button = (QPushButton*)sender();
    QString s = ui->result_show->text() + button->text();
    ui->result_show->setText(s);
    operation_is_entered = true;
    }
}

void calc::on_equally_clicked()
{
    QString r = ui->result_show->text();
    if(ui->checkBox->isChecked())
    {
    if(!r.isEmpty())
    {
    if(answered == false && operation_is_entered == true)
    {
    stack<QString> tmp;
    if(space_is_entered == false)
    {
    r.replace("+"," +");
    r.replace("-"," -");
    r.replace("*"," *");
    r.replace("/"," /");
    r.replace("^"," ^");
    }

    auto sl = r.split(" ");
    int n = sl.size();
    for (int i = 0; i < n; i++){
        auto t = sl.front();
        sl.pop_front();
        bool is_number;
        t.toDouble(&is_number);
        if (is_number){
            tmp.push(t);
        }
        else{
            QString n1, n2;
            switch(t.toStdString().back()){
            case '+':
                n1 = tmp.top(); tmp.pop();
                n2 = tmp.top(); tmp.pop();
                tmp.push(QString::number(n2.toDouble()+n1.toDouble()));
                break;
            case '-':
                n1 = tmp.top(); tmp.pop();
                n2 = tmp.top(); tmp.pop();
                tmp.push(QString::number(n2.toDouble()-n1.toDouble()));
                break;
            case '*':
                n1 = tmp.top(); tmp.pop();
                n2 = tmp.top(); tmp.pop();
                tmp.push(QString::number(n2.toDouble()*n1.toDouble()));
                break;
            case '/':
                n1 = tmp.top(); tmp.pop();
                n2 = tmp.top(); tmp.pop();
                if(n1.toDouble() == 0)
                {
                    QMessageBox::critical(this,"ERROR!!!","You can't divide by zero!");
                    answered = true;
                    return;
                }
                tmp.push(QString::number(n2.toDouble()/n1.toDouble()));
                break;
            case '^':
                n1 = tmp.top(); tmp.pop();
                n2 = tmp.top(); tmp.pop();  
                tmp.push(QString::number(pow(n2.toDouble(),n1.toDouble())));
                break;
            }
        }
    }
    ui->result_show->setText(tmp.top());
    answered = true;
    }
    }
    }
    else
    {
        if(answered == false && operation_is_entered == false)
        {
        stack<QString> tmp;
        if(space_is_entered == false)
        {
        r.replace("+"," + ");
        r.replace("-"," - ");
        r.replace("*"," * ");
        r.replace("/"," / ");
        r.replace("^"," ^ ");
        }
        auto sl = reverse_polish_notation(r);
        int n = sl.size();
        for (int i = 0; i < n; i++){
            auto t = sl.front();
            sl.pop_front();
            bool is_number;
            t.toDouble(&is_number);
            if (is_number){
                tmp.push(t);
            }
            else{
                QString n1, n2;
                switch(t.toStdString().back()){
                case '+':
                    n1 = tmp.top(); tmp.pop();
                    n2 = tmp.top(); tmp.pop();
                    tmp.push(QString::number(n2.toDouble()+n1.toDouble()));
                    break;
                case '-':
                    n1 = tmp.top(); tmp.pop();
                    n2 = tmp.top(); tmp.pop();
                    tmp.push(QString::number(n2.toDouble()-n1.toDouble()));
                    break;
                case '*':
                    n1 = tmp.top(); tmp.pop();
                    n2 = tmp.top(); tmp.pop();
                    tmp.push(QString::number(n2.toDouble()*n1.toDouble()));
                    break;
                case '/':
                    n1 = tmp.top(); tmp.pop();
                    n2 = tmp.top(); tmp.pop();
                    if(n1.toDouble() == 0)
                    {
                        QMessageBox::critical(this,"ERROR!!!","You can't divide by zero!");
                        answered = true;
                        return;
                    }
                    tmp.push(QString::number(n2.toDouble()/n1.toDouble()));
                    break;
                case '^':
                    n1 = tmp.top(); tmp.pop();
                    n2 = tmp.top(); tmp.pop();
                    tmp.push(QString::number(pow(n2.toDouble(),n1.toDouble())));
                    break;
                }
            }
        }
        ui->result_show->setText(tmp.top());
        answered = true;
        }
    }
}
