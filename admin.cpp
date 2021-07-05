#include "admin.h"
#include "ui_admin.h"
#include "db.h"
#include <map>
#include <QMessageBox>


using namespace std;

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    ui->frame_7->hide();

    map <int, map<QString,QString> > mp;
    DBHelper helper;
    QString sql="SELECT * FROM users";
    helper.select(sql,mp,"users");
    for(int i=0; i<mp.size(); i++){
        ui->listWidget->addItem(mp[i]["fio"]);
    }

    map <int, map<QString,QString> > mp2;

    sql="SELECT * FROM courses";
    helper.select(sql,mp2,"courses");
    for(int i=0; i<mp2.size(); i++){
        ui->listWidget_2->addItem(mp2[i]["name"]);
        ui->listWidget_3->addItem(mp2[i]["name"]);
    }
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Admin::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Admin::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Admin::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void Admin::on_pushButton_5_clicked()
{
    QString fio=ui->lineEdit_2->text().trimmed();
    QString email=ui->lineEdit_3->text().trimmed();
    QString parol=ui->lineEdit_4->text().trimmed();

    if(fio.size()>0&&email.size()>0&&parol.size()){
        DBHelper db;
        QString sql="INSERT INTO users (fio,email,password) VALUES ('"+fio+"','"+email+"','"+parol+"')";
        if(db.inupde(sql)){
            QMessageBox::information(this,"ok","Foydalanuvchi qo'shildi",QMessageBox::Ok);
            ui->listWidget->addItem(fio);
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
        }
        else{
             QMessageBox::warning(this,"err","Xa'tolik",QMessageBox::Ok);
        }

    }

}

void Admin::on_pushButton_6_clicked()
{
    QString fan=ui->listWidget_2->currentItem()->text();
    map <int, map<QString,QString> > mptest;
    DBHelper helper;
    helper.select("SELECT * FROM courses WHERE name='"+fan+"'",mptest,"courses");
    QString course_id=mptest[0]["id"];
    QString title=ui->lineEdit_5->text().trimmed();
    QString video=ui->lineEdit_6->text().trimmed();
    QString content=ui->textEdit->document()->toPlainText();
    content=content.toHtmlEscaped();
    if(title.size()>0&&video.size()>0&&content.size()){
        DBHelper db;
        QString sql="INSERT INTO lessons (course_id,title,content,video) VALUES ('"+course_id+"','"+title+"','"+content+"','"+video+"')";
        if(db.inupde(sql)){
            QMessageBox::information(this,"ok",mptest[0]["name"]+" kursiga dars qo'shildi",QMessageBox::Ok);
            ui->lineEdit_5->clear();
            ui->lineEdit_6->clear();
            ui->textEdit->clear();

        }
        else{
             QMessageBox::warning(this,"err","Xa'tolik",QMessageBox::Ok);
        }
    }
}

void Admin::on_pushButton_7_clicked()
{
    QString name=ui->lineEdit_8->text().trimmed();
    QString title=ui->lineEdit_9->text().trimmed();
    QString image=ui->lineEdit_10->text().trimmed();

    if(name.size()>0&&title.size()>0&&image.size()){
        DBHelper db;
        QString sql="INSERT INTO courses (name,title,image) VALUES ('"+name+"','"+title+"','"+image+"')";
        if(db.inupde(sql)){
            QMessageBox::information(this,"ok","Kurs qo'shildi",QMessageBox::Ok);
            ui->listWidget_2->addItem(name);
            ui->lineEdit_8->clear();
            ui->lineEdit_9->clear();
            ui->lineEdit_10->clear();
        }
        else{
             QMessageBox::warning(this,"err","Xa'tolik",QMessageBox::Ok);
        }
    }


}

void Admin::on_listWidget_2_currentTextChanged(const QString &currentText)
{
    ui->frame_7->show();
    ui->label_5->setText(currentText+" kursiga dars qo'shish");
}


void Admin::on_listWidget_3_currentTextChanged(const QString &currentText)
{
    ui->listWidget_4->clear();
    map <int, map<QString,QString> > mptest;
    map <int, map<QString,QString> > mp;

    DBHelper helper;

    helper.select("SELECT * FROM courses WHERE name='"+currentText+"'",mptest,"courses");
    QString course_id=mptest[0]["id"];

    helper.select("SELECT * FROM lessons WHERE course_id="+course_id,mp,"lessons");

    for(int i=0;i<mp.size();i++){
        ui->listWidget_4->addItem(mp[i]["title"]);
    }

}

void Admin::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    DBHelper helper;
    QString user=item->text();
    map <int, map<QString,QString> > mp;
    QString sql="SELECT * FROM users WHERE fio='"+user+"'";
    helper.select(sql,mp,"users");
    QMessageBox::information(this,"user","fio: "+user+"\nEmail: "+mp[0]["email"]+"\Password: "+mp[0]["password"],QMessageBox::Ok);

}
