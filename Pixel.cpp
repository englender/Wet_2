#include "Pixel.h"

Pixel::Pixel(int ID):pixel_ID(ID), father_pixel(nullptr) {
    SuperPixel* super_tmp=new SuperPixel(this);
    this->super=super_tmp;

}
