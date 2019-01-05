//
// Created by nadav on 11/29/2018.
//

#ifndef EX2_MAP_TREE_H
#define EX2_MAP_TREE_H

#include <iostream>
#include <algorithm>
//#include "map_tree.cpp"
//#include "library1.h"

using namespace std;
#define MAX_BF 2
#define MIN_BF -2
#define EVEN_BF 0

template <class K, class D>
class TreeNode{
    K key;
    D data;
    int max_score;
    int height;

    TreeNode* left_son;
    TreeNode* right_son;
public:
    TreeNode(const K& key, const D& data);
//    ~TreeNode();

/*
 * Description: gets the node's key
 * Input:   none.
 * Output:  the node's key
 */
    const K& get_key();

/*
 * Description: gets the node's data
 * Input:   none.
 * Output:  the node's data
 */
    D& get_data();

/*
 * Description: sets the node's key
 * Input:   the key to set
 * Output:  none.
 */
    void set_key(K key);

/*
 * Description: sets the node's data
 * Input:   the data to ser.
 * Output:  none
 */
    void set_data(D data);

/*
 * Description: sets the node's max_score
 * Input:   the score to set.
 * Output:  none
 */
    void set_max_score(int score);

    int get_max_score();

    void update_max_score();

/*
 * Description: gets the node's height
 * Input:   none.
 * Output:  the node's height
 */
    const int get_height();

/*
 * Description: gets the node's left son
 * Input:   none.
 * Output:  the node's left son
 */
    TreeNode* get_left_son();

/*
 * Description: gets the node's right son
 * Input:   none.
 * Output:  the node's right son
 */
    TreeNode* get_right_son();

/*
 * Description: sets the node's left son
 * Input:   left_son - the node's new left son
 * Output:  none.
 */
    void set_left_son(TreeNode* left_son);

/*
 * Description: sets the node's right son
 * Input:   right_son - the node's new right son
 * Output:  none.
 */
    void set_right_son(TreeNode* right_son);

/*
 * Description: sets the node's height - the max height between his sons +1
 * if the node has no sons - height is set to 0
 * Input:   none.
 * Output:  none.
 */
    void set_height();

/*
 * Description: gets the node's right son height
 * Input:   none.
 * Output:  the node's right son height
 */
    int get_right_height();

/*
 * Description: gets the node's left son height
 * Input:   none.
 * Output:  the node's left son height
 */
    int get_left_height();

/*
 * Decription: returns node's balance factor - the difference between left son height and right son height
 * Input:   none.
 * Output:  node's balance factor
 */
    int get_balance_factor();

/*
 * Description: inside function for printing
 * prints "Key: XXX | Left: XXX | Right: XXX | Height: XXX | BF: XXX "
 */
    ostream& printNode(ostream& os);

};

