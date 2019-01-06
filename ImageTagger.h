//
// Created by ronien on 06/01/2019.
//

#ifndef NEW_WET2_IMAGETAGGER_H
#define NEW_WET2_IMAGETAGGER_H

#include "Image.h"

#define START_SIZE 8
#define EMPTY -1
#define DELETED -2

class ImageTagger {
    int* images_ids;
    Image** images;
    int size;
    int num_images;
    int num_pixels;

public:
    ImageTagger(int pixels);
    bool add_image(int imageID);
    bool delete_image(int imageID);
    int find_image(int imageID);
    int hash_func(int k, int imageID);

    int find_index_to_insert(int* array,int ImageID);

    void check_and_expand();
    void check_and_shrink();

    int get_num_pixels();

    bool set_label_score(int imageID, int pixel, int label, int score);
    bool reset_label_score( int imageID, int pixel, int label);

    Image* get_image_by_index(int index);
};


#endif //NEW_WET2_IMAGETAGGER_H
