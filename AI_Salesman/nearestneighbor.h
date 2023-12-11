#ifndef NEARESTNEIGHBOR_H
#define NEARESTNEIGHBOR_H

#include "QVector"

class NearestNeighbor
{
public:
    NearestNeighbor();
    QVector<int> countRoute(QVector<QVector<double>> matrix, int start);
};

#endif // NEARESTNEIGHBOR_H
