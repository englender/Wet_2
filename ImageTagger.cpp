//
// Created by nadav on 1/8/2019.
//

#include "ImageTagger.h"

ImageTagger::ImageTagger(int pixels) : size(START_SIZE), num_images(0), num_pixels(pixels){
    this->images= new Node_list<int,Image*>*[START_SIZE];

    for (int i = 0; i < this->size ; i++)
        this->images[i]= new Node_list<int,Image*>();


}

ImageTagger::~ImageTagger() {

    for (int i = 0; i < this->size ; i++)
        delete this->images[i];

    delete[] images;
}

bool ImageTagger::add_image(int imageID) {
    if(find_image(imageID) != nullptr)
        return false;

    check_and_expand();

    this->images[hash_func(imageID,this->size)]->add_node(imageID,new Image(imageID, this->num_pixels));
    (this->num_images)++;

    return true;
}



bool ImageTagger::delete_image(int imageID) {
    ListNode<int,Image*>*tmp_ptr=find_image(imageID);
    if(tmp_ptr == nullptr)
        return false;

    this->images[hash_func(imageID,this->size)]->remove_node(tmp_ptr);

    (this->num_images)--;
    check_and_shrink();
    return true;
}


void ImageTagger::check_and_expand() {
    if((this->num_images/this->size)<LOAD_FACTOR)
        return;

    int new_size=this->size*2;
    Node_list<int,Image*>** new_images=new Node_list<int,Image*>*[new_size];
    for (int i = 0; i < new_size ; i++)
        new_images[i]= new Node_list<int,Image*>();

    for (int j = 0; j < this->size; j++) {
        ListNode<int,Image*>* tmp_ptr=this->images[j]->get_first();
        while(tmp_ptr!= nullptr){
            new_images[hash_func(tmp_ptr->get_key(),new_size)]->add_node(tmp_ptr->get_key(),tmp_ptr->get_data());
            tmp_ptr->set_data(nullptr);
            tmp_ptr=tmp_ptr->get_next();
        }
    }

    for (int i = 0; i < this->size ; i++)
        delete this->images[i];

    delete[] this->images;

    this->images=new_images;
    this->size=new_size;
}


void ImageTagger::check_and_shrink() {
    if(size<=START_SIZE || num_images/size<EMPTY_FACTOR)
        return;

    int new_size=this->size/2;
    Node_list<int,Image*>** new_images=new Node_list<int,Image*>*[new_size];

    for (int i = 0; i < new_size ; i++)
        new_images[i]= new Node_list<int,Image*>();

    for (int j = 0; j < this->size; j++) {
        ListNode<int,Image*>* tmp_ptr=this->images[j]->get_first();
        while(tmp_ptr!= nullptr){
            new_images[hash_func(tmp_ptr->get_key(),new_size)]->add_node(tmp_ptr->get_key(),tmp_ptr->get_data());
            tmp_ptr->set_data(nullptr);
            tmp_ptr=tmp_ptr->get_next();
        }
    }

    for (int i = 0; i < this->size ; i++)
        delete this->images[i];

    delete[] this->images;

    this->images=new_images;
    this->size=new_size;
}

ListNode<int,Image*>* ImageTagger::find_image(int imageID) {
    int index=hash_func(imageID, this->size);
//    if (this->images[index]->get_size()==0)
//        return
    return this->images[index]->find(imageID);
}

int ImageTagger::hash_func(int imageID, int size){
    return imageID%size;
}

int ImageTagger::get_num_pixels(){
    return this->num_pixels;
}

bool ImageTagger::set_label_score(int imageID, int pixel, int label,
                                  int score) {

    ListNode<int,Image*>*tmp_ptr=find_image(imageID);
    if(tmp_ptr == nullptr)
        return false;

    tmp_ptr->get_data()->set_label_score(pixel,label,score);
    return true;
}

bool ImageTagger::reset_label_score(int imageID, int pixel, int label) {
    ListNode<int,Image*>*tmp_ptr=find_image(imageID);
    if(tmp_ptr == nullptr)
        return false;

    return tmp_ptr->get_data()->delete_label(pixel,label);
}