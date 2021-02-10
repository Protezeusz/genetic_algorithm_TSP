#include "reader.h"

reader::reader()
{

    std::ifstream file;
    std::string s;

    file.open("best.txt");
    std::getline(file, s);
    bestKnow[0] = std::stoi(s);
    std::getline(file, s);
    bestKnow[1] = std::stoi(s);
    std::getline(file, s);
    bestKnow[2] = std::stoi(s);
    file.close();

    std::string delimiter = " ", token;
    size_t pos = 0;

    file.open("tsp_17.txt");
    std::getline(file, s);
    n[0] = std::stoi(s);

    tab1 = new int *[n[0]];
    for (int i = 0; i < n[0]; ++i)
        tab1[i] = new int[n[0]];

    for (int i = 0; i < n[0]; ++i) {
        int j = 0;
        std::getline(file, s);
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            if (token != "")
            {
                tab1[i][j] = std::stoi(token);
                j++;
            }
            s.erase(0, pos + delimiter.length());
        }
        tab1[i][j] = std::stoi(s);
    }
    file.close();

    file.open("tsp_100.txt");
    std::getline(file, s);
    n[1] = std::stoi(s);

    tab2 = new int *[n[1]];
    for (int i = 0; i < n[1]; ++i)
        tab2[i] = new int[n[1]];

    for (int i = 0; i < n[1]; ++i) {
        int j = 0;
        std::getline(file, s);
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            if (token != "")
            {
                tab2[i][j] = std::stoi(token);
                j++;
            }
            s.erase(0, pos + delimiter.length());
        }
        tab2[i][j] = std::stoi(s);
    }
    file.close();

    file.open("tsp_443.txt");
    std::getline(file, s);
    n[2] = std::stoi(s);

    tab3 = new int *[n[2]];
    for (int i = 0; i < n[2]; ++i)
        tab3[i] = new int[n[2]];

    for (int i = 0; i < n[2]; ++i) {
        int j = 0;
        std::getline(file, s);
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            if (token != "")
            {
                tab3[i][j] = std::stoi(token);
                j++;
            }
            s.erase(0, pos + delimiter.length());
        }
        tab3[i][j] = std::stoi(s);
    }
    file.close();

}

reader::~reader()
{
    for(int i = 0; i < n[0]; ++i) {
        delete [] tab1[i];
    }
    delete [] tab1;

    for(int i = 0; i < n[1]; ++i) {
        delete [] tab2[i];
    }
    delete [] tab2;

    for(int i = 0; i < n[1]; ++i) {
        delete [] tab3[i];
    }
    delete [] tab3;
}

int reader::getBestKnown(int i)
{
    return bestKnow[i];
}

int reader::getN(int i)
{
    return n[i];
}

int **reader::getTab(int a)
{
    if (a == 0)
        return tab1;
    if (a == 1)
        return tab2;
    if (a == 2)
        return tab3;
}
