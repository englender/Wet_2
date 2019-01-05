//
// Created by nadav on 1/2/2019.
//

#include "UnionFindPixel.h"
#include <math.h>

#define ROOT -1

UnionFindPixel::UnionFindPixel(int pixels):num_of_pixels(pixels) {
    this->size=new int[pixels];
    this->parent=new int[pixels];
    this->labels=new Map_tree<int,int>*[pixels];


    for (int i = 0; i < pixels; i++) {
        this->size[i]=1;
        this->parent[i]=ROOT;
        this->labels[i]=new Map_tree<int,int>();
    }
}

int UnionFindPixel::find(int pixel_ID) {
    return find_recurse(pixel_ID,this->parent);
}


int UnionFindPixel::find_recurse(int pixel_id, int* parent){
    if(parent[pixel_id]==ROOT)
        return pixel_id;

    int new_parent = find_recurse(parent[pixel_id], parent);
    parent[pixel_id]=new_parent;                                //shrinking routes
    return new_parent;
}

void UnionFindPixel:: Union(int pixel1, int pixel2){
    int root1=find(pixel1);
    int root2=find(pixel2);

    Map_tree<int,int>* new_tree=merge_trees(labels[root1],labels[root2]);
    delete labels[root1];
    delete labels[root2];


    if (size[root1]>size[root2]){
        parent[root2]=root1;
        size[root1]+=size[root2];
        size[root2]=0;
        labels[root1]=new_tree;
        labels[root2]=new Map_tree<int,int>();// same as initialize, needs to be nullptr ??
    }
    else{
        parent[root1]=root2;
        size[root2]+=size[root1];
        size[root1]=0;
        labels[root2]=new_tree;
        labels[root1]=new Map_tree<int,int>(); // same as initialize, needs to be nullptr ??
    }
//????????????? - needs to merge trees - assumption: only parent of superpixel have a label tree
}



Map_tree<int,int>* UnionFindPixel::merge_trees(Map_tree<int,int>* tree1, Map_tree<int,int>* tree2){
    TreeNode<int,int>** array1=tree_to_array(tree1);
    TreeNode<int,int>** array2=tree_to_array(tree2);

    TreeNode<int,int>** full_array=merge_arrays(array1,tree1->get_size(),array2,tree2->get_size());
    delete array1;
    delete array2;

    Map_tree<int,int>* new_tree=build_complete_tree(full_array,(tree1->get_size()+tree2->get_size()));
    insert_array_to_tree(new_tree,full_array);
    delete full_array;

    return new_tree;
}

TreeNode<int,int>** UnionFindPixel::tree_to_array(Map_tree<int,int>* tree){
    if(tree->get_size()==0){
        return nullptr;
    }
    TreeNode<int,int>** array = new TreeNode<int,int>*[tree->get_size()];
    tree_to_array_recurse(tree->get_root(),array,0);
    return array;
}

void UnionFindPixel::tree_to_array_recurse(TreeNode<int,int>* current,
                                           TreeNode<int,int>** array_to_fill,
                                           int index){
    if(current == nullptr)
        return;

    tree_to_array_recurse(current->get_left_son(),array_to_fill,index);
    array_to_fill[index]=current;
    index++;
    tree_to_array_recurse(current->get_right_son(),array_to_fill,index);
}

TreeNode<int,int>** UnionFindPixel::merge_arrays(TreeNode<int,int>** array1,int size1,
                                          TreeNode<int,int>** array2, int size2){
//
//    if(size1 == 0)
//        return array2;
//    if(size2 == 0)
//        return array1;
    int new_size= size1+size2;
    TreeNode<int,int>** new_array = new TreeNode<int,int>*[new_size];
    int i1, i2, i_new;
    for(i1 = i2 = i_new = 0; (i1<size1) && (i2<size2); i_new++){
        if(array1[i1]<array2[i2]){
            new_array[i_new]=array1[i1];
            i1++;
        } else{
            new_array[i_new]=array2[i2];
            i2++;
        }
    }
    for(; i1<size1; i1++, i_new++){
        new_array[i_new]=array1[i1];
    }
    for(; i2<size2; i2++, i_new++){
        new_array[i_new]=array2[i2];
    }
    return new_array;
}

