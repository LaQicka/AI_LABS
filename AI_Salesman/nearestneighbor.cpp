#include "nearestneighbor.h"
#include "iostream"

NearestNeighbor::NearestNeighbor()
{

}

QVector<int> NearestNeighbor::countRoute(QVector<QVector<double> > matrix, int start)
{
    bool flag = false;
    QVector<int> visited;
    visited.push_back(start);
    int cur = start;
    while(visited.size()!=matrix.size()){
        int minIndex;
        bool tempFlag = false;
        for(int i=0;i<matrix.size();i++){
            if(!tempFlag && i!=cur && !visited.contains(i)){
                tempFlag = true;
                minIndex = i;
            }
            else if(i!=cur && matrix[cur][minIndex]<matrix[cur][i] && !visited.contains(i)){
                minIndex = i;
            }
        }
        visited.push_back(minIndex);
    }
    visited.push_back(start);
    return visited;
}
