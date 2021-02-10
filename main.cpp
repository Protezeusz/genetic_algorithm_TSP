#include <iostream>

#include "environment.h"
//#include "reader.h"
#include "salesman.h"
//#include "population.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//reader r;
environment e;
std::vector<int> path;

void printtab(int **a, int n)
{
    std::cout << "Tab:\n";
    if (n < 101)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                std::cout << a[i][j] << " ";
            std::cout <<"\n";
        }
    else
        std::cout <<"over size\n";
}

void populationTest()
{

    std::vector<float> A; //averge
    std::vector<float> R; //relative
    std::vector<std::vector<int>> P; //path
    std::vector<int> B; //bestFind

    int n;
    int bestFind;
    int sum;
    int bestKnown;
    int nrTab = 3;
    int nrSetup = 4;
    float averge;
    float relative;

    std::vector<std::string> txtSetup; //setup

    std::cout <<"Podaj liczbe testowanych populacji: ";
    std::cin >> n;
    std::vector<int> popul(n);

    for (int i = 0; i < popul.size(); ++i) {
        std::cout <<"Podaj rozmiar populacji nr "<< i + 1 <<": ";
        std::cin >> n;
        popul[i] = n;
    }

    std::cout <<"Podaj liczbe testow: ";
    std::cin >> n;
    system("cls");

    int timeleft = 0;
    for (int var = 0; var < popul.size(); ++var) {

        e.setPopulationSize(popul[var]);

        for (int j = 0; j < nrTab; ++j) {

            e.setA(j);

            for (int i = 0; i < nrSetup; ++i) {

                std::string txt;
                if (i)
                    e.changeMutation();
                if (i == 2)
                    e.changeCrossing();

                if (e.ifAlternateCrossing())
                    txt = "OX & ";
                else
                    txt = "PMX & ";

                if (e.ifAlternateMutatinon())
                    txt += "Insert ";
                else
                    txt+= "Swap ";

                txt += "\nPopulacja: ";
                txt += std::to_string(popul[var]);

                txt += "\nRozmiar tablicy: ";
                txt += std::to_string(e.getN());

                txtSetup.push_back(txt);

                bestFind = INT_MAX;
                sum = 0;
                bestKnown = e.getBest();

                for (int k = 0; k < n; ++k) {
                    salesman s = e.solve(popul.size()*nrTab*nrSetup*n- timeleft);
                    timeleft++;
                    sum += s.getPhenotype();
                    if (bestFind > s.getPhenotype()) {
                        path = s.getGenotype();
                        bestFind = s.getPhenotype();
                    }
                }
                averge = sum/n;
                relative = abs(averge - bestKnown);
                relative /= bestKnown;

                A.push_back(averge);
                R.push_back(relative);
                P.push_back(path);
                B.push_back(bestFind);
            }
        }
    }

//    std::cout.precision(2);
    for (int i = 0; i < txtSetup.size(); ++i) {
        std::cout << txtSetup[i] << "\n";

        std::cout << "\nsrednia     blad\n";
        std::cout << A[i] << "        " << R[i]*100 << "%";

        std::cout << "\nNajlepsza sciezka:\n";
        for (unsigned j = 0; j < P[i].size(); ++j) {
            std::cout << P[i][j] << " ";
        }
        std::cout << "\nwaga: " << B[i] << "\n\n";
    }
}

void autoSolve(int n)
{
    int bestFind = INT_MAX;
    int sum = 0;
    int bestKnown = e.getBest();

    for (int i = 0; i < n; ++i) {
        salesman s = e.solve(n-i);
        sum += s.getPhenotype();
        if (bestFind > s.getPhenotype()) {
            path = s.getGenotype();
            bestFind = s.getPhenotype();
        }
    }

    float averge = sum/n;
    float relative = abs(averge - bestKnown);
    relative /= bestKnown;


    std::cout.precision(2);
    std::cout << "\nsrednia     blad\n";
    std::cout << averge << "        " << relative;

    std::cout << "\nNajlepsza sciezka:\n";
    for (unsigned i = 0; i < path.size(); ++i) {
        std::cout << path[i] << " ";
    }
    std::cout << "\nwaga: " << bestFind << "\n";
}

