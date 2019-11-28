#include "place.h"
#include <QDebug>
Place::Place()
{
    id=0;
    cin=0;
    nom="";
    prenom="";
    nbplace=0;
    nbres=0;
}

Place::Place(int id, int cin, QString nom,QString prenom,QString email, int nbplace,int nbres, QString td)
{
    this->id=id;
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->nbplace=nbplace;
    this->nbres=nbres;
    this->td=td;
}

QString Place::get_nom(){return  nom;}
QString Place::get_prenom(){return prenom;}
QString Place::get_email(){return email;}
int Place::get_id(){return  id;}
int Place::get_cin(){return  cin;}
int Place::get_nbplace(){return  nbplace;}
int Place::get_nbres(){return  nbres;}



bool Place::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("INSERT INTO PLACE(ID,CIN,NOM,PRENOM,EMAIL,NBPLACE,NBRES,TD)"
                  "VALUES(:id, :cin, :nom, :prenom,:email, :nbplace, :nbres, :td )");
    query.bindValue(":id", res);
    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email",email);
    query.bindValue(":nbplace", nbplace);
    query.bindValue(":nbres", nbres);
    query.bindValue(":td", td);
    return query.exec();

}

QSqlQueryModel *Place::afficher()
{
    QSqlQueryModel * mode1= new QSqlQueryModel();
    mode1->setQuery("select * from place");
    mode1->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    mode1->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN"));
    mode1->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    mode1->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    mode1->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    mode1->setHeaderData(5, Qt::Horizontal, QObject::tr("NBP"));
    mode1->setHeaderData(6, Qt::Horizontal, QObject::tr("NBR"));
    mode1->setHeaderData(7, Qt::Horizontal, QObject::tr("TD"));
    return mode1;
}

bool Place::supprimer(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("Delete from place WHERE ID =:id");
    query.bindValue(":id",res);
    return query.exec();

}

bool Place::modifier(int idd)
{
    QSqlQuery query;
    QString res=QString::number(idd);
    query.prepare("UPDATE place SET NBRES=:nbres  where ID=:id");

     query.bindValue(":id", res);
     query.bindValue(":nbres", nbres);
    return query.exec();
}


QSqlQueryModel *Place::afficherf()
{
    QSqlQueryModel * mode1= new QSqlQueryModel();

    mode1->setQuery("select * from place where nbres>=5 ");
    mode1->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    mode1->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN"));
    mode1->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    mode1->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    mode1->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    mode1->setHeaderData(5, Qt::Horizontal, QObject::tr("NBP"));
    mode1->setHeaderData(6, Qt::Horizontal, QObject::tr("NBR"));
    mode1->setHeaderData(7, Qt::Horizontal, QObject::tr("TD"));
    return mode1;
}
