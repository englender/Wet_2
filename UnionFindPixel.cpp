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

UnionFindPixel::~UnionFindPixel(){
    delete[] size;
    delete[] parent;

    for (int i = 0; i < this->num_of_pixels; i++)
        delete labels[i];

    delete[] labels;
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

bool UnionFindPixel:: Union(int pixel1, int pixel2){
    int root1=find(pixel1);
    int root2=find(pixel2);

    if(root1 == root2)      //if trying to merge same super_pixel - return false
        return false;

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

    return true;
}



Map_tree<int,int>* UnionFindPixel::merge_trees(Map_tree<int,int>* tree1, Map_tree<int,int>* tree2){
    int array1_len=tree1->get_size();
    int array2_len=tree2->get_size();
    TreeNode<int,int>** array1=tree_to_array(tree1);
    TreeNode<int,int>** array2=tree_to_array(tree2);

    int full_array_size=0;
    TreeNode<int,int>** full_array=merge_arrays(array1,array1_len,array2,array2_len, &full_array_size);

//    TreeNode<int,int>* tmp_ptr;

    Map_tree<int,int>* new_tree=build_complete_tree(full_array_size);
    insert_array_to_tree(new_tree,full_array);

    for (int i = 0; i < array1_len; i++){
        delete array1[i];
    }

    for (int i = 0; i < array2_len; i++){
        delete array2[i];
    }

    delete[] array1;
    delete[] array2;
    delete[] full_array;

    return new_tree;
}

TreeNode<int,int>** UnionFindPixel::tree_to_array(Map_tree<int,int>* tree){
    if(tree->get_size()==0){
        return nullptr;
    }
    TreeNode<int,int>** array = new TreeNode<int,int>*[tree->get_size()];
    int index=0;
    tree_to_array_recurse(tree->get_root(),array,&index);
//    delete tree;
    return array;
}

void UnionFindPixel::tree_to_array_recurse(TreeNode<int,int>* current,
                                           TreeNode<int,int>** array_to_fill,
                                           int* index){
    if(current == nullptr)
        return;

    tree_to_array_recurse(current->get_left_son(),array_to_fill,index);
//    array_to_fill[*index]=current;
    array_to_fill[*index]=new TreeNode<int,int>(current->get_key(),current->get_data());
    (*index)++;
    tree_to_array_recurse(current->get_right_son(),array_to_fill,index);
}

TreeNode<int,int>** UnionFindPixel::merge_arrays(TreeNode<int,int>** array1,int size1,
                                          TreeNode<int,int>** array2, int size2, int* final_size){

    *final_size= size1+size2;
    if(*final_size==0)
        return nullptr;

    TreeNode<int,int>** new_array = new TreeNode<int,int>*[*final_size];
    int i1, i2, i_new;
    for(i1 = i2 = i_new = 0; (i1<size1) && (i2<size2); i_new++){
        if(array1[i1]->get_key()<array2[i2]->get_key()){
            new_array[i_new]=array1[i1];
            i1++;
        } else if(array1[i1]->get_key()>array2[i2]->get_key()){
            new_array[i_new]=array2[i2];
            i2++;
        } else {                            // fixing merging of two labels with the same key: new data = sum of two old datas
            new_array[i_new]=array1[i1];
            new_array[i_new]->set_data(array1[i1]->get_data()+array2[i2]->get_data());
            i1++;
            i2++;
            (*final_size)--;             //decreasing the size of the new array because of the duplication
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

Map_tree<int,int>* UnionFindPixel::build_complete_tree(int size){
    int height = 0;
    if(size>0) {
        height = log2(size);//need to check complexity of log2??
    }
    Map_tree<int,int>* empty_tree= new Map_tree<int,int>();

    if(size==0)
        return empty_tree;

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
    TreeNode<int,int>* new_node2= new TreeNode<int,int>(0,0);

    current->set_left_son(new_node1);
    current->set_right_son(new_node2);

    build_recurse(current->get_left_son(),height-1);
    build_recurse(current->get_right_son(),height-1);
}

void UnionFindPixel::delete_right_leaves(Map_tree<int,int>* tree, int num_to_delete, int height){
//    TreeNode<int,int>* current=tree->get_root();
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
    if(tree->get_size()<=0){
        return;
    }
    height = log2(tree->get_size());
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
    current->set_max_score(array[*index]->get_data());
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
        current->set_label_of_max_score(current->get_key());
        return;
    }
    update_max_score_recurse(current->get_left_son());
    update_max_score_recurse(current->get_right_son());

    current->update_max_score();

}

void UnionFindPixel::set_score_to_label(int pixel, int label, int score){
    int super_pixel=this->find(pixel);
    auto label_ptr = this->labels[super_pixel]->find(label);

    if(label_ptr == nullptr) {
        this->labels[super_pixel]->add_node(label, score);
        label_ptr =this->labels[super_pixel]->find(label);
        return;
    }

    label_ptr->set_data(score);
    label_ptr =this->labels[super_pixel]->find(label);

}

bool UnionFindPixel::delete_label(int pixel, int label){
    int super_pixel=this->find(pixel);
    auto label_ptr = this->labels[super_pixel]->find(label);

    if(label_ptr == nullptr)
        return false;

    TreeNode<int,int>* update_max_score_ptr= nullptr;
    this->labels[super_pixel]->remove_node(label_ptr, &update_max_score_ptr);

    if(update_max_score_ptr== nullptr)              // no need to update max score
        return true;

    this->labels[super_pixel]->find(update_max_score_ptr->get_key());
    return true;

}


bool UnionFindPixel::is_super_pixel_labeled(int pixel){
    int super_pixel=this->find(pixel);
    if(this->labels[super_pixel]->get_size()==0)
        return false;
    return true;
}

int UnionFindPixel::get_max_label_score(int pixel){
    return (this->labels[this->find(pixel)])->get_root()->get_label_of_max_score();
}

//ostream& UnionFindPixel::printUnionFind(ostream& os) {
//    os << "Index:  | ";
//    for (int i = 0; i < this->num_of_pixels; i++)
//        os << (i) << " | ";
//    os << endl;
//
//    os << "Size:   | ";
//    for (int i = 0; i < this->num_of_pixels; i++)
//        os << this->size[i] << " | ";
//    os << endl;
//
//    os << "Parent: | ";
//    for (int i = 0; i < this->num_of_pixels; i++){
//        if (this->parent[i] == ROOT)
//            os << "- | ";
//        else {
//            os << this->parent[i] << " | ";
//        }
//    }
//    os << endl;
//
//    os << "Labels: " << endl<< "------------------------------------------"<<endl;
//    for (int i = 0; i < this->num_of_pixels; i++) {
//        this->labels[i]->printTree(os);
//        if(this->labels[i]->get_root()!= nullptr)
//            os << "Max score of label tree: " << this->labels[i]->get_root()->get_max_score() << endl;
//        os << "------------------------------------------"<<endl;
//    }
//    os << "------------------------------------------"<<endl<<endl;
//}
//
//















