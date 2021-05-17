#include "secwin.h"
#include "ui_secwin.h"

secwin::secwin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secwin)
{
    ui->setupUi(this);
}

secwin::~secwin()
{
    delete ui;
}
