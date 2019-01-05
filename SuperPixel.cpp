//
// Created by nadav on 1/2/2019.
//

#include "SuperPixel.h"
SuperPixel::SuperPixel() : max_lable_score(NO_SCORE){
    this->tree=new Map_tree<int,int>;
}
