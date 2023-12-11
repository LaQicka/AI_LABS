#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <QVector>
#include <QPair>
#include <cmath>

#include <swarm.h>
#include <genetic.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    double f(QPair<double,double> x);
    void sort(QVector<QPair<double,double>>& arr, QVector<QPair<double, double>>& buff, int left, int right);
    void generation(QVector<QPair<double,double>>& population);
    double random(double min, double max);
    void init();
    void run();

    double decode(int g);
    int code(double r);

    ~MainWindow();

private slots:
    void on_initButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QPair<double,double>> population;
    QPair<double,double> ans;

    QString algo;
    Genetic* genetic;
    Swarm* swarm;
};
#endif // MAINWINDOW_H
