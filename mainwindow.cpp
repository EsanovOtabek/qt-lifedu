#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"

#include <QMessageBox>
bool LOG_IN;
QString BTN_LOG;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Session user;
//    QMessageBox::information(this,"Msg",user.echo,QMessageBox::Ok);
    LOG_IN = user.isActive();
    BTN_LOG = "KIRISH";
    LOG_IN?BTN_LOG="KIRISH":BTN_LOG="KIRISH";
    ui->btn_login->setText(BTN_LOG);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_login_clicked()
{
    if(LOG_IN){
        this->close();
        home_page.show();
    }
    else{
        login_page.show();

    }
}

void MainWindow::on_btn_about_clicked()
{
    about_page.show();
}

void MainWindow::on_btn_default_clicked()
{
    this->close();
    admin_page.show();
}
