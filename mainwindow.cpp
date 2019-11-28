#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reseau.h"
#include <QMessageBox>
#include <QString>
#include "smtp.h"
#include "station.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);
ui->tabreseau->setModel(tmpreseau.afficher());
ui->tabstation->setModel(tmpstation.afficher());
ui->stackedWidget_2->setCurrentIndex(0);
ui->stackedWidget->setCurrentIndex(1);


connect(ui->send, SIGNAL(clicked()),this, SLOT(sendMail()));
connect(ui->sends, SIGNAL(clicked()),this, SLOT(sendMailstation()));

}





MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{ QString trajet= ui->lineEdit_trajet->text();
    int duree = ui->lineEdit_duree->text().toInt();
     int distance= ui->lineEdit_distance->text().toInt();
      int id = ui->lineEdit_id->text().toInt();

  reseau e(trajet,duree,distance,id);
  bool test=e.ajouter();
  if(test)
{ui->tabreseau->setModel(tmpreseau.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un reseau"),
                  QObject::tr("reseau ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un reseau"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_supprimer_clicked()
{
 int id = ui->lineEdit_id_2->text().toInt();
bool test=tmpreseau.supprimer(id);
if(test)
{ui->tabreseau->setModel(tmpreseau.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un reseau"),
                QObject::tr("reseau supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un reseau"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}
void MainWindow::on_modifier_clicked()
{
    int id = ui->line1->text().toInt();

    int duree = ui->line3->text().toInt();
    QString trajet= ui->line2->text();
    int distance = ui->line4->text().toInt();


  reseau e(trajet,duree,distance,id);

  bool test=e.modifier();

  if(test)
{
ui->tabreseau->setModel(tmpreseau.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("modifier une machine"),
                  QObject::tr("machine modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Ok);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("modifier une machine"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);




}
void MainWindow::on_trier_clicked()
{



    QSqlQueryModel * model=tmpreseau.trier();
    ui->tabreseau->setModel(model);
}







void MainWindow::on_imprimer_clicked()
{
    QString str;
    str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> GESTION DES RESEAUX DES BUS</font><br /> <br /> "));
    str.append("<table border=1><tr>");
    str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">id</font>&nbsp;&nbsp;"+"</td>");
    str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">trajet</font>&nbsp;&nbsp;")+"</td>");
    str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">duree</font>&nbsp;&nbsp;")+"</td>");
    str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">distance</font>&nbsp;&nbsp;")+"</td>");

    QSqlQuery * query=new QSqlQuery();
    query->exec("SELECT id,trajet,duree,distance FROM reseau");
    while(query->next())
    {
        str.append("<tr><td>");
        str.append("&nbsp;&nbsp;<font color =""green"" size= ""10"">"+query->value(0).toString()+"&nbsp;&nbsp;");
        str.append("</td><td>");
        str.append("&nbsp;&nbsp;<font color =""green""  size=""10"">"+query->value(1).toString()+"&nbsp;&nbsp;");
        str.append("</td><td>");
        str.append("&nbsp;&nbsp;<font color =""green"" size=""10"">"+query->value(2).toString()+"&nbsp;&nbsp;");
        str.append("</td><td>");
        str.append("&nbsp;&nbsp;<font color =""green"" size=""10"">"+query->value(3).toString()+"&nbsp;&nbsp;");
        str.append("</td></tr>");


    }


  str.append("</table></center><body></html>");

  QPrinter printer;
  printer.setOrientation(QPrinter::Portrait);
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setPaperSize(QPrinter::A4);

  QString path= QFileDialog::getSaveFileName(NULL,"imprimer","gestion des reseaux des bus","PDF(*.pdf");
   if(path.isEmpty()) return;
   printer.setOutputFileName(path);
   QTextDocument doc;
   doc.setHtml(str);
   doc.print(&printer);



}





void MainWindow::sendMail()
{Smtp* smtp = new Smtp("cpp.projet.cpp@gmail.com", "c++testc++", "smtp.gmail.com", 465);
connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("cpp.projet.cpp@gmail.com", ui->rcpt->text() , "tableau de gestion des reseaux des bus",0);
}
void MainWindow::sendMailstation()
{Smtp* smtp = new Smtp("cpp.projet.cpp@gmail.com", "c++testc++", "smtp.gmail.com", 465);
connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("cpp.projet.cpp@gmail.com", ui->rcpts->text() , "tableau de gestion des reseaux des bus",1);
}
void MainWindow::mailSent(QString status)
{
if(status == "Message sent")
    QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void MainWindow::on_stat_clicked()
{
    ui->tabreseau->setModel(tmpreseau.stat());
}



void MainWindow::on_afficher_clicked()
{
    ui->tabreseau->setModel(tmpreseau.afficher());
}

void MainWindow::on_send0_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_ajouter2_clicked()
{
    QString emplacement= ui->lineEdit_emplacement->text();
        int taux = ui->lineEdit_taux->text().toInt();
          int id = ui->lineEdit_ids->text().toInt();

      station s(id,taux,emplacement);
      bool test=s.ajouter();
      if(test)
    {ui->tabstation->setModel(tmpstation.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Ajouter un reseau"),
                      QObject::tr("reseau ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un reseau"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_modifiers_clicked()
{
    int id = ui->line1s->text().toInt();

    int taux = ui->line2s->text().toInt();
    QString emplacement= ui->line3s->text();


  station s(id,taux,emplacement);

  bool test=s.modifier();

  if(test)
{
ui->tabstation->setModel(tmpstation.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("modifier une station"),
                  QObject::tr("station modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Ok);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("modifier une station"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);



}

void MainWindow::on_pb_supprimers_clicked()
{
    int id = ui->lineEdit_id_2s->text().toInt();
   bool test=tmpstation.supprimer(id);
   if(test)
   {ui->tabstation->setModel(tmpstation.afficher());//refresh
       QMessageBox::information(nullptr, QObject::tr("Supprimer une station"),
                   QObject::tr("station supprimé.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

   }
   else
       QMessageBox::critical(nullptr, QObject::tr("Supprimer une station"),
                   QObject::tr("Erreur !.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_affichers_clicked()
{
    ui->tabstation->setModel(tmpstation.afficher());
}

void MainWindow::on_triers_clicked()
{
    QSqlQueryModel * model=tmpstation.trier();
    ui->tabstation->setModel(model);
}

void MainWindow::on_stats_clicked()
{
    ui->tabstation->setModel(tmpstation.stat());

}

void MainWindow::on_send0s_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}



void MainWindow::on_pushButtons_clicked()
{

    ui->stackedWidget_2->setCurrentIndex(0);

}

void MainWindow::on_imprimers_clicked()
{
    QString str;
    str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> GESTION DES STATION DES BUS</font><br /> <br /> "));
    str.append("<table border=1><tr>");
    str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">id</font>&nbsp;&nbsp;"+"</td>");
    str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">taux d'encombrement </font>&nbsp;&nbsp;")+"</td>");
    str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">emplacement</font>&nbsp;&nbsp;")+"</td>");

    QSqlQuery * query=new QSqlQuery();
    query->exec("SELECT id,taux,emplacement FROM station");
    while(query->next())
    {
        str.append("<tr><td>");
        str.append("&nbsp;&nbsp;<font color =""green"" size= ""10"">"+query->value(0).toString()+"&nbsp;&nbsp;");
        str.append("</td><td>");
        str.append("&nbsp;&nbsp;<font color =""green""  size=""10"">"+query->value(1).toString()+"&nbsp;&nbsp;");
        str.append("</td><td>");
        str.append("&nbsp;&nbsp;<font color =""green"" size=""10"">"+query->value(2).toString()+"&nbsp;&nbsp;");
        str.append("</td></tr>");

}

    str.append("</table></center><body></html>");

    QPrinter printer;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QString path= QFileDialog::getSaveFileName(NULL,"imprimer","gestion des station des bus","PDF(*.pdf");
     if(path.isEmpty()) return;
     printer.setOutputFileName(path);
     QTextDocument doc;
     doc.setHtml(str);
     doc.print(&printer);
}

void MainWindow::on_recherche_clicked()
{
    int id = ui->lineEdit_rech->text().toInt();

    QSqlQueryModel * model=tmpreseau.recherche(id);
    ui->tabreseau->setModel(model);


}

void MainWindow::on_recherches_clicked()
{
    int id = ui->rechs->text().toInt();

    QSqlQueryModel * model=tmpstation.recherche(id);
    ui->tabstation->setModel(model);
}
