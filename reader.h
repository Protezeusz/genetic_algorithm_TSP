#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>

class reader
{
public:
    reader();
    ~reader();

    int **tab1;
    int **tab2;
    int **tab3;
    int bestKnow[3];
    int n[3];


    int **getTab(int a);
    int getBestKnown(int i);
    int getN(int i);
};

#endif // READER_H
