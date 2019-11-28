#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H
#include <bus.h>
#include <QDialog>

namespace Ui {
class Mainwindow2;
}

class Mainwindow2: public QDialog
{
    Q_OBJECT

public:
    explicit Mainwindow2(QWidget *parent = nullptr);
    ~Mainwindow2();

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
    Ui::Mainwindow2 *ui;
    bus tmp;
};
#endif // MAINWINDOW2_H
