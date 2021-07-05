#include "dars.h"
#include "ui_dars.h"
#include "home.h"
#include <QFile>
#include <QTextStream>
#include "db.h"
#include <map>
#include <QWebElement>
#include <QWebFrame>

using namespace std;

Dars::Dars(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dars)
{
    ui->setupUi(this);
    QString fileName = "C:\\Users\\beoo\\Documents\\LifeduTest\\assets\\lesson.txt";
    QFile file(fileName);
    QTextStream in(&file);
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
       line= in.readLine();
    }


    DBHelper helper;
    map <int, map<QString,QString> > mp;
    helper.select(line,mp,"lessons");


    ui->label->setText(mp[0]["title"]);
    ui->textEdit->setText(mp[0]["content"]);

    QString video = mp[0]["video"];

    ui->webView->setHtml(video);

}

Dars::~Dars()
{
    delete ui;
}
