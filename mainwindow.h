#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"reseau.h"

#include <QMainWindow>
#include <QPrinter>
#include<QFileDialog>
#include <QTextDocument>
#include "station.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();
    void on_modifier_clicked();
    void on_trier_clicked();
    void on_imprimer_clicked();

    void sendMail();
    void sendMailstation();
    void mailSent(QString);

    void on_stat_clicked();



    void on_afficher_clicked();

    void on_send0_clicked();

    void on_pushButton_clicked();



    void on_ajouter2_clicked();

    void on_modifiers_clicked();

    void on_pb_supprimers_clicked();

    void on_affichers_clicked();

    void on_triers_clicked();

    void on_stats_clicked();

    void on_send0s_clicked();

    void on_imprimers_clicked();

    void on_pushButtons_clicked();




    void on_recherche_clicked();

    void on_recherches_clicked();

private:
    Ui::MainWindow *ui;
    reseau tmpreseau;
    station tmpstation;

};
#endif // MAINWINDOW_H
