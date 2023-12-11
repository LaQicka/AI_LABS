#include "swarm.h"

Swarm::Swarm(double left, double right, int n, double a1, double a2)
{
    this->a1 = a1;
    this->a2 = a2;
    this->EraCounter = 0;
    init(left, right, n);
}

double Swarm::f(double x, double y)
{
    return (x*x + y - 11)*(x*x + y - 11) + (x + y*y - 7)*(x + y*y - 7);
}

void Swarm::init(double left, double right, int n)
{
    swarm.resize(n);

    for(int i=0;i<n;i++){
        swarm[i].x = random(left,right);
        swarm[i].y = random(left,right);
        swarm[i].vx = 0;
        swarm[i].vy = 0;

        swarm[i].pbest = f(swarm[i].x,swarm[i].y);
        swarm[i].pbestX = swarm[i].x;
        swarm[i].pbestY = swarm[i].y;

        if(gbest > swarm[i].pbest){
            gbest = swarm[i].pbest;
            gbestX = swarm[i].pbestX;
            gbestY = swarm[i].pbestY;
        }
    }
    qDebug()<<"SWARM: Success init";
}

double Swarm::random(double min, double max)
{
    return (double)(rand())/RAND_MAX*(max - min) + min;
}

void Swarm::run()
{
    EraCounter += 10;
    double a1 = 1;
    double a2 = 1;

    for(int i=0;i<10;i++){
        for(int i = 0; i < swarm.size(); i++){ // Перемещение частицы и рассчет значения функции в новой точке
            swarm[i].x += swarm[i].vx;
            swarm[i].y += swarm[i].vy;
            double fCur = f(swarm[i].x,swarm[i].y);
            if(fCur < swarm[i].pbest){
                swarm[i].pbest = fCur;
                swarm[i].pbestX = swarm[i].x;
                swarm[i].pbestY = swarm[i].y;
            }
            if(swarm[i].pbest < gbest){
                gbest = swarm[i].pbest;
                gbestX = swarm[i].pbestX;
                gbestY = swarm[i].pbestY;
            }
        }

        for(int i=0;i<swarm.size();i++){ // Корректировка скорости частиц
            double r = random(0,1);
            swarm[i].vx += a1*r*(swarm[i].pbestX - swarm[i].x);
            swarm[i].vy += a1*r*(swarm[i].pbestY - swarm[i].y);
            r = random(0,1);
            swarm[i].vx += a2*r*(gbestX-swarm[i].x);
            swarm[i].vy += a2*r*(gbestY-swarm[i].y);
        }
    }

    qDebug()<<EraCounter<<" "<<gbest<<" "<<gbestX<<" "<<gbestY;
}

