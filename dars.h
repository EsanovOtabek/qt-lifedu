#ifndef DARS_H
#define DARS_H

#include <QWidget>

namespace Ui {
class Dars;
}

class Dars : public QWidget
{
    Q_OBJECT

public:
    explicit Dars(QWidget *parent = 0);
    ~Dars();

private:
    Ui::Dars *ui;
};

#endif // DARS_H
