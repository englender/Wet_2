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

    int find(int pixel_ID);                             //return index of the "super pixel"
    static int find_recurse(int pixel_id, int* parent);
    bool Union(int pixel1, int pixel2);
    bool is_super_pixel_labeled(int pixel);
    int get_max_label_score(int pixel);
///---------------------------Merge Functions--------------------------------///

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
    static TreeNode<int,int>** merge_arrays(TreeNode<int,int>** array1,int size1,
                                              TreeNode<int,int>** array2, int size2, int *final_size);
    Map_tree<int,int>* build_complete_tree(TreeNode<int,int>** array, int size);
    static void build_recurse(TreeNode<int,int>* current, int height);
    void delete_right_leaves(Map_tree<int,int>* tree, int num_to_delete, int height);
    void delete_right_leaves_recurse(TreeNode<int,int>* current, int* num_to_delete, int height);
    void insert_array_to_tree(Map_tree<int,int>* tree,TreeNode<int,int>** array);
    void insert_array_to_tree_recurse(TreeNode<int,int>* current,TreeNode<int,int>** array, int* index, int height);
    void update_max_score_recurse(TreeNode<int,int>* current);



///--------------------------------------------------------------------------///

    void set_score_to_label(int pixel, int label, int score);//return true if label exist, else return false
    bool delete_label(int pixel, int label);//return true if label exist, else return false

    ostream& printUnionFind(ostream& os);



    };


#endif //EX4_UNIONFINDPIXEL_H
