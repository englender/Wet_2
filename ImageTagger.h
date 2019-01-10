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

/*
 * Description: adds a new image to the images array
 * Input:   imageID - the imageID of the new image to add
 * Output:  true - if the new image was added
 *          false - if already exists and image with the same imageID in the array
 */
    bool add_image(int imageID);

/*
 * Description: deletes an image from the images array
 * Input:   imageID - the imageID to delete
 * Output:  true - if the image was deleted
 *          false - if there is no image with the imageID
 */
    bool delete_image(int imageID);

/*
 * Description: finds the image with imageID in the images array
 * Input:   imageID - the imageID of the image to find
 * Outpu:   the image with the imageID received. if there is no image, returns null
 */
    ListNode<int,Image*>* find_image(int imageID);

/*
 * Description: the function that determines where in the array a new image is inserted
 * Input:   imageID - the imageID of the new image to insert
 *          size - the size of the images arrat
 * Output:  the index in the images array to insert the new image
 */
    int hash_func(int imageID, int size);

/*
 * Description: Expands images array if necessary, meaning if load factor is LOAD_FACTOR
 * If expanding is necessary, expands the array to twice its size and inserts the images
 * again using the hash func.
 * the func is called after adding a new image to the array
 * Input:   none
 * Output:  none
 */
    void check_and_expand() ;

/*
 * Description: Shrinks images array if necessary, meaning if load factor is EMPTY_FACTOR
 * If shrinking is necessary, shrinks the array by half and inserts the images
 * again using the hash func.
 * the func is called after every image that is deleted from the array
 * Input:   none
 * Output:  none
 */
    void check_and_shrink() ;

/*
 * Description: Returns the number of pixels in each image as initalized in structure.
 * Input:   none
 * Output:  num_pixels in structure
 */
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
