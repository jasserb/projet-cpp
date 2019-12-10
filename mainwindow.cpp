#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reseau.h"
#include <QMessageBox>
#include <QString>
#include "smtp.h"
#include "station.h"
#include <QUrl>
#include <QDebug>
#include <QTextBrowser>
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
QRegExp rx("[A-Za-z_]+");//[A-Za-z0-9_]
    QRegExp rx1("[0-9_]+");
    QValidator *validator = new QRegExpValidator(rx, this);
    QValidator *validator2 = new QRegExpValidator(rx1, this);
    ui->lineEdit_id->setValidator(validator2);
    ui->lineEdit_duree->setValidator(validator2);
    ui->lineEdit_distance->setValidator(validator2);
    ui->lineEdit_emplacement->setValidator(validator);
    ui->lineEdit_taux->setValidator(validator2);
    ui->lineEdit_ids->setValidator(validator2);

    m_manager = new QNetworkAccessManager(this);
   connect(m_manager, &QNetworkAccessManager::finished, this, &MainWindow::uploadFinished);
    ui->lab->setText("<a href=\"http://www.gestion-reseaux-stations.tk/\"><font size=""10"">SITE WEB</font></a>");
    ui->lab->setTextFormat(Qt::RichText);
    ui->lab->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->lab->setOpenExternalLinks(true);
}





MainWindow::~MainWindow()
{
    delete ui;
}


QString MainWindow::trajet()
{
return "st "+ui->comboBox->currentText()+"-->"+"st "+ui->comboBox_2->currentText();
}


