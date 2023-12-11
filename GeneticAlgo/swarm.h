#ifndef SWARM_H
#define SWARM_H
#include <QVector>
#include <cmath>
#include <QDebug>

class Swarm
{
public:
    Swarm(double left, double right, int n, double a1, double a2);
    double f(double x, double y);
    void init(double left, double right, int n);
    double random(double min, double max);
    void run();

private:
    struct Element{
        double x;
        double y;
        double pbest;
        double pbestX;
        double pbestY;
        double vx;
        double vy;
    };

    int EraCounter = 0;
    double gbest = INT32_MAX;
    double gbestX;
    double gbestY;
    double a1;
    double a2;
    QVector<Element> swarm;

};

#endif // SWARM_H
