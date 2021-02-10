#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>

#include "salesman.h"

class population
{
    int sizeOfPopulation;
    int sizeOfUnit;
    float mutationRatio;
    float crossingRatio;
    bool alternateMutation;
    bool alternateCrossing;
    std::vector<salesman> p;

    void cross(int n, int **tab);
    std::vector<int> mutate(std::vector<int> a);
    void generateNewPop(int **tab);
    bool mutating();

public:
    population(int n, float m, float k, bool mm2, bool mk2, int **tab, int tabN);

    void kill(std::vector<int> deathRoll, int **tab);
    int getSalesmanPhenotype(int n);
    std::vector<int> getSalesmanGenotype(int n);

    void resize(int **tab, int n);
    int size();

    void setMutationRatio(float m);
    void setCrossingRatio(float k);
    void changeMutation();
    void changeCrossing();
    float getMutationRatio();
    float getCrossingRatio();
    bool getAlternateMutation();
    void setAlternateMutation(bool value);
    bool getAlternateCrossing();
    void setAlternateCrossing(bool value);
};

#endif // POPULATION_H
