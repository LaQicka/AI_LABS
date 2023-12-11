#include "graph.h"

Graph::Graph()
{

}

Graph::Graph(int n)
{
    this->resize(n);
}

void Graph::resize(int n)
{
    matrix.resize(n);
    srand(time(0));
    for(int i=0;i<n;i++){
        matrix[i].resize(n);
        for(int j=0;j<n;j++){
            if(i==j) matrix[i][j]=0;
            else matrix[i][j] = 1 + rand()%50;
        }
    }
}
