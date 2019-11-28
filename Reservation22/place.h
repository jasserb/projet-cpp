#ifndef PLACE_H
#define PLACE_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Place
{
public:
    Place();
    Place(int,int,QString,QString,QString,int,int,QString);
    QString get_nom();
    QString get_prenom();
     QString get_email();
    int get_id();
    int get_cin();
    int get_nbplace();
    int get_nbres();
    bool ajouter();
    QString get_td();
    QSqlQueryModel * afficher();
    bool supprimer(int);
     QSqlQueryModel * afficherf();
    bool modifier(int);
   QSqlQueryModel * trier();
    private:
    QString nom , prenom , email,td;
    int id , cin , nbplace , nbres;

};

#endif // PLACE_H

