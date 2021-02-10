#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <queue>
#include <thread>
#include <windows.h>
#include <ctime>
#include <iostream>

#include "reader.h"
#include "population.h"
#include "salesman.h"

class environment
{
    reader r;
    //population p;
    int a;
    int time;
    int populationSize;
    float mutationRatio;
    float crossingRatio;
    bool alternateMutatinon;
    bool alternateCrossing;
    bool timeOut;
    void clock(int N);

public:
    environment();


    int **getTab();
    int getN();
    int getBest();


    void setA(int value);
    int getTime();
    void setTime(int value);
    int getPopulationSize();
    void setPopulationSize(int value);
    float getMutationRatio();
    void setMutationRatio(float value);
    float getCrossingRatio();
    void setCrossingRatio(float value);
    void changeMutation();
    void changeCrossing();

    salesman solve(int N);
    bool ifAlternateMutatinon();
    bool ifAlternateCrossing();
};

#endif // ENVIRONMENT_H
