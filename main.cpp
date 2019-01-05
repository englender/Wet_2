//
// Created by nadav on 1/4/2019.
//
#include "Image.h"
int main() {
    cout << "Test Initialize: " << endl;
    UnionFindPixel* union1 = new UnionFindPixel(5);
    union1->printUnionFind(cout);

    cout << "set new label: " << endl;
    union1->set_score_to_label(0,1,3);
    union1->set_score_to_label(0,2,4);
    union1->printUnionFind(cout);

    cout << "union 0,1" << endl;
    union1->Union(0,1);
    union1->printUnionFind(cout);

    return 0;
}