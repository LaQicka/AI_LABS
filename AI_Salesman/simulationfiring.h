#ifndef SIMULATIONFIRING_H
#define SIMULATIONFIRING_H

#include <QVector>

class SimulationFiring
{
public:
    SimulationFiring();
    SimulationFiring(QVector<QVector<double>> matrix, double minT, double maxT, int iterationN);
    double decreaseTemp(double initTemp, int i);
    double GetTransitionProb(int e, double t);
    bool isTransition(double prob);
    int energyCount(QVector<int> cur);
    void GenerateState(QVector<int>& cur);
    void simulate(QVector<int> route);

    QVector<QVector<double>> matrix;
    double minT, maxT;
    int iterationN;

    QVector<QVector<int>> states;

};

#endif // SIMULATIONFIRING_H
