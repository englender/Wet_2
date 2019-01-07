//
// Created by nadav on 1/4/2019.
//

#ifndef EX4_IMAGE_H
#define EX4_IMAGE_H

#include "UnionFindPixel.h"

class Image {
    int imageID;
    UnionFindPixel *pixels;

public:
    Image(int imageID, int num_of_pixels);
//    ~Image();

    void set_label_score(int pixel, int label, int score);
    bool delete_label(int pixel, int label);
    bool is_super_pixel_labeled(int pixel);
    int get_max_label_score(int pixel);
    bool Union(int pixel1, int pixel2);
};


#endif //EX4_IMAGE_H
