#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_initButton_clicked()
{
    int xmin = ui->lineXMIN->text().toInt();
    int xmax = ui->lineXMAX->text().toInt();
    double accuracy = ui->lineAccuracy->text().toDouble();
    double mutationK = ui->lineMutationK->text().toDouble();
    double a1 = ui->lineA1->text().toDouble();
    double a2 = ui->lineA2->text().toDouble();
    int n = ui->lineN->text().toInt();

    QString method = ui->codeBox->currentText();

    QString function = ui->funcBox->currentText();

    int functionNumber = 0;

    if(function == "(x^2+y-11)^2 + (x+y^2-7)^2") functionNumber = 0;
    else if(function == "x^2 + 3*y^2 + 2*x*y") functionNumber = 1;
    else if(function == "-12*y + 4*x^2 + 4*y^2 - 4*x*y") functionNumber = 2;
    else if(function == "(x-2)^4 + (x-2*y)^2") functionNumber = 3;
    else if(function == "8*x^2 + 4*x*y + 5*y") functionNumber = 4;
    else if(function == "x^3 + y^2 - 3*y - 2*x + 2") functionNumber = 5;

    algo = ui->algoBox->currentText();
    if(algo == "Genetic"){
        genetic = new Genetic(xmin,xmax,accuracy,method,functionNumber,mutationK);
    }
    else if(algo == "Swarm"){
        swarm = new Swarm(xmin,xmax,n,a1,a2);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(this->algo == "Genetic") this->genetic->run();
    else if (this->algo == "Swarm") this->swarm->run();
}

