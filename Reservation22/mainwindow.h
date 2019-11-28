#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "place.h"
#include <QDialog>

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_modifier_clicked();



    void on_pb_supprimer_clicked();

    void on_pb_show_clicked();

    void on_tabplace_activated(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pb_retour_clicked();

private:
    Ui::Mainwindow *ui;
     Place tmp;
};

#endif // MAINWINDOW_H
