#include "environment.h"

void environment::setA(int value)
{
    a = value;
}

int environment::getTime()
{
    return time;
}

void environment::setTime(int value)
{
    time = value;
}

int environment::getPopulationSize()
{
    return populationSize;
}

void environment::setPopulationSize(int value)
{
    populationSize = value;
}

float environment::getMutationRatio()
{
    return mutationRatio;
}

void environment::setMutationRatio(float value)
{
    mutationRatio = value;
}

float environment::getCrossingRatio()
{
    return crossingRatio;
}

void environment::setCrossingRatio(float value)
{
    crossingRatio = value;
}

void environment::changeMutation()
{
    alternateMutatinon = !alternateMutatinon;
}

void environment::changeCrossing()
{
    alternateCrossing= !alternateCrossing;
}

salesman environment::solve(int N)
{
    salesman best;
    population p(populationSize, mutationRatio, crossingRatio, alternateMutatinon, alternateCrossing, r.getTab(a), r.getN(a));
    std::vector<int> deathRoll(populationSize/2);

    auto cmp = [&p](int left, int right) { return (p.getSalesmanPhenotype(left)) < (p.getSalesmanPhenotype(right)); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q(cmp);

    timeOut = false;
    std::thread timeLord (clock, this, N);
    while (!timeOut) {
        for (int i = 0; i < populationSize; ++i) {
            q.push(i);
        }

        for (int i = 0; i < populationSize/2; ++i) {
            deathRoll[i] = q.top();
            q.pop();
    //        std::cout << deathRoll[i] << " " << p.getSalesmanWeight(deathRoll[i]) << "\n";
        }
    //    std::cout << "\n";
        p.kill(deathRoll, r.getTab(a));
        while (!(q.size() == 1)) {
            q.pop();
        }
        salesman s(r.getTab(a), p.getSalesmanGenotype(q.top()));
        best = s;
        q.pop();
    }

    timeLord.join();
    return best;
}

bool environment::ifAlternateMutatinon()
{
    return alternateMutatinon;
}

bool environment::ifAlternateCrossing()
{
    return alternateCrossing;
}

void environment::clock(int N)
{
    for (int i = 0; i < time; ++i) {
        system("CLS");
        std::cout << "pozostalo: " << N*time - i << "s";
        Sleep(1000);
    }
    system("CLS");
    timeOut = true;
}

environment::environment()
{
    a = 0;
    time = 3;
    populationSize = 10;
    mutationRatio = 0.01;
    crossingRatio = 0.8;
    alternateCrossing = false;
    alternateMutatinon = false;
}

int **environment::getTab()
{
    return r.getTab(a);
}

int environment::getN()
{
    return r.getN(a);
}

int environment::getBest()
{
    return r.getBestKnown(a);
}
