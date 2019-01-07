//
// Created by ronien on 06/01/2019.
//

#include "library.h"
#include "ImageTagger.h"


void * Init(int pixels){
    if(pixels<=0)
        return NULL;
    ImageTagger* DS;

    try {
        DS = new ImageTagger(pixels);
    }catch(std::exception& e){
        return NULL;
    }
    return (void*)DS;
}

StatusType AddImage(void *DS, int imageID){
    if(DS== nullptr || imageID<=0){
        return INVALID_INPUT;
    }
    try {
        if (((ImageTagger *) DS)->add_image(imageID)) {
            return SUCCESS;
        }
    }catch (std::exception& e){
        return ALLOCATION_ERROR;
    }
    return FAILURE;
}

StatusType DeleteImage(void *DS, int imageID){
    if(DS== nullptr || imageID<=0){
        return INVALID_INPUT;
    }
    try {
        if (((ImageTagger *) DS)->delete_image(imageID)) {
            return SUCCESS;
        }
    }catch(std::exception& e){
        return ALLOCATION_ERROR;
    }
    return FAILURE;
}

StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score){
    if(DS== nullptr || pixel<0 || pixel>((ImageTagger*)DS)->get_num_pixels()
       || imageID<=0 || score<=0 || label<=0){
        return INVALID_INPUT;
    }
    try{
        if(((ImageTagger*)DS)->set_label_score(imageID,pixel,label,score)){
            return SUCCESS;
        }
    }catch(std::exception& e){
        return ALLOCATION_ERROR;
    }

    return FAILURE;
}

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label){
    if(DS== nullptr || pixel<0 || pixel>((ImageTagger*)DS)->get_num_pixels()
       || imageID<=0 || label<=0){
        return INVALID_INPUT;
    }
    try {
        if (((ImageTagger*)DS)->reset_label_score(imageID, pixel, label)) {
            return SUCCESS;
        }
    }catch(std::exception& e){
    return ALLOCATION_ERROR;
    }
    return FAILURE;
}

StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label){
    if(DS== nullptr || pixel<0 || pixel>((ImageTagger*)DS)->get_num_pixels()
       || imageID<=0 || label== nullptr){
        return INVALID_INPUT;
    }
    int index = ((ImageTagger*)DS)->find_image(imageID);
    if(index==EMPTY){
        return FAILURE;
    }
    if(!((ImageTagger*)DS)->get_image_by_index(index)->is_super_pixel_labeled(pixel))
        return FAILURE;

    *label=((ImageTagger*)DS)->get_image_by_index(index)->get_max_label_score(pixel);

    return SUCCESS;
}

StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2){

    if(DS== nullptr || imageID <=0 || pixel1<0 || pixel1>=((ImageTagger*)DS)->get_num_pixels() ||
            pixel2<0 || pixel2>=((ImageTagger*)DS)->get_num_pixels()){
        return INVALID_INPUT;
    }

    int index = ((ImageTagger*)DS)->find_image(imageID);
    if(index==EMPTY){
        return FAILURE;
    }
    try {
        if (!((ImageTagger *) DS)->get_image_by_index(index)->Union(pixel1,
                                                                    pixel2))
            return FAILURE;
    }catch(std::exception& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void Quit(void** DS){
    if(DS== nullptr || *DS==nullptr)
        return;

    delete ((ImageTagger*)*DS);
    *DS=NULL;

}