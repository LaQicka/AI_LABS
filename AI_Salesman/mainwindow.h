#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QDebug>
#include <graph.h>
#include <nearestneighbor.h>
#include <QRandomGenerator>
#include <simulationfiring.h>
#include <QPair>
#include <QtMath>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <verticle.h>
#include <antalgo.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    int countRouteValue(QVector<int> route);
    ~MainWindow();

private slots:
    void on_generateButton_clicked();

    void on_clearButton_clicked();

    void on_drawButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;


    QVector<Verticle*> verticles;
    QVector<QVector<double>> matrix;
    QVector<QVector<int>> states;

};
#endif // MAINWINDOW_H
