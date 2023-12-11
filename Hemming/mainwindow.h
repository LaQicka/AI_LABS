#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <iostream>
#include <QDebug>
#include <QVector>
#include <QString>

#include <hemmingnet.h>
#include <hebbnet.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void drawLine(int i, int x);
    QVector<int> runHemming(QVector<int> x);
    QVector<int> runHebb(QVector<int> x);
    ~MainWindow();

private slots:
    void on_runButton_clicked();

    void on_study_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    QVector<QPointF> points;
    QVector<QVector<int>> linesPoints
        {
            {0,1},{0,2},{1,2},{1,3},{2,3},{2,4},{3,4},{3,5},{4,5}
        };

    HemmingNet hemming;
    HebbNet hebb;

//    _              _    _    _
//   |_|  | |  |_|  |_|  |_|  |_
//   | |  |/|  | |  |_|  |    |_
//


    QVector<QVector<int>> q
    {
        {-1,-1,1,1,1,1,-1,1,-1}, // A
        {-1,1,-1,1,-1,1,1,1,-1}, // И
        {-1,1,-1,1,1,1,-1,1,-1}, // H
        {1,1,-1,1,1,1,-1,1,1},   // B
        {1,1,-1,1,1,1,-1,-1,-1}, // P
        {1,1,-1,-1,1,1,-1,-1,1}  // E
    };

};
#endif // MAINWINDOW_H
