#include "home.h"
#include "ui_home.h"
#include "db.h"
#include <QMessageBox>
#include <QListWidget>
#include <map>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QTextStream>

using namespace std;

map <int, map<QString,QString> > mp;
map <int, map<QString,QString> > mpu;

Home::Home(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);


    Session user;
    if(user.isActive()){
        ui->label_fio->setText(user.fio+" nomi bilan tizimga kirdingiz.");
        ui->frame_6->hide();
    }

    QString sql="SELECT * FROM courses";

    DBHelper helper;
    helper.select(sql,mp,"courses");
    int row_count=mp.size();
    for(int i=0; i<row_count; i++){
        ui->listWidget->addItem(mp[i]["name"]);
    }




}

Home::~Home()
{
    delete ui;
}

//chiqish
void Home::on_pushButton_4_clicked()
{
    Session user;
    if(user.isActive()){
        QMessageBox msg;
        msg.setWindowTitle("Chiqish");
        msg.setText("Dasturdan chiqishni xohlaysizmi?");
        msg.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        int ret=msg.exec();
        switch(ret){
            case QMessageBox::Ok:
                user.logout();
                this->close();
                break;
            case QMessageBox::Cancel:
                msg.hide();
                break;
        }

    }

}

// kurslar listidan tanlaganda u haqida qisqacha ma'lumot chiqadi
void Home::on_listWidget_currentRowChanged(int currentRow)
{
    ui->frame_6->show();
    ui->label_kurs_name->setText(mp[currentRow]["name"]);
    ui->label_kurs_title->setText(mp[currentRow]["title"]);
    QPixmap image(mp[currentRow]["image"]);
    ui->label_8->setPixmap(image);

}
// kurslar sahifasini ochadi
void Home::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Mening kurslarim sahifasini ochadi
void Home::on_pushButton_2_clicked()
{
    ui->listWidget_2->clear();
    map <int, map<QString,QString> > mpu;

    Session user;
    user.isActive();
    QString sql1="SELECT * FROM user_courses WHERE user_id="+user.id;
    ui->stackedWidget->setCurrentIndex(1);
    DBHelper helper;
    helper.select(sql1,mpu,"user_courses");

    for(int i=0;i<mpu.size();i++){
        ui->listWidget_2->addItem(mp[mpu[i]["course_id"].toInt()-1]["name"]);
    }
}

//Help oynasini ochadi
void Home::on_pushButton_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://t.me/beootabek"));
}

void Home::on_pushButton_5_clicked()
{
    int row = ui->listWidget->currentRow();
    kurs_oyna.show();
}

void Home::on_pushButton_6_clicked()
{
    int row = ui->listWidget->currentRow();

    QMessageBox msg;
    msg.setWindowTitle("Olish");
    msg.setText(mp[row]["name"]+" kursini olmoqchimisiz?");
    msg.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    int ret=msg.exec();
    switch(ret){
        case QMessageBox::Ok:{
            QString T=QDateTime::currentDateTime().toString("d.MM.yyyy hh:mm:ss");
            Session user;
            user.isActive();
            QString sql="INSERT INTO user_courses (user_id,course_id,vaqt) VALUES("+user.id+","+mp[row]["id"]+",'"+T+"')";
            DBHelper helper;
            if(helper.inupde(sql)){
                QMessageBox::information(this,"OK","Kurs qo'shildi!",QMessageBox::Ok);
            }
            else{
                QMessageBox::information(this,"err","Xatolik ro'y berdi!",QMessageBox::Ok);
            }


            break;
        }
        case QMessageBox::Cancel:
            msg.hide();
            break;
    }
}

//kursni o'chirish
void Home::on_pushButton_8_clicked()
{
    QMessageBox msg;
    msg.setWindowTitle("O'chirish");
    msg.setText("Kursni o'chirmoqchimisiz?");
    msg.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    int ret=msg.exec();

    switch(ret){
        case QMessageBox::Ok:{
            Session user;
            QString id;
            if(user.isActive()) id=user.id;

            map <int, map<QString,QString> > mptest;
            QString row = ui->listWidget_2->currentItem()->text();

            DBHelper helper;
            helper.select("SELECT * FROM courses WHERE name='"+row+"'",mptest,"courses");

            if(helper.inupde("DELETE FROM user_courses WHERE user_id="+id+" AND course_id="+mptest[0]["id"])){
                QMessageBox::information(this,"OK","Kurs o'chirildi!",QMessageBox::Ok);
                QListWidgetItem *it = ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
                delete it;
            }
            else{
                QMessageBox::information(this,"err","Xatolik ro'y berdi!",QMessageBox::Ok);
            }

            break;
        }
        case QMessageBox::Cancel:
            msg.hide();
            break;
    }

}

void Home::on_listWidget_2_currentTextChanged(const QString &currentText)
{
    ui->listWidget_3->clear();
    map <int, map<QString,QString> > mptest;
    DBHelper helper;
    helper.select("SELECT * FROM courses WHERE name='"+currentText+"'",mptest,"courses");
    QString course_id=mptest[0]["id"];

    map <int, map<QString,QString> > mpdars;
    helper.select("SELECT * FROM lessons WHERE course_id="+course_id,mpdars,"lessons");
//     ui->listWidget_3->addItem(course_id);
    for(int i=0;i<mpdars.size();i++){
        ui->listWidget_3->addItem(mpdars[i]["title"]);
    }
}

void Home::on_pushButton_9_clicked()
{
    QString lnedit=ui->lineEdit->text().trimmed();
    if(lnedit.size()>0){
        ui->listWidget_3->clear();

//        SELECT * FROM Customers WHERE CustomerName LIKE '%or%';
        map <int, map<QString,QString> > mptest;
        DBHelper helper;
        helper.select("SELECT * FROM courses WHERE name='"+ui->listWidget_2->currentItem()->text()+"'",mptest,"courses");
        QString course_id=mptest[0]["id"];

        map <int, map<QString,QString> > mpdars;
        QString sql="SELECT * FROM lessons WHERE course_id="+course_id+"AND title LIKE '%"+lnedit+"%";

        ui->listWidget_3->addItem(sql);
//        helper.select(sql,mpdars,"lessons");
    //     ui->listWidget_3->addItem(course_id);
        for(int i=0;i<mpdars.size();i++){
            ui->listWidget_3->addItem(sql);
        }
    }
}









void Home::on_listWidget_3_itemDoubleClicked(QListWidgetItem *item)
{
    QString fan=ui->listWidget_2->currentItem()->text();
    map <int, map<QString,QString> > mptest;
    DBHelper helper;
    helper.select("SELECT * FROM courses WHERE name='"+fan+"'",mptest,"courses");
    QString course_id=mptest[0]["id"];
    QString dars=item->text();


    QString filename = "C:\\Users\\beoo\\Documents\\LifeduTest\\assets\\lesson.txt";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "SELECT * FROM lessons WHERE course_id="+course_id+" AND title='"+dars+"'";
    }
    dars_oyna.show();
}
