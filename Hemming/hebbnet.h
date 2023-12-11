#ifndef HEBBNET_H
#define HEBBNET_H

#include <QDebug>

#include <QVector>

class HebbNet
{
public:
    HebbNet();
    void study();
    int f(int S);
    QVector<int> runAligned(QVector<int> x); // Run with shift index
    QVector<int> run(QVector<int> x);

private:
    QVector<QVector<int>> S
    {
         {1,-1,-1,1,1,1,1,-1,1,-1}
        ,{1,-1,1,-1,1,-1,1,1,1,-1}
        ,{1,-1,1,-1,1,1,1,-1,1,-1}
//        ,{1,1,1,-1,1,1,1,-1,1,1}
//        ,{1,1,1,-1,1,1,1,-1,-1,-1}
        ,{1,1,1,-1,-1,1,1,-1,-1,1}
    };

    QVector<QVector<double>> w;

    int N = 10;
    int M = 4;
    int ERA = 20;
};

#endif // HEBBNET_H
