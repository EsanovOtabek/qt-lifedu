#include "kurs.h"
#include "ui_kurs.h"

Kurs::Kurs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kurs)
{
    ui->setupUi(this);
}

Kurs::~Kurs()
{
    delete ui;
}

void Kurs::on_pushButton_clicked()
{

}
