#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->scene=new QGraphicsScene;
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    points.resize(6);
    points[0].setX(0);
    points[0].setY(0);
    points[1].setX(100);
    points[1].setY(0);
    points[2].setX(0);
    points[2].setY(100);
    points[3].setX(100);
    points[3].setY(100);
    points[4].setX(0);
    points[4].setY(200);
    points[5].setX(100);
    points[5].setY(200);
}

void MainWindow::drawLine(int i, int x)
{
    int s = linesPoints[i][0];
    int d = linesPoints[i][1];

    this->scene->addLine(points[s].x()+x,points[s].y(),points[d].x()+x,points[d].y());
}

QVector<int> MainWindow::runHemming(QVector<int> x)
{
    QVector<double> ans;
    ans = hemming.run(x);
    int ansInd = 0;
    for(int i=0;i<ans.size();i++) if(ans[i]>ans[ansInd]) ansInd = i;
    return q[ansInd];
}

QVector<int> MainWindow::runHebb(QVector<int> x)
{
    QVector<int> ans = hebb.run(x);
    return ans;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runButton_clicked()
{

    QVector<int> x(9);
    x[0] = ui->line0->text().toInt();
    x[1] = ui->line1->text().toInt();
    x[2] = ui->line2->text().toInt();
    x[3] = ui->line3->text().toInt();
    x[4] = ui->line4->text().toInt();
    x[5] = ui->line5->text().toInt();
    x[6] = ui->line6->text().toInt();
    x[7] = ui->line7->text().toInt();
    x[8] = ui->line8->text().toInt();

    QString algo = ui->algoBox->currentText();

    qDebug()<<algo;

//    QVector<int> x {1,1,-1,-1,1,1,-1,-1,1};


    QVector<int> ansDraw;

    if(algo == "Hemming Algo")ansDraw = runHemming(x);
    else if(algo == "Hebb Algo")ansDraw = runHebb(x);

    scene->clear();
    for(int i=0;i<x.size();i++) if(x[i]>0) drawLine(i,-50);
    for(int i=0;i<ansDraw.size();i++) if(ansDraw[i]>0) drawLine(i,100);
}


void MainWindow::on_study_clicked()
{
    hemming.study();
    hebb.study();
}

