#include "hebbnet.h"

HebbNet::HebbNet()
{

}

void HebbNet::study()
{
    for(int i=0;i<w.size();i++) w[i].clear();
    w.clear();

    w.resize(N);
    for(int i=0;i<N;i++){
        w[i].resize(M);
        for(int j=0;j<M;j++)w[i][j] = 0;
    }

    bool flag = true;
    for(int k = 0;k<ERA;k++){
        for(int l = 0; l<M; l++){ // Проходимся по всем эталонным векторам
            // Инициализация вектора входных нейронов и эталонного вектора выходных нейронов
            QVector<int> x(N);
            QVector<int> t(M);
            for(int k=0;k<M;k++){
                if(k==l) t[k] = 1;
                else t[k] = -1;
            }

            for(int i=0;i<N;i++)x[i] = S[l][i];

            // Корректировка весов нейронов
            int counter = 0;
            while(counter!=M){
                for(int i=0;i<N;i++){
                    for(int j=0;j<M;j++){
                        w[i][j]+=x[i]*t[j];
                    }
                }
                QVector<int> y = runAligned(x);
                counter = 0;
                for(int j=0;j<M;j++)if(y[j]==t[j])counter++;
                if(counter==M) break;  // Если веса достаточно скорректированы то переходим к следующей паре
            }
        }

        flag = true;
        for(int l = 0; l<M && flag; l++){  // Проверка корректной работы сети
            QVector<int> t(M);
            for(int k=0;k<M;k++){
                if(k==l) t[k] = 1;
                else t[k] = -1;
            }

            QVector<int> y = runAligned(S[l]);

            int counter = 0;
            for(int j=0;j<M;j++)if(y[j]==t[j])counter++;
            if(counter!=M) flag = false;
        }
        if(flag) break;
    }

    if(flag == true) qDebug()<<"Hebb Net succesfully trained";
    else qDebug()<<"Hebb Net didn't trained correctly";

}

int HebbNet::f(int S)
{
    if(S>0) return 1;
    else return -1;
}

QVector<int> HebbNet::runAligned(QVector<int> x)
{
    QVector<int> y(M);
    for(int j=0;j<M;j++){
        int s = 0;
        for(int i=0;i<N;i++)s+=x[i]*w[i][j];
        y[j] = f(s);
    }
    return y;
}

QVector<int> HebbNet::run(QVector<int> x)
{
    x.push_front(1);
    QVector<int> y = runAligned(x);
    int ansIndex = 0;
    for(int i=0;i<y.size();i++) if(y[i]==1) ansIndex = i;
    QVector<int> ans = S[ansIndex];
    ans.pop_front();
    return ans;
}
