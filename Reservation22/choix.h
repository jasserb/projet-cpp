#ifndef CHOIX_H
#define CHOIX_H

#include <QMainWindow>
#include "mainwindow.h"
#include "mainwindow2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Choix; }
QT_END_NAMESPACE

class Choix : public QMainWindow
{
    Q_OBJECT

public:
    Choix(QWidget *parent = nullptr);
    ~Choix();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Choix *ui;
    Mainwindow *m;
    Mainwindow2 *n;
};
#endif // CHOIX_H
