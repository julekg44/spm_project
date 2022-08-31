//
// Created by Giuliano Galloppi on 23/08/22.
//
#include <iostream>
#include <vector>
#include <chrono>
#include <barrier>
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

void printMilliSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine){
    auto int_millisec = std::chrono::duration_cast<std::chrono::milliseconds>(fine-inizio).count();
    std::cout<<"Secondi: "<<int_millisec<<std::endl;
}

void printMicroSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine){
    auto microsec = std::chrono::duration_cast<std::chrono::microseconds>(fine-inizio).count();
    std::cout<<"Tempo in Microsecondi: "<<microsec<<std::endl;
}
