#ifndef GENETIC_H
#define GENETIC_H

#include <QVector>
#include <QString>
#include <cmath>
#include <QPair>
#include <QDebug>

class Genetic
{
public:
    Genetic(int XMIN, int XMAX, double accuracy, QString method, int functionNumber, double mutationK);
    void init();
    void run();
    double random(double min, double max);
    void generation(QVector<QPair<double,double>>& population);
    void sort(QVector<QPair<double,double>>& arr, QVector<QPair<double, double>>& buff, int left, int right);
    double f(QPair<double,double> x);

    double decode(int g);
    int code(double r);

private:
    int XMAX, XMIN;
    double accuracy;
    int m;
    QString method;

    double mutationK;
    int EraCounter = 0;
    int functionNumber;

    QPair<double,double> ans;
    QVector<QPair<double,double>> population;
};

#endif // GENETIC_H
