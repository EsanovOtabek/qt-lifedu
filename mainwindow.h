#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "home.h"
#include "about.h"
#include "admin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btn_login_clicked();

    void on_btn_about_clicked();

    void on_btn_default_clicked();

private:
    Ui::MainWindow *ui;
    Login login_page;
    Home home_page;
    About about_page;
    Admin admin_page;
};

#endif // MAINWINDOW_H