template <class K, class D>
class Map_tree {
    TreeNode<K,D>* root;
    int size;

public:
    Map_tree();
    ~Map_tree();

/*
 * Description: removes all nodes in the tree
 * function called from Map_tree destructor
 * Input:   node_to_delete - the tree's root
 * Output:  none.
 */
    void delete_recurse(TreeNode<K,D>* node_to_delete);

/*
 * Description: gets the tree's root
 * Input:   none.
 * Output:  the tree's root
 */
    TreeNode<K,D>* get_root();

/*
 * Description: sets the tree's root
 * Input:   the tree's new root to set
 * Output:  none.
 */
    void set_root(TreeNode<K,D>* new_root);

/*
 * Description: gets the tree's size
 * Input:   none.
 * Output:  the tree's size
 */
    int get_size() const;

/*
 * Description: find's the node with the given key, using recurse finc find_recurse
 * Input:   key - the key of the node to find
 * Output:  the node with the given key. if there is no node in the tree with the key, returns null
 */
    TreeNode<K,D>* find(const K& key);

/*
 * Description: finds the node with the sent key
 * Input:   key - the requested key to find
 *          current_node - first iteration the tree's root, afterwards the current node
 * Output:  node_ptr - the node with the same key
 *          if there is no node with the key in the tree, returns nullptr
 */
    TreeNode<K,D>* find_recurse(const K& key, TreeNode<K,D>* current_node);

/*
 * Description: finds the node's father and adds it to the tree as his son
 * corrects the BF of the tree after adding the node, and updates the trees size
 * Input:   key - the key of new node to add
 *          data - the data of new node to add
 * Output:  none
 */
    void add_node(const K& key,const D& data);

/*
 * Description: finds the node to remove's father and removes him as his son
 * then removes the node from the tree
 * corrects BF of tree after removing the node
 * Input:   node_to_remove - the required node to remove.
 * Output:  none.
 */
    void remove_node(TreeNode<K,D>* node_to_remove);

/*
 * Description: corrects the BF of the tree after adding a new node
 * Input:   key - the key of the new node that was added
 *          current_node - first iteration the tree's root, afterwards the current node
 *          papa - first iteration nullptr, afterwards the current nodes father
 * Output:  none.
 */
    void add_correct(const K& key, TreeNode<K,D>* current_node, TreeNode<K,D>* papa);

/*
 * Description: If a node has BF of 2, executes roll to the left
 * is called in add_correct/delete_correct after adding/removing a node
 * checks if need to roll LL or LR
 * Input:   current_node - the node with BF = 2
 * Output:  the new root of the tree that had BF = 2
 */
    TreeNode<K,D>* roll_left(TreeNode<K,D>* current_node);

/*
 * Description: If a node has BF of -2, executes roll to the right
 * is called in add_correct/delete_correct after adding/removing a node
 * checks if need to roll RL or RR
 * Input:   current_node - the node with BF = -2
 * Output:  the new root of the tree that had BF = -2
 */
    TreeNode<K,D>* roll_right(TreeNode<K,D>* current_node);

/*
 * Description: If node has BF = 2, and his left son has BF >= 0
 * Input:   b - is root of mini-tree, BF = 2
 *          a - is left son of b, BF >=0 (a<b)
 * Output:  a - new root of mini-tree
 */
    TreeNode<K,D>* roll_LL(TreeNode<K,D>* b, TreeNode<K,D>* a);

/*
 * Description: If node has BF = -2, and his left son has BF >= 0
 * Input:   a - is root of mini-tree, BF = -2
 *          b - is right son of a, BF <=0 (a<b)
 * Output:  b - new root of mini-tree
 */
    TreeNode<K,D>* roll_RR(TreeNode<K,D>* b, TreeNode<K,D>* a);

/*
 * Description: If node has BF = 2, and his left son has BF >= 0
 * Input:   c - is root of mini-tree, BF = 2
 *          a - is left son of c, BF = -1
 *          b - is right son of a (a<b<c)
 * Output:  b - new root of mini-tree
 */
    TreeNode<K,D>* roll_LR(TreeNode<K,D>* c, TreeNode<K,D>* b, TreeNode<K,D>* a);

/*
 * Description: If node has BF = -2, and his left son has BF = 1
 * Input:   a - is root of mini-tree, BF = -2
 *          c - is right son of a, BF = 1
 *          b - is left son of c (a<b<c)
 * Output:  b - new root of mini-tree
 */
    TreeNode<K,D>* roll_RL(TreeNode<K,D>* c, TreeNode<K,D>* b, TreeNode<K,D>* a);

/*
 * Description: receives a father node and son node and connects between them
 * if key_son<key_papa then connects tmp_son as left son, else as right son
 * is called after removing a node or after executing a roll
 * Input:   papa - the father node of tmp son
 *          tmp_son - the son of papa
 * Output:  none.
 */
    void reconnect_to_papa(TreeNode<K,D>* papa, TreeNode<K,D>* tmp_son);

/*
 * Description: finds the father of the required node
 * Input:   key - key of node to add/remove
 *          current_node - first iteration the tree's root, afterwards the current node
 * Output:  papa - the father of the node to add/remove
 */
    TreeNode<K,D>* find_papa(const K& key, TreeNode<K,D>* current_node);

/*
 * Description: inside function for printing
 */
    ostream& printTree(ostream& os);

/*
 * Description: inside function for printing. recursive func called from printTree
 */
    ostream& print(ostream& os, TreeNode<K,D>* node_to_print);

/*
 * Description: deletes the node_to_remove and updates the fathers son to nullptr
 * Input:   papa - the node_to_remove father
 *          node_to_remove - the node that is to be removed from the tree
 * Output:  none.
 */
    void remove_son_with_no_grandsons(TreeNode<K,D>* papa, TreeNode<K,D>* node_to_remove) ;

/*
 * Description: deletes the node_to_remove and updates the fathers son accordingly
 * Input:   papa - the node_to_remove father
 *          node_to_remove - the node that is to be removed from the tree
 * Output:  none.
 */
    void remove_son_with_one_grandson(TreeNode<K,D>* papa, TreeNode<K,D>* node_to_remove) ;

/*
 * Description: deletes the node_to_remove and updates the fathers son accordingly
 * Input:   papa - the node_to_remove father
 *          node_to_remove - the node that is to be removed from the tree
 * Output:  none.
 */
    void remove_son_with_two_grandson(TreeNode<K,D>* papa, TreeNode<K,D>* node_to_remove) ;

/*
 * Description: receives two nodes and swaps their right sons
 * Input:   a - the node_to_remove
 *          b - the node_to_switch
 * Output:  none.
 */
    void swap_right_sons(TreeNode<K,D>* a,TreeNode<K,D>* b);

/*
 * Description: corrects the BF of the tree after removing a node
 * Input:   key - the key of the node that was removed
 *          current_node - first iteration the tree's root, afterwards the current node
 *          papa - first iteration nullptr, afterwards the current nodes father
 * Output:  none.
 */
    void delete_correct(const K& key, TreeNode<K,D>* current_node, TreeNode<K,D>* papa);

    };


