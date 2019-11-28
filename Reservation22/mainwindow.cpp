#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "place.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QDesktopServices>
#include <QStatusBar>
Mainwindow::Mainwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::on_pb_ajouter_clicked()
{   QFile file("maillist.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    QMessageBox::warning(this,"title","file not open");
    int id = ui->lineEdit_id->text().toInt();
    int cin = ui->lineEdit_cin->text().toInt();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString email= ui->lineEdit_email->text();
    int nbplace = ui->lineEdit_nbp->text().toInt();
    int nbres = ui->lineEdit_nbr->text().toInt();
    QString td=ui->edit_td->text();
  Place p(id,cin,nom,prenom,email,nbplace,nbres,td);
  bool test=p.ajouter();
  if(test)
{ui->tabplace->setModel(tmp.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter place"),
                  QObject::tr("place ajoutée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

QTextStream out(&file);
QString text = ui->lineEdit_email->text();
out << text;
file.flush();
file.close();
ui->lineEdit_id->clear();
ui->lineEdit_cin->clear();
ui->lineEdit_nom->clear();
ui->lineEdit_prenom->clear();
ui->lineEdit_email->clear();
ui->lineEdit_nbp->clear();
ui->lineEdit_nbr->clear();
ui->edit_td->clear();


}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter place"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void Mainwindow::on_pb_modifier_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    int cin = ui->lineEdit_cin->text().toInt();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString email= ui->lineEdit_email->text();
    int nbplace = ui->lineEdit_nbp->text().toInt();
    int nbres = ui->lineEdit_nbr->text().toInt();
    QString td=ui->edit_td->text();

  Place p(id,cin,nom,prenom,email,nbplace,nbres,td);
  bool test=p.modifier(id);
  if(test)
{ui->tabplace->setModel(tmp.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("modifier place"),
                  QObject::tr("place modifiée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
ui->lineEdit_id->clear();
ui->lineEdit_cin->clear();
ui->lineEdit_nom->clear();
ui->lineEdit_prenom->clear();
ui->lineEdit_email->clear();
ui->lineEdit_nbp->clear();
ui->lineEdit_nbr->clear();
ui->edit_td->clear();


}
  else

      QMessageBox::critical(nullptr, QObject::tr("modifier place"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}



void Mainwindow::on_pb_supprimer_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    bool test=tmp.supprimer(id);
    if(test)
    {ui->tabplace->setModel(tmp.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer place"),
                    QObject::tr("place supprimée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer place"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Mainwindow::on_pb_show_clicked()
{
    ui->tabplace->setModel(tmp.afficher());
}

void Mainwindow::on_tabplace_activated(const QModelIndex &index)
{
    QString valeur=ui->tabplace->model()->data(index).toString();
    QSqlQuery query;

    query.prepare(" select * from place WHERE ID=: valeur  ");
 if (query.exec())
 {  while (query.next())
     {


    ui->lineEdit_id->setText(query.value(0).toString());
    /*ui->lineEdit_cin->setText(query.value(1).toString());
    ui->lineEdit_nom->setText(query.value(2).toString());
    ui->lineEdit_prenom->setText(query.value(3).toString());
    ui->lineEdit_email->setText(query.value(4).toString());
    ui->lineEdit_nbp->setText(query.value(5).toString());
    ui->lineEdit_nbr->setText(query.value(6).toString());*/
     }
 }
 else
 {
     QMessageBox::critical(nullptr, QObject::tr("Supprimer un étudiant"),
                 QObject::tr("Erreur !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
 }

}

void Mainwindow::on_pushButton_4_clicked()
{
      QDesktopServices::openUrl(QUrl("https://mail.google.com/mail/u/0/#inbox?compose=new", QUrl::TolerantMode));
}

void Mainwindow::on_pushButton_3_clicked()
{
    ui->tabplace->setModel(tmp.afficherf());

}

void Mainwindow::on_pushButton_2_clicked()
{
    QSqlQueryModel * model=tmp.trier();
       ui->tabplace->setModel(model);
   }

   QSqlQueryModel * Place::trier()
   {QSqlQueryModel * model= new QSqlQueryModel();

   model->setQuery("select * from place order by id asc;");


   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("NBP"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("NBR"));
   model->setHeaderData(7, Qt::Horizontal, QObject::tr("TD"));

   return model;
}

void Mainwindow::on_pb_retour_clicked()
{
    Mainwindow::hide();
}
