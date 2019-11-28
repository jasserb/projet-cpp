#include "station.h"
#include <QDebug>

station::station()
{
id=0 ;
emplacement="";
taux=0;


}
station::station(int id,int taux,QString emplacement)
{

    this->id=id;
    this->taux=taux;
    this->emplacement=emplacement;

}
QString station::get_emplacement(){return  emplacement;}
int station::get_id(){return  id;}
int station::get_taux(){return  taux;}
bool station::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);

QString res2= QString::number(taux);

query.prepare("INSERT INTO station (id,taux,emplacement) "
                    "VALUES (:id, :taux, :emplacement)");
query.bindValue(":id", res);
query.bindValue(":emplacement", emplacement);
query.bindValue(":taux", res2);




return    query.exec();
}

QSqlQueryModel * station::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from station");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("taux"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("emplacement "));



    return model;
}
bool station::modifier()
{

QSqlQuery query;
QString res= QString::number(id);
QString res1= QString::number(taux);

query.prepare("update station set  emplacement='"+emplacement+"',taux='"+res1+"'   where id='"+res+"'  ;");



    query.bindValue(":taux",taux);
    query.bindValue(":emplacement", emplacement);

    query.bindValue(":id",id);
return    query.exec();
}


bool station::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from station where id = :id ");
query.bindValue(":id", res);
return    query.exec();
}

QSqlQueryModel * station::trier()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from station order by taux asc;");


model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("taux d'encombrement "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("emplacement"));


return model;

}

QSqlQueryModel  * station::recherche(int idd)
{
QSqlQueryModel * model= new QSqlQueryModel();
QString res= QString::number(idd);
model->setQuery("select * from station where id = '"+res+"' ");
return    model;
}
QSqlQueryModel * station::stat()
{QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("delete  from tabs");
model->setQuery(" INSERT  INTO tabs(taux,pourcentage) select  station.taux, 100.0 * COUNT(*) / SUM(COUNT(*)) OVER () As ""pourcentage"" FROM station GROUP BY taux;");




    model->setQuery("select * from tabs");
model->setHeaderData(1, Qt::Horizontal, QObject::tr("%TAUX "));


    return model;
}
