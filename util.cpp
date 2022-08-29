//
// Created by Giuliano Galloppi on 23/08/22.
//
#include <iostream>
#include <vector>
#include "util.hpp"


void printTest(){
    std::cout<<("Stampa Test")<<std::endl;
}

void printStr(std::string str){
    std::cout<<(str);
}

void printArray(std::string msg, std::vector<float> array, int array_size){
    std::cout<<msg;
    for(int h=0;h<array_size;h++){
        printf ("x[%d]: %.3f \n",h, array[h]);
    }

}