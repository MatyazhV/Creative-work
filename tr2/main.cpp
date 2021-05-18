#include "komiv.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    komiv w;
    w.show();
    return a.exec();
}
