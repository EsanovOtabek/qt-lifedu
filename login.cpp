#include "login.h"
#include "ui_login.h"
#include "db.h"
#include <QMessageBox>
#include <map>
#include "mainwindow.h"
using namespace std;
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_buttonBox_accepted()
{
    DBHelper helper;
    QString email=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();

    QString sql="SELECT * FROM users WHERE email='"+email+"' AND password='"+password+"'";
    int k=helper.count(sql);
    if(k>0){
        map <int,map <QString,QString> > mp;
        helper.select(sql,mp,"users");
        Session user;
        user.id=mp[0]["id"];
        user.fio=mp[0]["fio"];
        user.email=mp[0]["email"];
        if(user.login()){
            QMessageBox::information(this,"ok",mp[0]["fio"]+" Tizimga kirdingiz!",QMessageBox::Ok);
            MainWindow w;
            w.close();
            w.show();
        }
        else
            QMessageBox::critical(this,"error","Tizimga kirishda xa'tolik",QMessageBox::Ok);

    }else{
        QMessageBox::critical(this,"error","Login yoki Parol xato",QMessageBox::Ok);
    }
}
