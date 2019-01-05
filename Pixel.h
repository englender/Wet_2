#ifndef EX4_LIBRARY_H
#define EX4_LIBRARY_H

#include "SuperPixel.h"

class Pixel{
    int pixel_ID;
    Pixel* father_pixel;
    SuperPixel* super;

public:
    Pixel(int ID);
    ~Pixel();

};





#endif