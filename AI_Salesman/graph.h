#ifndef GRAPH_H
#define GRAPH_H
#include "QVector"

class Graph
{
public:
    Graph();
    Graph(int n);
    void resize(int n);
    int size;
    QVector<QVector<int>> matrix;


};

#endif // GRAPH_H