void MainWindow::on_pb_ajouter_clicked()
{
    QSqlQuery query;
    int duree = ui->lineEdit_duree->text().toInt();
     int distance= ui->lineEdit_distance->text().toInt();
      int id = ui->lineEdit_id->text().toInt();

  reseau e(trajet(),duree,distance,id);
  query.prepare("select * from reseau where id= :id");
  query.bindValue(":id",ui->lineEdit_id->text());
  query.exec();
  if(!(query.next()))
{

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
  else
      QMessageBox::critical(nullptr, QObject::tr("Demande"),
                  QObject::tr("id existe !.\n"
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
QMessageBox::information(nullptr, QObject::tr("modifier un reseau"),
                  QObject::tr("reseau modifié.\n"
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

void MainWindow::combo()
{
    QSqlQuery * query=new QSqlQuery();
    query->exec("SELECT id FROM station");

ui->comboBox->clear();
ui->comboBox_2->clear();
    while(query->next())
    {
        ui->comboBox->addItem(query->value(0).toString());
         ui->comboBox_2->addItem(query->value(0).toString());
    }
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

    QSqlQuery query;
    QString emplacement= ui->lineEdit_emplacement->text();
        int taux = ui->lineEdit_taux->text().toInt();
          int id = ui->lineEdit_ids->text().toInt();



      query.prepare("select * from station where id= :id");
      query.bindValue(":id",ui->lineEdit_ids->text());
      query.exec();
      if(!(query.next()))
    {
          station s(id,taux,emplacement);
          bool test=s.ajouter();
      if(test)
    {ui->tabstation->setModel(tmpstation.afficher());//refresh
          combo();
    QMessageBox::information(nullptr, QObject::tr("Ajouter une station"),
                      QObject::tr("reseau ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter une station"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter une station"),
                      QObject::tr("id existe !.\n"
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
    str.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;;<font size=""10"" color =""red""> GESTION DES STATIONS </font><br /> <br /> "));
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

    QString path= QFileDialog::getSaveFileName(NULL,"imprimer","gestion des stations des bus","PDF(*.pdf");
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


QString * MainWindow::html()
{
    QString *path=new QString;
    path[0] ="C:/Users/jasser/Desktop/qt/index.htm";
    path[1]="C:/Users/jasser/Desktop/qt/index.html";
    QString str0;
    str0.append("<!DOCTYPE html>");
    str0.append("<html><head></head><style>  body {background-image: url(""https://img.wallpapersafari.com/desktop/1920/1080/20/72/ibFeIy.jpg"");background-repeat:no-repeat; background-size:cover;} </style><body><center>");
    str0.append(" <a href=""http://www.gestion-reseaux-stations.tk/""><font size=10>Accueil</font></a></center> <center> ");

    str0.append("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font size=""10"" color =""red""> GESTION DES RESEAUX DES BUS</font><br /> <br /> ");
    str0.append("<table border=1><tr>");
    str0.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">id</font>&nbsp;&nbsp;"+"</td>");
    str0.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">trajet</font>&nbsp;&nbsp;")+"</td>");
    str0.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">duree</font>&nbsp;&nbsp;")+"</td>");
    str0.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">distance</font>&nbsp;&nbsp;")+"</td>");

    QSqlQuery * query=new QSqlQuery();
    query->exec("SELECT id,trajet,duree,distance FROM reseau");
    while(query->next())
    {
        str0.append("<tr><td>");
        str0.append("&nbsp;&nbsp;<font color =""green"" size= ""10"">"+query->value(0).toString()+"&nbsp;&nbsp;");
        str0.append("</td><td>");
        str0.append("&nbsp;&nbsp;<font color =""green""  size=""10"">"+query->value(1).toString()+"&nbsp;&nbsp;");
        str0.append("</td><td>");
        str0.append("&nbsp;&nbsp;<font color =""green"" size=""10"">"+query->value(2).toString()+"&nbsp;&nbsp;");
        str0.append("</td><td>");
        str0.append("&nbsp;&nbsp;<font color =""green"" size=""10"">"+query->value(3).toString()+"&nbsp;&nbsp;");
        str0.append("</td></tr>");


    }


  str0.append("</table></center><center><a href=""http://www.gestion-reseaux-stations.tk/station""><font size=10>Table station</font></a></center><body></html>");
  QFile file0(path[0]);
  if(file0.open(QIODevice::WriteOnly | QIODevice::Text))
  {

  QTextStream doc(&file0);
  doc<<str0;
  qDebug() <<"done";
  file0.close();

    }



    QString str;
    str.append("<!DOCTYPE html>");
    str.append("<html><head></head><style>  body {background-image: url(""https://img.wallpapersafari.com/desktop/1920/1080/20/72/ibFeIy.jpg"");background-repeat:no-repeat; background-size:cover;} </style><body><center>");

    str.append(" <a href=""http://www.gestion-reseaux-stations.tk/""><font size=10>Accueil</font></a></center> <center> ");
    str.append("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp<font size=""10"" color =""red""> GESTION DES STATIONS</font><br /> <br /> ");



    str.append("<table border=1><tr>");
    str.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""10"">id</font>&nbsp;&nbsp;"+"</td>");
    str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">taux d'encombrement </font>&nbsp;&nbsp;")+"</td>");
    str.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""10"">emplacement</font>&nbsp;&nbsp;")+"</td>");

   query=new QSqlQuery();
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

    str.append("</table></center><a href=""http://www.gestion-reseaux-stations.tk/reseau"" ><font size=10><center>Table reseau</center></font></a><body></html>");

QFile file(path[1]);
if(file.open(QIODevice::WriteOnly | QIODevice::Text))
{

QTextStream doc(&file);
doc<<str;
qDebug() <<"done";
file.close();


}


     return path;

}







void MainWindow::on_uploadButton_clicked()
{
    ui->progressBar->setValue(0);
QString * path=html();
    m_file = new QFile(path[0]);



       QFileInfo fileInfo(*m_file);
       QUrl url("ftp://files.000webhost.com/public_html/reseau/" + fileInfo.fileName());
       url.setUserName("gestion-reseaux-stations");    // Set login
       url.setPassword("7SGmeHejb(bedAALTo@c"); // Set пароль
       url.setPort(21);             // Protocol port, which we will work on

      if (m_file->open(QIODevice::ReadOnly))
       {
            m_manager->put(QNetworkRequest(url), m_file);

       }
       m_file= new QFile(path[1]);
       QFileInfo fileInfo1(*m_file);
       QUrl url1("ftp://files.000webhost.com/public_html/station/" + fileInfo1.fileName());

       url1.setUserName("gestion-reseaux-stations");    // Set login
       url1.setPassword("7SGmeHejb(bedAALTo@c"); // Set пароль
       url1.setPort(21);             // Protocol port, which we will work on

       if (m_file->open(QIODevice::ReadOnly))
       {
           // Start upload
           QNetworkReply *reply = m_manager->put(QNetworkRequest(url1), m_file);
           // And connect to the progress upload signal
           connect(reply, &QNetworkReply::uploadProgress, this, &MainWindow::uploadProgress);
       }
}


void MainWindow::uploadFinished(QNetworkReply *reply)
{
   /* // If the upload was successful without errors
    if (!reply->error())
    {
        // то закрываем файл
        m_file->close();
        m_file->deleteLater();  // delete object of file
        reply->deleteLater();   // delete object of reply
    }*/

}

void MainWindow::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    // Display the progress of the upload
    ui->progressBar->setValue(100 * bytesSent/bytesTotal);
}
