#include "simulationfiring.h"
#include "cmath"
#include "QDebug"



SimulationFiring::SimulationFiring()
{

}

SimulationFiring::SimulationFiring(QVector<QVector<double> > matrix, double minT, double maxT, int iterationN)
{
    this->matrix = matrix;
    this->maxT = maxT;
    this->minT = minT;
    this->iterationN = iterationN;
}

double SimulationFiring::decreaseTemp(double initTemp, int i)
{
    return initTemp*0.1/i;
}

double SimulationFiring::GetTransitionProb(int e, double t)
{
    return exp(-e/t);
}

bool SimulationFiring::isTransition(double prob)
{
    srand(time(0));
    double val = rand()%100;
    val/=100;
    if(val<prob) return 1;
    else return 0;
}

int SimulationFiring::energyCount(QVector<int> cur)
{
    int ans = 0;
    for(int i=1;i<cur.size();i++){
        ans+=matrix[cur[i-1]][cur[i]];
    }
    return ans;
}

void SimulationFiring::GenerateState(QVector<int>& cur)
{
    int i = rand()%(cur.size()-1);
    int j = rand()%(cur.size()-1);
    for(int l=0;l<cur.size();l++){
        if(cur[l]==i) cur[l]=j;
        else if(cur[l]==j) cur[l]=i;
    }
}

void SimulationFiring::simulate(QVector<int> route)
{
    this->states.clear();
    int currentEnergy = this->energyCount(route);
    QVector<int> currentState = route;
    QVector<int> newState = route;
    double t = this->maxT;
    for(int i=0;i<=iterationN;i++){
        if(i%1000==0) this->states.push_back(currentState);

        srand(time(0)+i);
        this->GenerateState(newState);
        int newStateEnergy = this->energyCount(newState);

        if(newStateEnergy<currentEnergy){
            currentEnergy = newStateEnergy;
            currentState = newState;
        }
        else{
            double p = this->GetTransitionProb(newStateEnergy-currentEnergy, t);
            if(isTransition(p)){
                currentEnergy = newStateEnergy;
                currentState = newState;
            }
        }

        t = this->decreaseTemp(this->maxT,i);
        if(t<this->minT)break;
    }
}
