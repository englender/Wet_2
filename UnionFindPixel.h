//
// Created by nadav on 1/2/2019.
//

#ifndef EX4_UNIONFINDPIXEL_H
#define EX4_UNIONFINDPIXEL_H

//#include "SuperPixel.h"
#include "map_tree.h"
class UnionFindPixel {
    int num_of_pixels;      //needs only for printing function
    int* size;
    int* parent;
    Map_tree<int,int>** labels;             //array of trees?

public:
    UnionFindPixel(int pixels);
    ~UnionFindPixel();

/*
 * Description: finds index of the superpixel that pixel_ID belongs to. calls find_recurse
 * to find the parent.
 * Input:   pixel_ID - the pixel to find the parent
 * Output:  new_parent - the ID of the parent of pixel_ID
 */
    int find(int pixel_ID);                             //return index of the "super pixel"

/*
 * Description: finds index of the superpixel that pixel_ID belongs to. calls find_recurse
 * to find the parent.
 * Input:   pixel_ID - the pixel to find the parent
 *          parent - array of the parents of the pixels
 * Output:  new_parent - the ID of the parent of pixel_ID
 */
    static int find_recurse(int pixel_id, int* parent);

/*
 * Description: merges two superpixels to become one superpixel.
 * merges the label trees to one label tree
 * Input:   pixel1 - the pixelID that is part of the first superpixel to merge
 *          pixel2 - the pixelID that is part of the second superpixel to merge
 * Output:  false - if the two pixels belong to the same superpixel
 *          true - if the merging succeeded
 */
    bool Union(int pixel1, int pixel2);

/*
 * Description: merges two binary search trees into one.
 * time complexity O(n). n - number of nodes total
 * Input:   tree1 - the first tree to merge
 *          tree2 - the second tree to merge
 * Output:  new_tree - the combined tree
 */
    Map_tree<int,int>* merge_trees(Map_tree<int,int>* tree1, Map_tree<int,int>* tree2);

/*
 * Description: receives a binary search tree and transforms it to sorted array
 * allocates new array
 * time complexity O(n). n - number of nodes in tree
 * Input:   tree - tree to turn into array
 * Output:  array - sorted array of nodes from tree
 */
    static TreeNode<int,int>** tree_to_array(Map_tree<int,int>* tree);          //inserting tree to array by in-order scan

/*
 * Description: creates array from tree recursively.
 * Input:   current - current node in tree (starts from root)
 *          array_to_fill - the created array
 *          index - the current index in the array to fill
 * Output:  none
 */
    static void tree_to_array_recurse(TreeNode<int,int>* current, TreeNode<int,int>** array_to_fill, int *index);

/*
 * Description: receives two sorted arrays and merges them into one sorted array
 * Input:   array1 - the first array to merge
 *          size1 - the size of the first array
 *          array2 - the second array to merge
 *          size2 - the size of the second array
 * Output:  new_array - the merged sorted array
 */
    static TreeNode<int,int>** merge_arrays(TreeNode<int,int>** array1,int size1,
                                              TreeNode<int,int>** array2, int size2, int *final_size);

/*
 * Description: builds an empty complete AVL tree in the size that is received.
 * first builds a full AVL tree the deletes the necassery amount of right leaves
 * Input:   size - the size of the final tree
 * Output: empty_tree - the built complete AVL tree
 */
    Map_tree<int,int>* build_complete_tree(int size);

/*
 * Description: Builds an empty full tree
 * Input:   current - the current treenode in the tree
 *          height - the current height of the tree
 * Output:  none
 */
    static void build_recurse(TreeNode<int,int>* current, int height);

/*
 * Description: deletes the unnecessary leaves in a full tree to make it a complete tree
 * Input:   tree - the tree that needs to delete its leaves
 *          num_to_delete - the amount of leaves that need to be deleted
 *          height - the height of the tree
 *Output:   none.
 */
    void delete_right_leaves(Map_tree<int,int>* tree, int num_to_delete, int height);

/*
 * Description: deletes the unnecessary leaves in a full tree to make it a complete tree
 *Input:    current - the current treenode
 *          num_to_delete - the amount of leaves that need to be deleted
 *          height - the height of the tree
 *Output:   none.
 */
    void delete_right_leaves_recurse(TreeNode<int,int>* current, int* num_to_delete, int height);

/*
 * Description: inserts a sorted array to an AVL tree (the same size as array) inorder
 * Input:   tree - the tree to insert the array into
 *          array - the sorted array that needs to be inserted
 *Output:   none
 */
    void insert_array_to_tree(Map_tree<int,int>* tree,TreeNode<int,int>** array);

/*
 * Description: inserts a sorted array to an AVL tree (the same size as array) inorder
 * Input:   current - the current treenode to insert data into
 *          array - the sorted array that needs to be inserted
 *          index - the current index in array of the data to insert
 *          height - the height of the current treenode
 *Output:   none
 */
    void insert_array_to_tree_recurse(TreeNode<int,int>* current,TreeNode<int,int>** array, int* index, int height);

/*
 *Description: updates the max score of the tree (meaning of every node in the tree)
 * Input:   current - the current node to update max score (begins with root)
 * Output:  none
 */
    void update_max_score_recurse(TreeNode<int,int>* current);

/*
 * Description: adds a label with a score to the superpixel
 * Input:   pixel - the pixelID to find the superpixel it belongs to
 *          label - the label to add
 *          score - the score of the new label
 * Output:  none
 */
    void set_score_to_label(int pixel, int label, int score);

/*
 * Description: deletes and removes a label from the superpixel
 * Input:   pixel - the pixelID to find the superpixel it belongs to
 *          label - the label to remove
 * Output:  false - if there is no label as received in the superpixel
 *          true - if the label was removed
 */
    bool delete_label(int pixel, int label);//return true if label exist, else return false

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


//    ostream& printUnionFind(ostream& os);



    };


#endif //EX4_UNIONFINDPIXEL_H
