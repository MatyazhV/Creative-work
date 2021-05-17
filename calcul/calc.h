#ifndef CALC_H
#define CALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class calc; }
QT_END_NAMESPACE

class calc : public QMainWindow
{
    Q_OBJECT

public:
    calc(QWidget *parent = nullptr);
    ~calc();
private slots:
    void digit_number();
    void space();
    void mathoper();
    void on_equally_clicked();
    void set_point();
    void clean();
    void set_br1();
    void set_br2();
    void clean2();
private:
    Ui::calc *ui;
    bool point_is_entered = false;
    bool operation_is_entered = true;
    bool answered = false;
    bool space_is_entered = false;
};
#endif // CALC_H