Map_tree<int,int>* UnionFindPixel::build_complete_tree(TreeNode<int,int>** array, int size){
    int height = 0;
    if(size>0) {
        height = log2(size);//need to check complexity of log2??
    }
    Map_tree<int,int>* empty_tree= new Map_tree<int,int>();
    TreeNode<int,int>* new_node= new TreeNode<int,int>(0,0);
    empty_tree->set_root(new_node);
    build_recurse(empty_tree->get_root(),height);

    int num_to_delete = exp2(height+1)-size-1;
    delete_right_leaves(empty_tree,num_to_delete,height);
    empty_tree->set_size(size);
    return empty_tree;

}

void UnionFindPixel::build_recurse(TreeNode<int,int>* current, int height){
    if(height<=0 )                       //maybe should check if current == nullptr?
        return;

    TreeNode<int,int>* new_node1= new TreeNode<int,int>(0,0);
    current->set_left_son(new_node1);
    build_recurse(current->get_left_son(),height-1);
    TreeNode<int,int>* new_node2= new TreeNode<int,int>(0,0);
    current->set_right_son(new_node2);
    build_recurse(current->get_right_son(),height-1);
}

void UnionFindPixel::delete_right_leaves(Map_tree<int,int>* tree, int num_to_delete, int height){
    TreeNode<int,int>* current=tree->get_root();
    delete_right_leaves_recurse(tree->get_root(),&num_to_delete,height);

}

void UnionFindPixel::delete_right_leaves_recurse(TreeNode<int,int>* current, int* num_to_delete, int height){
    if(height==0 || *num_to_delete<=0){
        return;
    }

    delete_right_leaves_recurse(current->get_right_son(),num_to_delete,height-1);       //does num_to_delete need * before the name?
    if((*num_to_delete)>0 && height==1){
        delete current->get_right_son();
        current->set_right_son(nullptr);
        (*num_to_delete)--;
    }

    delete_right_leaves_recurse(current->get_left_son(),num_to_delete,height-1);
    if((*num_to_delete)>0 && height==1){
        delete current->get_left_son();
        current->set_left_son(nullptr);
        (*num_to_delete)--;
    }

}

void UnionFindPixel::insert_array_to_tree(Map_tree<int,int>* tree,TreeNode<int,int>** array){
    int index=0;
    int height=0;
    if(tree->get_size()>0){
        height = log2(tree->get_size());
    }
    insert_array_to_tree_recurse(tree->get_root(),array,&index,height);
    update_max_score_recurse(tree->get_root());
}

void UnionFindPixel::insert_array_to_tree_recurse(TreeNode<int,int>* current,TreeNode<int,int>** array, int* index, int height){
    if(height<0 || current== nullptr){
        return;
    }
    insert_array_to_tree_recurse(current->get_left_son(),array,index,height-1);
    current->set_key(array[*index]->get_key());
    current->set_data(array[*index]->get_data());
    (*index)++;

    insert_array_to_tree_recurse(current->get_right_son(),array,index,height-1);

    current->set_height();                  //verify correct place to update height...
}



void UnionFindPixel::update_max_score_recurse(TreeNode<int,int>* current){
    if(current== nullptr){
        return;
    }
    if(current->get_height()==0){
        current->set_max_score(current->get_data());
        return;
    }
    update_max_score_recurse(current->get_left_son());
    update_max_score_recurse(current->get_right_son());

    current->update_max_score();

}

bool UnionFindPixel::set_score_to_label(int pixel, int label, int score){
    int super_pixel=this->find(pixel);
    auto label_ptr = this->labels[super_pixel]->find(label);

    if(label_ptr == nullptr) {
        this->labels[super_pixel]->add_node(label, score);
        return false;
    }

    label_ptr->set_data(score);
    return true;
}

bool UnionFindPixel::delete_label(int pixel, int label){
    int super_pixel=this->find(pixel);
    auto label_ptr = this->labels[super_pixel]->find(label);

    if(label_ptr == nullptr)
        return false;

    this->labels[super_pixel]->remove_node(label_ptr);
    return true;

}

ostream& UnionFindPixel::printUnionFind(ostream& os) {
    os << "Index:  | ";
    for (int i = 0; i < this->num_of_pixels; i++)
        os << (i) << " | ";
    os << endl;

    os << "Size:   | ";
    for (int i = 0; i < this->num_of_pixels; i++)
        os << this->size[i] << " | ";
    os << endl;

    os << "Parent: | ";
    for (int i = 0; i < this->num_of_pixels; i++){
        if (this->parent[i] == ROOT)
            os << "- | ";
        else {
            os << this->parent[i] << " | ";
        }
    }
    os << endl;

    os << "Labels: " << endl;
    for (int i = 0; i < this->num_of_pixels; i++)
        this->labels[i]->printTree(os);
    os << endl;
}

















