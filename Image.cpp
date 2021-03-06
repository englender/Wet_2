//
// Created by nadav on 1/4/2019.
//

#include "Image.h"

Image::Image(int imageID, int num_of_pixels): imageID(imageID){
    this->pixels=new UnionFindPixel(num_of_pixels);

}

Image:: ~Image(){
    delete pixels;
}


void Image::set_label_score(int pixel, int label, int score) {
//assumption: only parent of superpixel have a label tree
    this->pixels->set_score_to_label(pixel,label,score);
}



bool Image::delete_label(int pixel, int label) {
    return this->pixels->delete_label(pixel,label);
}

bool Image::is_super_pixel_labeled(int pixel){
    return this->pixels->is_super_pixel_labeled(pixel);
}

int Image::get_max_label_score(int pixel){
    return this->pixels->get_max_label_score(pixel);
}

bool Image::Union(int pixel1, int pixel2){
    return this->pixels->Union(pixel1,pixel2);
}
