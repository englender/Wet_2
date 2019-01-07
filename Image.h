//
// Created by nadav on 1/4/2019.
//

#ifndef EX4_IMAGE_H
#define EX4_IMAGE_H

#include "UnionFindPixel.h"

class Image {
    int imageID;
    UnionFindPixel *pixels;

public:
    Image(int imageID, int num_of_pixels);
    ~Image();

/*
 * Description: adds a label with a score to the superpixel
 * Input:   pixel - the pixelID to find the superpixel it belongs to
 *          label - the label to add
 *          score - the score of the new label
 * Output:  none
 */
    void set_label_score(int pixel, int label, int score);

/*
 * Description: deletes and removes a label from the superpixel
 * Input:   pixel - the pixelID to find the superpixel it belongs to
 *          label - the label to remove
 * Output:  false - if there is no label as received in the superpixel
 *          true - if the label was removed
 */
    bool delete_label(int pixel, int label);

/*
 * Description: determines wether a superpixel has any labels or no labels at all
 * Input:   pixel - the pixelID to find the superpixel it belongs to
 * Output:  false - the superpixel has no labels
 *          true - the superpixel is labeled
 */
    bool is_super_pixel_labeled(int pixel);

/*
 * Description: returns the highest score of a label in the superpixel
 * Input:   pixel - the pixelID to find the superpixel it belongs to
 * Output:  the highest score of a label in the superpixel
 */
    int get_max_label_score(int pixel);

/*
 * Description: merges two superpixels to become one superpixel.
 * merges the label trees to one label tree
 * Input:   pixel1 - the pixelID that is part of the first superpixel to merge
 *          pixel2 - the pixelID that is part of the second superpixel to merge
 * Output:  false - if the two pixels belong to the same superpixel
 *          true - if the merging succeeded
 */
    bool Union(int pixel1, int pixel2);
};


#endif //EX4_IMAGE_H
