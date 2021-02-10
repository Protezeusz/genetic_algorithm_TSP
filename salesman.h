#ifndef SALESMAN_H
#define SALESMAN_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

class salesman
{

    std::vector<int> genotype;
    int phenotype;

    int cost(int **tab);

public:
    salesman();
    salesman(int **tab, int N);
    salesman(int **tab, std::vector<int> path);

    std::vector<int> getGenotype();
    int getPhenotype();
};

#endif // SALESMAN_H
