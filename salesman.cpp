#include "salesman.h"

int salesman::cost(int **tab)
{
    int value = 0;
    int n = genotype.size()-1;
    for (int i = 0; i < n; ++i) {
        value += tab[genotype[i]][genotype[i+1]];
    }
    value += tab[genotype[n]][genotype[0]];

    return value;
}


salesman::salesman()
{

}

salesman::salesman(int **tab, int N)
{
//    srand(time(NULL));

    std::vector<int> chromosome(N);
    std::vector<int> x(N);

    for (int i = 0; i < N; ++i) {
        x[i] = i;
    }

    int i = 0;
    while (x.size() != 0) {
        int y = rand() % x.size();
        chromosome[i] = x[y];
        x.erase(x.begin()+y);
        ++i;
    }

    genotype = chromosome;
    phenotype = cost(tab);
}

salesman::salesman(int **tab, std::vector<int> path)
{
    genotype = path;
    phenotype = cost(tab);
}

std::vector<int> salesman::getGenotype()
{
    return genotype;
}

int salesman::getPhenotype()
{
    return phenotype;
}
