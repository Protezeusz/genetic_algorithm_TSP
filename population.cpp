#include "population.h"

float population::getMutationRatio()
{
    return mutationRatio;
}

float population::getCrossingRatio()
{
    return crossingRatio;
}

population::population(int n, float m, float k, bool mm2, bool mk2, int **tab, int tabN)
{
    sizeOfPopulation = n;
    mutationRatio = m;
    crossingRatio = k;
    alternateMutation = mm2;
    alternateCrossing = mk2;
    sizeOfUnit = tabN;

    generateNewPop(tab);
}

void population::kill(std::vector<int> deathRoll, int **tab)
{
    std::priority_queue<int> q;
    for (unsigned i = 0; i < deathRoll.size(); ++i) {
        q.push(deathRoll[i]);
    }

    for (unsigned i = 0; i < deathRoll.size(); ++i) {
        p.erase(p.begin() + q.top());
        q.pop();
    }
    cross(deathRoll.size(), tab);
}

int population::getSalesmanPhenotype(int n)
{
    return p[n].getPhenotype();
}

std::vector<int> population::getSalesmanGenotype(int n)
{
    return p[n].getGenotype();
}

void population::resize(int **tab, int n)
{
    p.clear();
    sizeOfPopulation = n;
    generateNewPop(tab);
}

int population::size()
{
    return sizeOfPopulation;
}

bool population::getAlternateMutation()
{
    return alternateMutation;
}

void population::setAlternateMutation(bool value)
{
    alternateMutation = value;
}

bool population::getAlternateCrossing()
{
    return alternateCrossing;
}

void population::setAlternateCrossing(bool value)
{
    alternateCrossing = value;
}

void population::cross(int n, int **tab)
{

    // srand(time(NULL));

    if (alternateCrossing) { //(OX)
        for (int i = 0; i < n; ++i) {
            std::vector<int> a = p[rand() % (sizeOfPopulation - n)].getGenotype();
            std::vector<int> b = p[rand() % (sizeOfPopulation - n)].getGenotype();

            std::vector<int> c(a.size(), -1);
    //        std::vector<int> d(a.size(), -1);
            int o = a.size() * crossingRatio/2;
            int x = rand() % (a.size() - o);
            int y = x + o - 1;

            for (int j = x; j < y; ++j) {
                c[j] = a[j];
//                d[j] = b[j];
            }

            std::vector<int> b2(b.begin() + y, b.end());
//            std::vector<int> a2(a.begin() + y, a.end());
            for (int j = 0; j < y; ++j) {
                b2.push_back(b[j]);
//                a2.push_back(a[j]);
            }
            for (int j = 0; j < b2.size(); ++j) {
                for (int k = x; k < y; ++k) {
                    if (b2[j] == c[k]) {
                        b2.erase(b2.begin() + j);
                        --j;
                        break;
                    }
                }
            }

//            for (int j = 0; j < a2.size(); ++j) {
//                for (int k = x; k < y; ++k) {
//                    if (a2[j] == d[k]) {
//                        a2.erase(a2.begin() + j);
//                        --j;
//                        break;
//                    }
//                }
//            }

            int h = c.size()-y;
            for (int j = 0; j < b2.size(); ++j) {
                if(j < h)
                    c[j + y] = b2[j];
                else
                    c[j - h] = b2[j];
            }

//            for (int j = 0; j < a2.size(); ++j) {
//                if(j < x)
//                    d[j + y] = a2[j];
//                else
//                    d[j - x] = a2[j];
//            }
            if(mutating())
                c = mutate(c);
//            d = mutate(d);

            salesman s1(tab, c);
//            salesman s2(tab, d);

            p.push_back(s1);
//            p.push_back(s2);
        }
    }
    else //(PMX)
    {
        for (int i = 0; i < n; ++i) {
            std::vector<int> a = p[rand() % (sizeOfPopulation - n)].getGenotype();
            std::vector<int> b = p[rand() % (sizeOfPopulation - n)].getGenotype();

            int x = a.size() * crossingRatio;
            std::vector<int> c(a.begin(), a.begin() + x);
//            std::vector<int> d(b.begin(), b.begin() + x);

            bool skip;

            for (int j = 0; j < b.size(); ++j) {
                skip = false;
                for (int k = 0; k < x; ++k) {
                    if (b[j] == c[k]) {
                        skip =  true;
                        break;
                    }
                }
                if(!skip)
                    c.push_back(b[j]);
            }

//            for (int j = 0; j < a.size(); ++j) {
//                skip = false;
//                for (int k = 0; k < x; ++k) {
//                    if (a[j] == d[k]) {
//                        skip =  true;
//                        break;
//                    }
//                }
//                if(!skip)
//                    d.push_back(a[j]);
//            }

            if(mutating())
                c = mutate(c);
//            d = mutate(d);

            salesman s1(tab, c);
//            salesman s2(tab, d);

            p.push_back(s1);
//            p.push_back(s2);
        }
    }
}

std::vector<int> population::mutate(std::vector<int> a)
{
   // srand(time(NULL));
//    if() {
        if (alternateMutation) { //insert
            int x = rand() % a.size();
            int y = rand() % a.size();
            while(x == y)
                y = rand() % a.size();
            std::vector<int> tab(a.size());
            for (int i = 0; i < a.size(); ++i) {
                if (x < y) {
                    if (i < x)
                        tab[i] = a[i];
                    else if (i < y)
                        tab[i] = a[i+1];
                    else if (i == y)
                        tab[i] = a[x];
                    else
                        tab[i] = a[i];
                } else {
                    if (i < y)
                        tab[i] = a[i];
                    else if (i == y)
                        tab[i] = a[x];
                    else if (i <= x)
                        tab[i] = a[i-1];
                    else
                        tab[i] = a[i];
                }
            }
            a = tab;
        }
        else //swap
        {
            int x = rand() % a.size();
            int y = rand() % a.size();

            int z = a[x];
            a[x] = a[y];
            a[y] = z;
        }
//    }
    return a;
}

void population::generateNewPop(int **tab)
{
    for (int i = 0; i < sizeOfPopulation; ++i) {
        salesman s(tab, sizeOfUnit);
        p.push_back(s);
    }
}

bool population::mutating()
{
    //srand(time(NULL));
    int x = 1/mutationRatio;
    if(rand()%x)
        return false;
    else
        return true;
}

void population::setMutationRatio(float m)
{
    mutationRatio = m;
}

void population::setCrossingRatio(float k)
{
    crossingRatio = k;
}

void population::changeMutation()
{
    alternateMutation = !alternateMutation;
}

void population::changeCrossing()
{
    alternateCrossing = !alternateCrossing;
}
