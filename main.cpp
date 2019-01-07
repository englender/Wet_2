//
// Created by nadav on 1/4/2019.
//
#include "Image.h"
int main() {
    cout << "Test Initialize: " << endl;
    UnionFindPixel* union1 = new UnionFindPixel(5);
//    union1->printUnionFind(cout);

    cout << "set new label: " << endl;
    union1->set_score_to_label(0,1,1);
    union1->set_score_to_label(0,2,2);
    union1->printUnionFind(cout);

    cout << "union 0,1" << endl;
    union1->Union(0,1);
    union1->printUnionFind(cout);

    cout << "Add label to index 0:" << endl;
    union1->set_score_to_label(0,3,3);
    union1->printUnionFind(cout);

    cout << "union 0,2" << endl;
    union1->Union(0,2);
    union1->printUnionFind(cout);

    cout << "union 4,2" << endl;
    union1->Union(4,2);
    union1->printUnionFind(cout);

    cout << "Add label to index 3:" << endl;
    union1->set_score_to_label(3,4,4);
    union1->set_score_to_label(3,5,5);
    union1->set_score_to_label(0,5,5);
    union1->printUnionFind(cout);


    cout << "union 4,3" << endl;
    union1->Union(4,3);
    union1->printUnionFind(cout);

    cout << "delete 3,3" << endl;
    union1->delete_label(3,3);
    union1->printUnionFind(cout);

    cout << "delete 3,5" << endl;
    union1->delete_label(3,5);
    union1->printUnionFind(cout);
    return 0;
}