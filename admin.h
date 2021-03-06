#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QListWidgetItem>
namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0);
    ~Admin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_listWidget_2_currentTextChanged(const QString &currentText);

    void on_pushButton_8_clicked();

    void on_listWidget_3_currentTextChanged(const QString &currentText);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
