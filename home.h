#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include "kurs.h"
#include <QListWidgetItem>
#include "dars.h"
#include <QString>
namespace Ui {
class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT

public:

    explicit Home(QWidget *parent = 0);
    ~Home();

private slots:
    void on_pushButton_4_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_listWidget_2_currentTextChanged(const QString &currentText);

    void on_pushButton_9_clicked();

    void on_listWidget_3_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Home *ui;
    Kurs kurs_oyna;
    Dars dars_oyna;
};

#endif // HOME_H
