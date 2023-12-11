#ifndef ANTALGO_H
#define ANTALGO_H

#include <QVector>
#include <cmath>
#include <QPair>


class AntAlgo
{
public:
    AntAlgo();
    AntAlgo(QVector<QVector<double>> matrix, double startFer, double alpha, double beta, double ferK, int iterationN);
    QVector<QPair<int,double>> propabilities(int cur, QVector<int> cities);
    int cityToTransit(QVector<QPair<int,double>> prop, double p);
    QVector<int> runAnt(int start);
    int lengthCount(QVector<int> route);
    void runAlgo();
    QVector<QVector<int>> getStates();

private:
    QVector<QVector<double>> matrix;
    QVector<QVector<double>> fer;
    double alpha, beta, ferK;
    int iterationNumber;
    QVector<QVector<int>> states;
};

#endif // ANTALGO_H
