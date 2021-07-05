#include "about.h"
#include "ui_about.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
About::About(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

//    QString filename = "D:/beoo/Esanov_Otabek/MyPortfolio/WEBSITES%20FRONTEND/portfolio%20website%20--%20MyBlog%20--/index.html";
//    QFile file(filename);


//    if (!file.open(QIODevice::ReadOnly)) {
//        QMessageBox::information(this, tr("Unable to open file"),
//            file.errorString());
//        return;
//    }

//    QTextStream out(&file);
//    QString output = out.readAll();

//    ui->webView->setHtml(output, QUrl::fromLocalFile(filename));
}

About::~About()
{
    delete ui;
}
