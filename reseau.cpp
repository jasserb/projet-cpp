#include "reseau.h"
#include <QDebug>

reseau::reseau()
{
duree=0;
trajet="";
distance=0;
id=0;
}
reseau::reseau(QString trajet,int duree,int distance,int id)
{
  this->trajet=trajet;
  this->duree=duree;
  this->distance=distance;
    this->id=id;

}
QString reseau::get_trajet(){return  trajet;}
int reseau::get_duree(){return  duree;}
int reseau::get_distance(){return  distance;}
int reseau::get_id(){return  id;}

bool reseau::ajouter()
{
QSqlQuery query;
QString res= QString::number(duree);
QString res1= QString::number(distance);
QString res2= QString::number(id);

query.prepare("INSERT INTO reseau (trajet,duree,distance,id) "
                    "VALUES (:trajet, :duree, :distance,:id)");
query.bindValue(":id", res2);
query.bindValue(":trajet", trajet);
query.bindValue(":duree", res);
query.bindValue(":distance", res1);




return    query.exec();
}

QSqlQueryModel * reseau::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from reseau");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("trajet"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("duree "));

model->setHeaderData(3, Qt::Horizontal, QObject::tr("distance"));


    return model;
}

bool reseau::modifier()
{

QSqlQuery query;
QString res= QString::number(duree);
QString res1= QString::number(id);

QString res2= QString::number(distance);
query.prepare("update reseau set  trajet='"+trajet+"',distance='"+res2+"' , duree='"+res+"'  where id='"+res1+"'  ;");



    query.bindValue(":duree",duree);
    query.bindValue(":trajet", trajet);
    query.bindValue(":distance", distance);
    query.bindValue(":id",id);
return    query.exec();
}


bool reseau::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from reseau where id = :id ");
query.bindValue(":id", res);
return    query.exec();
}
QSqlQueryModel  * reseau::recherche(int idd)
{
QSqlQueryModel * model= new QSqlQueryModel();
QString res= QString::number(idd);
model->setQuery("select * from reseau where id = '"+res+"' ");
return    model;
}

QSqlQueryModel * reseau::trier()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from reseau order by duree asc;");


model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("trajet "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("duree"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("distance"));

return model;

}


QSqlQueryModel * reseau::stat()
{QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("delete  from tab");
model->setQuery(" INSERT  INTO tab(duree,pourcentage_duree) select  reseau.duree, 100.0 * COUNT(*) / SUM(COUNT(*)) OVER () As ""pourcentage_duree"" FROM reseau GROUP BY duree;");


model->setQuery(" INSERT  INTO tab(distance,pourcentage_distance) select  reseau.distance, 100.0 * COUNT(*) / SUM(COUNT(*)) OVER () As ""Pourcentage_distance"" FROM reseau GROUP BY distance;");


    model->setQuery("select * from tab");
model->setHeaderData(1, Qt::Horizontal, QObject::tr("%DUREE "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("%DISTANCE "));


    return model;
}
