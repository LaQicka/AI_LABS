#include "genetic.h"

Genetic::Genetic(int XMIN, int XMAX, double accuracy, QString method, int functionNumber, double mutationK)
{
    this->XMIN = XMIN;
    this->XMAX = XMAX;
    this->accuracy = accuracy;
    this->method = method;
    this->functionNumber = functionNumber;
    this->mutationK = mutationK;
    this->EraCounter = 0;
    this->init();
}

void Genetic::init()
{
    double temp = (XMAX-XMIN)/accuracy;
    m = log2(temp) + 1;

    if(method == "integer"){
        population.clear();
        population.resize(16);
        for(int i=0;i<16;i++){
            population[i].first = code(random(XMIN,XMAX));
            population[i].second = code(random(XMIN,XMAX));
        }
    }
    else if(method == "real"){
        population.clear();
        population.resize(16);
        for(int i=0;i<16;i++){
            population[i].first = random(XMIN,XMAX);
            population[i].second = random(XMIN,XMAX);
        }
    }

    ans = population[0];

    qDebug()<<"GENETIC: Success init";
}

void Genetic::run()
{
        EraCounter += 100;
        QVector<QPair<double,double>> buff(16);
        QVector<QPair<double,double>> population2(16);

        if(method == "real"){
            for(int i=0;i<100;i++) generation(population);
        }
        else if(method == "integer"){

            for(int i=0;i<100;i++){
                for(int i=0;i<16;i++){
                    population2[i].first = decode(population[i].first);
                    population2[i].second = decode(population[i].second);
                }
                generation(population2);
                for(int i=0;i<16;i++){
                    population[i].first = code(population2[i].first);
                    population[i].second = code(population2[i].second);
                }
            }
        }

        if(method == "real")sort(population,buff,0,16);
        else if(method == "integer"){
            for(int i=0;i<16;i++){
                population2[i].first = decode(population[i].first);
                population2[i].second = decode(population[i].second);
            }
            sort(population2,buff,0,16);
            for(int i=0;i<16;i++){
                population[i].first = population2[i].first;
                population[i].second = population2[i].second;
            }
        }

        qDebug()<<EraCounter<<" "<<f(ans)<<" "<<ans;
}

double Genetic::random(double min, double max)
{
        return (double)(rand())/RAND_MAX*(max - min) + min;
}

void Genetic::generation(QVector<QPair<double, double> > &population)
{
        QVector<QPair<double,double>> buff(16);
        QVector<QPair<double,double>> selected(4);

        sort(population,buff,0,16);
        if(f(population[0]) < f(ans)) ans = population[0];

        for(int i=0;i<4;i++)selected[i] = population[i];

        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                population[i*4+j].first = selected[i].first;
                population[i*4+j].second = selected[j].second;
            }
        }

        for(int i=0;i<16;i++){
            double flag = random(-1,1);
            double p = random(0,1);
            if(flag < 0 && p <= mutationK){
                population[i].first = random(this->XMIN,this->XMAX);
            }else if(p <= mutationK){
                population[i].second = random(this->XMIN,this->XMAX);
            }
        }
}

void Genetic::sort(QVector<QPair<double, double> > &arr, QVector<QPair<double, double> > &buff, int left, int right)
{
        if (left+1 >= right) return;

        int mid = (left + right) / 2;

        sort(arr, buff, left, mid);
        sort(arr, buff, mid, right);

        int l = left, r = mid;
        int i = left;

        while (i < right) {
            if ((r >= right) || (l < mid && f(arr[l]) <= f(arr[r]))) {
                buff[i] = arr[l];
                i++;
                l++;
            }
            else if (r < right) {
                buff[i] = arr[r];
                r++;
                i++;
            }
        }

        for (i = left; i < right; i++)arr[i] = buff[i];
}

double Genetic::f(QPair<double,double> x)
{
        switch(functionNumber){
        case(0):
            return (x.first*x.first + x.second - 11)*(x.first*x.first + x.second - 11) + (x.first + x.second*x.second - 7)*(x.first + x.second*x.second - 7);
            break;
        case(1):
            return pow(x.first,2) + 3*pow(x.second,2) + 2*x.first*x.second;
            break;
        case(2):
            return -12*x.second + 4*x.first*x.first + 4*x.second*x.second - 4*x.first*x.second;
            break;
        case(3):
            //  "(x-2)^4 + (x-2*y)^2"
            return pow(x.first-2,4) + pow(x.first - 2*x.second,2);
            break;
        case(4):
            //  "8*x^2 + 4*x*y + 5*y"
            return 8*pow(x.first,2) + 4*x.first*x.second + 5*x.second*x.second;
            break;
        case(5):
            //  "x^3 + y^2 - 3*y - 2*x + 2"
            return pow(x.first,3) + pow(x.second,2) - 2*x.first + 2;
            break;
        default:
            return -12*x.second + 4*x.first*x.first + 4*x.second*x.second - 4*x.first*x.second;
            break;

        }
}

double Genetic::decode(int g)
{
    double r;
    r = g*(XMAX-XMIN);
    r /= (pow(2,m)-1);
    r += XMIN;
    return r;
}

int Genetic::code(double r)
{
    double g = (r-XMIN)*(pow(2,m)-1);
    g /= (XMAX-XMIN);
    return (int)g;
}
