#include "choix.h"
#include "ui_choix.h"

Choix::Choix(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Choix)
{
    ui->setupUi(this);
}

Choix::~Choix()
{
    delete ui;
}


void Choix::on_pushButton_clicked()
{
    m = new Mainwindow(this);
    m->show();

}

void Choix::on_pushButton_2_clicked()
{
    n = new Mainwindow2(this);
    n->show();
}

void Choix::on_pushButton_3_clicked()
{
    Choix::hide();

}
