#ifndef STATION_H
#define STATION_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class station
{
public:
    station();
    station(int , int, QString);
    QString get_emplacement();
    int get_id();
    int get_taux();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * stat();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * trier();
    QSqlQueryModel *  recherche(int);

private:
    QString emplacement;
    int id , taux;
};

#endif // STATION_H
