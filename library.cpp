//
// Created by ronien on 06/01/2019.
//

#include "library.h"
#include "ImageTagger.h"


void * Init(int pixels){
    ImageTagger* DS = new ImageTagger(pixels);

    return DS;
}

StatusType AddImage(void *DS, int imageID){
    if(DS== nullptr || imageID<=0){
        return INVALID_INPUT;
    }
    if(((ImageTagger*)DS)->add_image(imageID)){
        return SUCCESS;
    }
    return FAILURE;
}

StatusType DeleteImage(void *DS, int imageID){
    if(DS== nullptr || imageID<=0){
        return INVALID_INPUT;
    }

    if(((ImageTagger*)DS)->delete_image(imageID)){
        return SUCCESS;
    }
    return FAILURE;
}

StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score){
    if(DS== nullptr || pixel<0 || pixel>((ImageTagger*)DS)->get_num_pixels()
       || imageID<=0 || score<=0 || label<=0){
        return INVALID_INPUT;
    }

    if(((ImageTagger*)DS)->set_label_score(imageID,pixel,label,score)){
        return SUCCESS;
    }
    return FAILURE;
}

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label){
    if(DS== nullptr || pixel<0 || pixel>((ImageTagger*)DS)->get_num_pixels()
       || imageID<=0 || label<=0){
        return INVALID_INPUT;
    }

    if(((ImageTagger*)DS)->reset_label_score(imageID,pixel,label)){
        return SUCCESS;
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

    *label=
}