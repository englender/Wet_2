//
// Created by nadav on 1/8/2019.
//

#ifndef ONCOMPUTER_IMAGETAGGER_H
#define ONCOMPUTER_IMAGETAGGER_H

#include "node_list.h"
#include "Image.h"
#include <math.h>

#define START_SIZE 8
#define GOLD_NUM ((sqrt(5)-1)/2)
#define LOAD_FACTOR 0.9
#define EMPTY_FACTOR 0.25


class ImageTagger {
    Node_list<int,Image*>** images;
    int size;
    int num_images;
    int num_pixels;

public:
    ImageTagger(int pixels);
    ~ImageTagger();
    bool add_image(int imageID);
    bool delete_image(int imageID);
    ListNode<int,Image*>* find_image(int imageID);
    int hash_func(int imageID, int size);

    void check_and_expand() ;
    void check_and_shrink() ;


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
//    Image* get_image_by_index(int index);
};


#endif //ONCOMPUTER_IMAGETAGGER_H
