#include "antalgo.h"
#include "qdebug.h"

AntAlgo::AntAlgo()
{

}

AntAlgo::AntAlgo(QVector<QVector<double>> matrix, double startFer, double alpha, double beta, double ferK, int iterationN)
{
    this->matrix = matrix;
    this->fer.resize(matrix.size());
    for(int i=0;i<matrix.size();i++){
        fer[i].resize(matrix.size());
        for(int j=0;j<matrix.size();j++){
            fer[i][j]=startFer;
            if(i==j)fer[i][j]=0;
        }
    }
    this->alpha = alpha;
    this->beta = beta;
    this->ferK = ferK;
    this->iterationNumber = iterationN;
}

QVector<QPair<int,double>> AntAlgo::propabilities(int cur, QVector<int> cities)
{
    double sum = 0;
    QVector<QPair<int,double>> ans(cities.size());
    for(int i=0;i<cities.size();i++){
        sum += pow(fer[cur][cities[i]],alpha)*pow(matrix[cur][cities[i]],beta);
        ans[i].second = pow(fer[cur][cities[i]],alpha)*pow(matrix[cur][cities[i]],beta);
        ans[i].first = cities[i];
    }

    for(int i=0;i<ans.size();i++){
        if(i!=cur) ans[i].second /= sum;
    }
    return ans;
}

int AntAlgo::cityToTransit(QVector<QPair<int,double>> prop, double p)
{
    double sum = prop[0].second;
    int ans = prop[0].first;
    for(int i=1;i<prop.size();i++){
        if(sum<p && (sum+prop[i].second)>=p) ans = prop[i].first;
        sum+=prop[i].second;
    }
    return ans;
}

QVector<int> AntAlgo::runAnt(int start)
{
    QVector<int> cities(matrix.size());
    for(int i=0;i<cities.size();i++)cities[i]=i;
    cities.removeAll(start);
    QVector<int> route;
    route.push_back(start);

    int n = matrix.size()-1;
    srand(time(0));
    while(n--){
        QVector<QPair<int,double>> prop = propabilities(route.back(),cities);
        double p = rand()%100;
        p/=100;
        int next = cityToTransit(prop,p);
        cities.removeAll(next);
        route.push_back(next);
    }

    route.push_back(start);
    return route;
}

int AntAlgo::lengthCount(QVector<int> route)
{
    int sum = 0;
    for(int i=1;i<route.size();i++)sum+=matrix[route[i-1]][route[i]];
    return sum;
}

void AntAlgo::runAlgo()
{

    for(int l=0;l<iterationNumber;l++){
        QVector<QVector<int>> antsRoutes(matrix.size());
        for(int i=0;i<matrix.size();i++) antsRoutes[i] = runAnt(i);

        for(int i=0;i<matrix.size();i++) for(int j=0;j<matrix.size();j++) fer[i][j]*=ferK;

        int minIndex = 0, minLength=0;
        for(int i=0;i<antsRoutes.size();i++){

            double length = lengthCount(antsRoutes[i]);
            if(i==0 || length<minLength) {
                minIndex = i;
                minLength = length;
            }
            double ferToAdd = matrix.size()/length;
//            qDebug()<<length<<" "<<ferToAdd;
            for(int j=1;j<antsRoutes[i].size();j++) fer[antsRoutes[i][j-1]][antsRoutes[i][j]] += ferToAdd;

        }
//        qDebug()<<"\n\nFer"<<" "<<minLength;
//        for(int i=0;i<fer.size();i++)qDebug()<<fer[i];
        states.push_back(antsRoutes[minIndex]);
    }
}

QVector<QVector<int> > AntAlgo::getStates()
{
    return this->states;
}
