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
    ~ImageTagger();
    bool add_image(int imageID);
    bool delete_image(int imageID);
    int find_image(int imageID);
    int hash_func(int k, int imageID);

    int find_index_to_insert(int* array,int imageID);

    void check_and_expand();
    void check_and_shrink();

    int get_num_pixels();

/*
 * Description: adds a label with a score to the superpixel in the required image
 * Input:   imageID - the image to add the label to
 *          pixel - the pixelID to find the superpixel it belongs to
 *          label - the label to add
 *          score - the score of the new label
 * Output:  false - if there is no image with the imageID
 *          true - if the label was added
 */
    bool set_label_score(int imageID, int pixel, int label, int score);

/*
 * Description: deletes and removes a label from the superpixel
 * Input:   imageID - the image to add the label to
 *          pixel - the pixelID to find the superpixel it belongs to
 *          label - the label to remove
 * Output:  false - if there is no label as received in the superpixel
 *          true - if the label was removed
 */
    bool reset_label_score( int imageID, int pixel, int label);

/*
 * Description: returns the image in the requested index in images array
 * Input:   index - the index that the image is in
 * Output   the image in place index in images array
 */
    Image* get_image_by_index(int index);
};


#endif //NEW_WET2_IMAGETAGGER_H
