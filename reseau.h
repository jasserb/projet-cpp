#ifndef RESEAU_H
#define RESEAU_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class reseau
{public:
    reseau();
    reseau(QString,int,int,int);
    QString get_trajet();

    int get_duree();
    int get_distance();
    int get_id();

void print();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * stat();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel *  recherche(int);
    QSqlQueryModel * trier();

private:
    QString trajet;
    int duree,distance,id;
};
#endif // RESEAU_H
