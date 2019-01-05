//
// Created by nadav on 1/2/2019.
//

#ifndef EX4_SUPERPIXEL_H
#define EX4_SUPERPIXEL_H

#define NO_SCORE -1

#include "Pixel.h"
#include "map_tree.h"


class SuperPixel {
    int max_lable_score;
    Map_tree<int,int>* tree;

public:
    SuperPixel();
    ~SuperPixel();
};



#endif //EX4_SUPERPIXEL_H
