#include "hemmingnet.h"
#include "qdebug.h"

HemmingNet::HemmingNet()
{

}

void HemmingNet::study()
{
    for(int i=0;i<w.size();i++)w[i].clear();
    w.clear();

    w.resize(M);
    for(int i=0;i<M;i++){ // Заполнение массива весов нейронов
        w[i].resize(K);
        for(int j=0;j<K;j++){
            w[i][j] = (double)(q[j][i])/2;
        }
    }

    for(int i=0;i<e.size();i++)e[i].clear();
    e.clear();

    e.resize(K);
    for(int i=0;i<K;i++){ // Заполнение массива обратных связей синапсов
        e[i].resize(K);
        for(int j=0;j<K;j++){
            if(i==j) e[i][j] = 1;
            else e[i][j] = -EPS;
        }
    }
    qDebug()<<"Hemming Net succesfully trained";
}

double HemmingNet::f(double z) // Функция активации
{
    if(z<=0) return 0;
    else return z;
}

QVector<double> HemmingNet::run(QVector<int> x)
{
    QVector<double> sCur(K);
    QVector<double> yCur(K);

    for(int i=0;i<K;i++){ // Заполнение выходного вектора сумм
        sCur[i]=0;
        for(int j=0;j<M;j++){
            sCur[i]+=w[j][i]*x[j];
        }
        sCur[i] += T;
    }
    for(int i=0;i<K;i++){ // Заполнение выходного вектора
        yCur[i] = f(sCur[i]);
    }

    double dif = K;
    QVector<double> sPrev = sCur;
    QVector<double> yPrev = yCur;
    while(dif>=EPS){ // Расчитывание нового значения выходных нейронов
        sCur.clear();
        sCur.resize(K);
        yCur.clear();
        yCur.resize(K);
        for(int i=0;i<K;i++){
            sCur[i] = 0;
            for(int j=0;j<K;j++){
                if(i!=j)sCur[i]+=yPrev[j];
            }
            sCur[i] *= EPS;
            sCur[i] = yPrev[i] - sCur[i];
        }
        for(int i=0;i<K;i++){
            yCur[i] = f(sCur[i]);
        }
        dif = 0;
        for(int i=0;i<K;i++){
            if(yCur[i]!=yPrev[i])dif++;
        }
        sPrev = sCur;
        yPrev = yCur;
    }
    return yCur;
}