//----------------------------------------------------------------------------//
//------------------------------TreeNode Implement--------------------------------//
//----------------------------------------------------------------------------//
template <class K, class D>
TreeNode<K,D>::TreeNode(const K& key, const D& data) : key(key), data(data),max_score(0),
                                                       height(0), left_son(nullptr),
                                                       right_son(nullptr){
}

//template <class K, class D>
//TreeNode<K,D>::~TreeNode(){
//    delete &data;
//    delete &key;
//}

template <class K, class D>
const K& TreeNode<K,D>::get_key() {
    return this->key;
}

template <class K, class D>
D& TreeNode<K,D>::get_data() {
    return this->data;
}

template <class K, class D>
void TreeNode<K,D>::set_key(K key) {
    this->key=key;
}

template <class K, class D>
void TreeNode<K,D>::set_data(D data) {
    this->data=data;
}

template <class K, class D>
void TreeNode<K,D>::set_max_score(int score){
    this->max_score=score;
}

template <class K, class D>
int TreeNode<K,D>::get_max_score(){
    return this->max_score;
}

template <class K, class D>
void TreeNode<K,D>::update_max_score(){
    int score_left = this->get_left_son()->get_max_score();
    int score_right = this->get_right_son()->get_max_score();

    if(score_left>=score_right){                //?????
        this->set_max_score(score_left);
    } else {
        this->set_max_score(score_right);
    }
}

template <class K, class D>
TreeNode<K,D>* TreeNode<K,D>::get_left_son(){
    if(this->left_son== nullptr){
        return nullptr;
    }
    return this->left_son;
}

template <class K, class D>
TreeNode<K,D>* TreeNode<K,D>::get_right_son(){
    if(this->right_son== nullptr){
        return nullptr;
    }
    return this->right_son;
}

template <class K, class D>
void TreeNode<K,D>::set_left_son(TreeNode<K,D>* left_son){
    if(left_son== nullptr)
        this->left_son= nullptr;
    else{
        this->left_son=left_son;
    }
}

template <class K, class D>
void TreeNode<K,D>::set_right_son(TreeNode<K,D>* right_son){
    if(right_son== nullptr)
        this->right_son= nullptr;
    else{
        this->right_son=right_son;
    }
}

template <class K, class D>
void TreeNode<K,D>::set_height(){
    int left_height=this->get_left_height();
    int right_height=this->get_right_height();
    this->height=(std::max(left_height,right_height)+1);
}

template <class K, class D>
const int TreeNode<K,D>::get_height(){
   return this->height;
}

template <class K, class D>
int TreeNode<K,D>::get_right_height(){
    if(this->right_son == nullptr)
        return -1;
    return this->right_son->height;
}

template <class K, class D>
int TreeNode<K,D>::get_left_height(){
    if(this->left_son == nullptr)
        return -1;
    return this->left_son->height;
}

template <class K, class D>
int TreeNode<K,D>::get_balance_factor(){
    return (this->get_left_height())-(this->get_right_height());
}

template <class K, class D>
ostream& TreeNode<K,D>::printNode(ostream& os) {
    os << "Key: " << this->get_key() << " | Left: ";
    if(this->get_left_son()== nullptr)
        os << "-";
    else
        os << this->get_left_son()->get_key();

    os << " | Right: ";
    if(this->get_right_son()== nullptr)
        os << "-";
    else
        os << this->get_right_son()->get_key();
    os << " | Height: " << this->height << " | BF: " << this->get_balance_factor();


    os << endl;

    return os;
}



