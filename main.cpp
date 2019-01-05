//
// Created by nadav on 1/4/2019.
//
#include "Image.h"
int main() {
    UnionFindPixel* union1 = new UnionFindPixel(5);
    union1->Union(0,1);

    union1->printUnionFind(cout);


    return 0;
}