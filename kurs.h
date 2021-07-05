#ifndef KURS_H
#define KURS_H

#include <QWidget>

namespace Ui {
class Kurs;
}

class Kurs : public QWidget
{
    Q_OBJECT

public:
    explicit Kurs(QWidget *parent = 0);
    ~Kurs();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Kurs *ui;
};

#endif // KURS_H