//----------------------------------------------------------------------------//
//------------------------------TreeNode Tree Implement---------------------------//
//----------------------------------------------------------------------------//

template <class K, class D>
Map_tree<K,D>::Map_tree() : root(nullptr),size(0){
}

template <class K, class D>
Map_tree<K,D>::~Map_tree() {
    delete_recurse(this->root);
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::get_root(){
    return this->root;
}
template <class K, class D>
void Map_tree<K,D>::set_root(TreeNode<K,D>* new_root){
    this->root=new_root;
}

template <class K, class D>
int Map_tree<K,D>::get_size() const{
    return this->size;
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::find(const K& key){
    return find_recurse(key,this->root);
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::find_recurse(const K& key, TreeNode<K,D>* current_node) {
    if (current_node == nullptr)                //stop conditions - arrived at bottom of the tree
        return nullptr;

    else if (current_node->get_key() == key)    //stop conditions - found the required node
        return current_node;

    TreeNode<K, D> *node_ptr;
    if (current_node->get_key() > key) {        //the required key is smaller than the current, continue left
        node_ptr = find_recurse(key, current_node->get_left_son());
    } else {                                    //the required key is bigger than the current, continue right
        node_ptr=find_recurse(key, current_node->get_right_son());
    }
    return node_ptr;                            // ?????? roni - not sure we need this ??????
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::find_papa(const K& key, TreeNode<K,D>* papa) {
    if(papa == nullptr || papa->get_key()==key){
        return nullptr;
    }
    if(papa->get_right_son()== nullptr && papa->get_left_son()== nullptr)
        return papa;
    if(papa->get_key()<key && papa->get_right_son()!= nullptr &&
            papa->get_right_son()->get_key()==key)
        return papa;                //papa_key<key and also it has right_son_key==key
    if(papa->get_key()<key && papa->get_right_son()== nullptr)
        return papa;                //if papa_key<key and also it has no right son
    if(papa->get_key()>key && papa->get_left_son()!= nullptr &&
            papa->get_left_son()->get_key()==key)
        return papa;                //papa_key>key and also it has left_son_key==key
    if(papa->get_key()>key && papa->get_left_son()== nullptr)
            return papa;            //if papa_key>key and also it has no left son

    if(papa->get_key()<key)         //the required key is bigger than the current, continue right
        return find_papa(key,papa->get_right_son());

    return find_papa(key,papa->get_left_son());
}


template <class K, class D>
void Map_tree<K,D>::add_node(const K& key,const D& data){
    TreeNode<K,D>* new_node = new TreeNode<K,D>(key, data);
    TreeNode<K,D>* papa=this->find_papa(new_node->get_key(),this->get_root());

    if(papa== nullptr)                                  // Empty tree
        this->set_root(new_node);
    else if(papa->get_key() > new_node->get_key()){
        papa->set_left_son(new_node);
    }else{
        papa->set_right_son(new_node);
    }
    add_correct(new_node->get_key(),this->get_root(), nullptr);
    this->size++;

}

template <class K, class D>
void Map_tree<K,D>::remove_node(TreeNode<K,D>* node_to_remove) {
    TreeNode<K,D>* papa=find_papa(node_to_remove->get_key(), this->get_root());
    K* key=new K(node_to_remove->get_key());
    if(node_to_remove->get_right_son()== nullptr &&
            node_to_remove->get_left_son()== nullptr) {              //no grandsons

        remove_son_with_no_grandsons(papa, node_to_remove);
    }
    else if(node_to_remove->get_right_son()== nullptr ||
             node_to_remove->get_left_son()== nullptr){             //only one grandson
        remove_son_with_one_grandson(papa, node_to_remove);
    }else{
        remove_son_with_two_grandson(papa, node_to_remove);
    }
    delete_correct(*key,this->get_root(), nullptr);
    delete key;
    this->size--;
}

template <class K, class D>
void Map_tree<K,D>::delete_recurse(TreeNode<K,D>* node_to_delete){
    if(node_to_delete== nullptr)
        return;

    delete_recurse(node_to_delete->get_left_son());
    delete_recurse(node_to_delete->get_right_son());
    delete node_to_delete;

}

template <class K, class D>
void Map_tree<K,D>::remove_son_with_no_grandsons(TreeNode<K,D>* papa,
                                                 TreeNode<K,D>* node_to_remove) {
    if(papa == nullptr){                         //then node to remove is root
        this->set_root(nullptr);
    }
    else if(node_to_remove->get_key()>papa->get_key()) {          //then node to remove is papa's right son
        papa->set_right_son(nullptr);
    }else{
        papa->set_left_son(nullptr);
    }
    delete node_to_remove;
}

template <class K, class D>
void Map_tree<K,D>::remove_son_with_one_grandson(TreeNode<K,D>* papa,
                                                 TreeNode<K,D>* node_to_remove) {

    if(node_to_remove->get_right_son()!= nullptr)
        reconnect_to_papa(papa,node_to_remove->get_right_son());
    else
        reconnect_to_papa(papa,node_to_remove->get_left_son());

    delete node_to_remove;
}

template <class K, class D>
void Map_tree<K,D>:: remove_son_with_two_grandson(TreeNode<K,D>* papa,
                                                  TreeNode<K,D>* node_to_remove) {
    TreeNode<K, D> *node_to_switch = node_to_remove->get_right_son();
    TreeNode<K, D> *node_to_switch_PAPA = node_to_remove;
    while(node_to_switch->get_left_son()!= nullptr){
        node_to_switch_PAPA=node_to_switch;
        node_to_switch=node_to_switch->get_left_son();
    }
    TreeNode<K, D> *tmp_ptr = node_to_remove->get_left_son();
    node_to_remove->set_left_son(nullptr);
    node_to_switch->set_left_son(tmp_ptr);

    swap_right_sons(node_to_remove,node_to_switch);
    reconnect_to_papa(papa,node_to_switch);

    if(node_to_switch_PAPA!=node_to_remove) {             //example 2,3
        reconnect_to_papa(node_to_switch_PAPA, node_to_remove);
        if (node_to_remove->get_right_son() != nullptr) {
            node_to_switch_PAPA->set_left_son(node_to_remove->get_right_son());
        } else {
            node_to_switch_PAPA->set_left_son(nullptr);
        }
    }
    else{                                               //node_to_switch_PAPA=node_to_remove. example 1,4
        if (node_to_remove->get_right_son() != nullptr){
            tmp_ptr=node_to_remove->get_right_son();
            node_to_remove->set_right_son(nullptr);
            node_to_switch->set_right_son(tmp_ptr);
        }else{
            node_to_switch->set_right_son(nullptr);
        }
    }
    delete node_to_remove;

}

template <class K, class D>
void Map_tree<K,D>::swap_right_sons(TreeNode<K,D>* a,TreeNode<K,D>* b) {
    if(a->get_right_son()==b){
        TreeNode<K,D> *tmp=b->get_right_son();
        b->set_right_son(a);
        a->set_right_son(tmp);

    }else{
        TreeNode<K,D> *tmp=a->get_right_son();
        a->set_right_son(b->get_right_son());
        b->set_right_son(tmp);
    }
}

//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//


template <class K, class D>
ostream& Map_tree<K,D>::printTree(ostream& os) {
    TreeNode<K,D>* current_node=this->get_root();
    if(current_node == nullptr)
        return os << "Empty Tree!!!" << endl;
    return this->print(os, this->get_root());

}

template <class K, class D>
ostream& Map_tree<K,D>::print(ostream& os, TreeNode<K,D>* node_to_print){
    node_to_print->printNode(os);
    if(node_to_print->get_left_son()!= nullptr)
        this->print(os,node_to_print->get_left_son());

    if(node_to_print->get_right_son()!= nullptr)
        this->print(os,node_to_print->get_right_son());

    return os;
}

//----------------------------------------------------------------------------//
//------------------------------Roll Implement--------------------------------//
//----------------------------------------------------------------------------//

template <class K, class D>
void Map_tree<K,D>::add_correct(const K& key, TreeNode<K,D>* current_node, TreeNode<K,D>* papa){
    if (current_node->get_key() == key) {
        return;
    }
    TreeNode<K,D>* tmp_ptr;
    if (current_node->get_key() > key) {
        add_correct(key, current_node->get_left_son(),current_node);
        current_node->set_height();
        if(current_node->get_balance_factor()==MAX_BF) {
            if (papa == nullptr)
                this->set_root(roll_left(current_node));
            else {
                tmp_ptr = roll_left(current_node);
                reconnect_to_papa(papa, tmp_ptr);
            }
        }
    } else {
        add_correct(key, current_node->get_right_son(),current_node);
        current_node->set_height();
        if(current_node->get_balance_factor()==MIN_BF) {
            if (papa == nullptr)
                this->set_root(roll_right(current_node));
            else {
                tmp_ptr = roll_right(current_node);
                reconnect_to_papa(papa, tmp_ptr);
            }
        }
    }

}

template <class K, class D>
void Map_tree<K,D>::delete_correct(const K& key, TreeNode<K,D>* current_node, TreeNode<K,D>* papa) {
    if (current_node == nullptr) {
        return;
    }
    TreeNode<K,D>* tmp_ptr;
    if (current_node->get_key() > key) {
        delete_correct(key, current_node->get_left_son(), current_node);
    } else {
        delete_correct(key, current_node->get_right_son(), current_node);
    }
    current_node->set_height();

    if (current_node->get_balance_factor() == MAX_BF) {
        if (papa == nullptr) {
            this->set_root(roll_left(current_node));
        }
        else {
            tmp_ptr = roll_left(current_node);
            reconnect_to_papa(papa, tmp_ptr);
        }
    }
    else if(current_node->get_balance_factor()==MIN_BF){
        if(papa== nullptr) {
            this->set_root(roll_right(current_node));
        }
        else {
            tmp_ptr = roll_right(current_node);
            reconnect_to_papa(papa, tmp_ptr);
        }
    }
}


template <class K, class D>
void Map_tree<K,D>::reconnect_to_papa(TreeNode<K,D>* papa, TreeNode<K,D>* tmp_son){

    if(papa== nullptr){                         //if(tmp_son==root)
        this->set_root(tmp_son);
        return;
    }
    if(tmp_son->get_key()>papa->get_key()){

        papa->set_right_son(tmp_son);
    }else{
        papa->set_left_son(tmp_son);
    }
}



template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_left(TreeNode<K,D>* current_node){
    if(current_node->get_left_son()->get_balance_factor()>=EVEN_BF){
        return roll_LL(current_node,current_node->get_left_son());
    }
    else{
        return roll_LR(current_node,current_node->get_left_son()->get_right_son(),
                current_node->get_left_son());
    }
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_right(TreeNode<K,D>* current_node){
    if(current_node->get_right_son()->get_balance_factor()<=EVEN_BF) {
        return roll_RR(current_node->get_right_son(), current_node);
    }
    else{
        return roll_RL(current_node->get_right_son(),
                current_node->get_right_son()->get_left_son(),current_node);
    }
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_LL(TreeNode<K,D>* b, TreeNode<K,D>* a){
// b is root: BF=2
// a is left son of b: BF>=0
// a<b
    b->set_left_son(a->get_right_son());
    a->set_right_son(b);

    b->set_height();
    a->set_height();

    if(b==this->root)
        this->root=a;
    return a;
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_RR(TreeNode<K,D>* b, TreeNode<K,D>* a){
// a is root: BF=-2
// b is right son of a: BF<=0
// a<b
    a->set_right_son(b->get_left_son());
    b->set_left_son(a);

    a->set_height();
    b->set_height();

    if(a==this->root)
        this->root=b;

    return b;
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_LR(TreeNode<K,D>* c, TreeNode<K,D>* b, TreeNode<K,D>* a){
// c is root: BF=2
// a is left son of c: BF=-1
// b is right son of a
// a<b<c
    a->set_right_son(b->get_left_son());
    b->set_left_son(a);
    c->set_left_son(b);             //not sure if necessary

    c->set_left_son(b->get_right_son());
    b->set_right_son(c);

    c->set_height();
    a->set_height();
    b->set_height();

    if(c==this->root)
        this->root=b;

    return b;

}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_RL(TreeNode<K,D>* c, TreeNode<K,D>* b, TreeNode<K,D>* a) {
// a is root: BF=-2
// c is right son of a: BF=1
// b is left son of c
// a<b<c
    a->set_right_son(b);
    c->set_left_son(b->get_right_son());             //not sure if necessary
    b->set_right_son(c);

    a->set_right_son(b->get_left_son());
    b->set_left_son(a);

    a->set_height();
    c->set_height();
    b->set_height();

    if(a==this->root)
        this->root=b;

    return b;
};
#endif //EX2_MAP_TREE_H
