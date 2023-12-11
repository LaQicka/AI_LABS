#ifndef HEMMINGNET_H
#define HEMMINGNET_H

#include <QVector>

class HemmingNet
{
public:
    HemmingNet();
    void study();
    double f(double z);
    QVector<double> run(QVector<int> x);


private:
    QVector<QVector<int>> q
        {
            {-1,-1,1,1,1,1,-1,1,-1},
            {-1,1,-1,1,-1,1,1,1,-1},
            {-1,1,-1,1,1,1,-1,1,-1},
            {1,1,-1,1,1,1,-1,1,1},
            {1,1,-1,1,1,1,-1,-1,-1},
            {1,1,-1,-1,1,1,-1,-1,1}
        };

    QVector<QVector<double>> w;
    QVector<QVector<double>> e;

    double T = 4.5;
    double EPS = 0.2;
    double EMAX = 0.1;
    int K = 6;
    int M = 9;
};

#endif // HEMMINGNET_H
