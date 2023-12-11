#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->scene=new QGraphicsScene;
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
}

int MainWindow::countRouteValue(QVector<int> route)
{
    int ans = 0;
    for(int i=1;i<route.size();i++)ans+=matrix[route[i-1]][route[i]];
    return ans;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_generateButton_clicked()
{
    int number = this->ui->dotNumber->text().toInt();
    matrix.clear();
    verticles.clear();
    if(number<0)return;
    srand(time(0));
    for(int i=0;i<number;i++){
        int x = rand()%400;
        int y = rand()%400;
        Verticle* v = new Verticle;
        v->setPos(x,y);
        verticles.push_back(v);
    }

    matrix.resize(number);
    for(int i=0;i<number;i++){
        matrix[i].resize(number);
        for(int j=0;j<number;j++){
            if(i==j)matrix[i][j]=1;
            else{
                int dy = verticles[i]->y() - verticles[j]->y();
                int dx = verticles[i]->x() - verticles[j]->x();
                matrix[i][j] = qSqrt((dy*dy+dx*dx));
            }
        }
    }

    QString algo = ui->algoBox->currentText();
    qDebug()<<algo;

    if(algo == "AntAlgo"){
        double alpha = ui->antAlpha->text().toDouble();
        double beta = ui->antBeta->text().toDouble();
        double startFer = ui->antStartFer->text().toDouble();
        double ferK = ui->antStartFer->text().toDouble();
        int iterationNumber = ui->antIterationNumber->text().toInt();

//        AntAlgo* ants = new AntAlgo(matrix,0.4,4,2,0.5,10000);
        AntAlgo* ants = new AntAlgo(matrix,startFer,alpha,beta,ferK,iterationNumber);
        ants->runAlgo();
        this->states.clear();
        this->states = ants->getStates();
        qDebug()<<this->states.size();
    }
    else if(algo == "FiringAlgo"){

        NearestNeighbor neighbor;
        QVector<int> cur = neighbor.countRoute(this->matrix,1);

        double minT = ui->FireMinT->text().toDouble();
        double maxT = ui->FireMaxT->text().toDouble();
        int iterationN = ui->fireIterationNumber->text().toInt();

        qDebug()<<minT<<" "<<maxT<<" "<<iterationN;

//        SimulationFiring* simulation = new SimulationFiring(this->matrix, 0.000001, 10, 100000);
        SimulationFiring* simulation = new SimulationFiring(this->matrix,minT,maxT,iterationN);

        simulation->simulate(cur);

        this->states = simulation->states;
        qDebug()<<simulation->states.size();
    }
}


void MainWindow::on_clearButton_clicked()
{
    this->scene->clear();
}


void MainWindow::on_drawButton_clicked()
{
    for(int i=0;i<verticles.size();i++)scene->removeItem(verticles[i]);
    this->scene->clear();
    int iteration = ui->iteration->text().toInt();
    qDebug()<<"Iteration "<<iteration;
    if(iteration >= states.size() || iteration<0) return;
    QVector<int> route = this->states[iteration];
    qDebug()<<route;
    qDebug()<<" value "<<countRouteValue(route);
    for(int i=1;i<route.size();i++){
        this->scene->addLine(verticles[route[i-1]]->x(),verticles[route[i-1]]->y(),verticles[route[i]]->x(),verticles[route[i]]->y());
    }
    this->scene->addLine(verticles[route.back()]->x(),verticles[route.back()]->y(),verticles[route[0]]->x(),verticles[route[0]]->y());
    for(int i=0;i<verticles.size();i++){
        scene->addItem(verticles[i]);
    }


}

