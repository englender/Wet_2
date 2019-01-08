//
// Created by ronien on 06/01/2019.
//

#include "ImageTagger1.h"
#define PRIME 7

ImageTagger::ImageTagger(int pixels) : size(START_SIZE), num_images(0), num_pixels(pixels){
    this->images_ids = new int[START_SIZE];
    this->images= new Image*[START_SIZE];
    for (int i = 0; i <size ; i++) {
        this->images_ids[i]=EMPTY;
        this->images[i]= nullptr;
    }
}
ImageTagger::~ImageTagger() {
    delete[] images_ids;

    delete[] images;
}

bool ImageTagger::add_image(int imageID) {
    if(find_image(imageID)!=EMPTY)
        return false;

    check_and_expand();

    int index = find_index_to_insert(this->images_ids,imageID);
    this->images_ids[index]=imageID;
    this->images[index]= new Image(imageID, this->num_pixels);
    (this->num_images)++;

    return true;

}

int ImageTagger::find_image(int imageID) {
    int index=0;
    while(this->images_ids[hash_func(index,imageID)]!=imageID && index<num_images){
        index++;
    }
    if(this->images_ids[hash_func(index,imageID)]==imageID){
        return hash_func(index,imageID);
    }
    return EMPTY;

}





int ImageTagger::hash_func(int k, int imageID) {

    int tmp=imageID%PRIME;
    if(tmp%2==1)
        tmp--;
    return ((imageID%size + k*(1 + tmp))%size);

//    return (((imageID%size)+((2*imageID)+1))%size);

}






int ImageTagger::find_index_to_insert(int* array,int imageID){
    int index=0;
    while(array[hash_func(index,imageID)]!=EMPTY){
        index++;
    }
    return hash_func(index,imageID);
}

void ImageTagger::check_and_expand() {
    if(num_images<size)
        return;

    int new_size=this->size*2;
    int *new_id_array = new int[new_size];
    Image** new_images=new Image*[new_size];

    for (int i = 0; i < new_size; i++) {
        new_id_array[i]=EMPTY;
        new_images[i]= nullptr;
    }

    int index;
    for (int i = 0; i < this->size; i++) {
        if(this->images_ids[i]>EMPTY) {
            index = find_index_to_insert(new_id_array, images_ids[i]);
            new_id_array[index] = this->images_ids[i];
            new_images[index] = this->images[i];
            this->images[i] = nullptr;
        }
    }

    delete [] this->images_ids;
    delete [] this->images;

    this->images_ids=new_id_array;
    this->images=new_images;
    this->size=(new_size);
}

void ImageTagger::check_and_shrink() {
    if(num_images==0 ||size<=START_SIZE || size/num_images< 4)
        return;

    int new_size=this->size/2;
    int *new_id_array = new int[this->size/2];
    Image** new_images=new Image*[this->size/2];

    for (int i = 0; i < new_size; i++) {
        new_id_array[i]=EMPTY;
        new_images[i]= nullptr;
    }

    int index;
    for (int i = 0; i < this->size; i++) {
        if(this->images_ids[i]>EMPTY) {
            index = find_index_to_insert(new_id_array, images_ids[i]);
            new_id_array[index] = this->images_ids[i];
            new_images[index] = this->images[i];
            this->images[i] = nullptr;
        }
    }


    delete [] this->images_ids;
    delete [] this->images;

    this->images_ids=new_id_array;
    this->images=new_images;
    this->size=(new_size);
}

bool ImageTagger::delete_image(int imageID) {
    int index = find_image(imageID);
    if(index==EMPTY)
        return false;
    this->images_ids[index]=DELETED;
    delete this->images[index];
    this->images[index]= nullptr;

    (this->num_images)--;
    check_and_shrink();
    return true;
}

int ImageTagger::get_num_pixels(){
    return this->num_pixels;
}

bool ImageTagger::set_label_score(int imageID, int pixel, int label,
                                  int score) {
    int index = find_image(imageID);
    if(index==EMPTY)
        return false;

    this->images[index]->set_label_score(pixel,label,score);
    return true;

}

bool ImageTagger::reset_label_score(int imageID, int pixel, int label) {
    int index = find_image(imageID);
    if(index==EMPTY)
        return false;

    return this->images[index]->delete_label(pixel,label);
}

Image* ImageTagger::get_image_by_index(int index){
    return this->images[index];
}