void solve()
{
    salesman s = e.solve(1);
    path = s.getGenotype();
    std::cout << "\nsciezka:\n";
    for (unsigned i = 0; i < path.size(); ++i) {
        std::cout << path[i] << " ";
    }
    std::cout << "\nwaga: " << s.getPhenotype() << "\n";
}

int main()
{

    srand(time(NULL));
    int q,d; //switch
    int n; //int settings
    float fn; //float settings
    bool x = true; //main while
    bool y = true; //other while

    while (x) {
        std::cout << " 1. Wybierz dane z pliku i wyswietl.\n"
                     " 2. Wprowadz kryterium stopu.\n"
                     " 3. Ustaw wielkosc populacji poczatkowej.\n"
                     " 4. Ustaw wspolczynnik mutacji.\n"
                     " 5. Ustaw wspolczynnik krzyzowania.\n"
                     " 6. Zmiana metody mutacji.\n"
                     " 7. Zmiana metody krzyzowania.\n"
                     " 8. Uruchom algorytm.\n"
                     " 9. Policz srednia dla N testow\n"
                     "10. Zbadaj wplyw wielkosci populacji\n"
                     " 0. Wyjscie.\n";
        std::cin >> q;

        switch (q) {
        case 1:
            system("cls");
            std::cout << "Wybierz rozmiar tablicy:\n"
                         "1. n = 17\n"
                         "2. n = 100\n"
                         "3. n = 443\n";
            y = true;
            while (y)
            {
                std::cin >> d;
                if(d > 0 && d < 4)
                {
//                    a = d-1;
                    e.setA(d-1);
                    system("cls");
                    printtab(e.getTab(), e.getN());
                    y = false;
                }
                else
                    std::cout << "Nierozpoznano!\n";
            }
            break;
        case 2:
            system("cls");
            std::cout << "Aktualny czas: " << e.getTime() << "s\n";
            std::cout << "Zmien na: ";
            std::cin >> n;
            e.setTime(n);
            system("cls");
            std::cout << "Zmieniono\n";
            break;
        case 3:
            system("cls");
            std::cout << "Aktualna populacja: " << e.getPopulationSize() << "\n";
            std::cout << "Zmien na: ";
            std::cin >> n;
            e.setPopulationSize(n);
            system("cls");
            std::cout << "Zmieniono\n";
            break;
        case 4:
            system("cls");
            std::cout << "Aktualny wspolczynnik mutacji: " << e.getMutationRatio() << "\n";
            std::cout << "Zmien na: ";
            std::cin >> fn;
            e.setMutationRatio(fn);
            system("cls");
            std::cout << "Zmieniono\n";
            break;
        case 5:
            system("cls");
            std::cout << "Aktualny wspolczynnik krzyzowania: " << e.getCrossingRatio() << "\n";
            std::cout << "Zmien na: ";
            std::cin >> fn;
            e.setCrossingRatio(fn);
            system("cls");
            std::cout << "Zmieniono\n";
            break;
        case 6:
            e.changeMutation();
            system("cls");
            if (e.ifAlternateMutatinon())
                std::cout << "Zmieniono na insert\n";
            else
                std::cout << "Zmieniono na swap\n";
            break;
        case 7:
            e.changeCrossing();
            system("cls");
            if (e.ifAlternateCrossing())
                std::cout << "Zmieniono na OX\n";
            else
                std::cout << "Zmieniono na PMX\n";
            break;
        case 8:
            solve();
            break;
        case 9:
            system("cls");
            std::cout << "Podaj N: ";
            std::cin >> n;
            autoSolve(n);
            break;
        case 10:
            system("cls");
            populationTest();
            break;
        case 0:
            x = false;
            break;
        default:
            break;
        }
    }
}
