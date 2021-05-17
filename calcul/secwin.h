#ifndef SECWIN_H
#define SECWIN_H

#include <QDialog>

namespace Ui {
class secwin;
}

class secwin : public QDialog
{
    Q_OBJECT

public:
    explicit secwin(QWidget *parent = nullptr);
    ~secwin();

private:
    Ui::secwin *ui;
};

#endif // SECWIN_H
