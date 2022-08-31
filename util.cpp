//
// Created by Giuliano Galloppi on 23/08/22.
//
#include <iostream>
#include <vector>
#include <chrono>
#include <barrier>
#include <random>
#include "util.hpp"

using namespace std;

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

float randomBetween( int lowerBound, int upperBound ) //FORTISSIMA
{
    random_device rd;
    default_random_engine eng(rd());
    //uniform_real_distribution<float> dist(lowerBound, upperBound);
    uniform_int_distribution<int> dist(lowerBound, upperBound);
    float r = dist(eng);
    /*int upperbound, lowerbound;
    //float randomBetween = rand() % (upperbound-lowerbound) + upperbound;
    return randomBetween;*/
    return r;
}

vector<vector<float>> generateRandomSquareVectorMatrix(int size, int lowerBound, int upperBound){
    int rows = size;
    int col = size;
    vector<vector<float>> m(rows,vector<float>(col));

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            m[i][j] = randomBetween(lowerBound,upperBound);
        }
    }
    return m;
}

float** generateRandomSquareMatrix(int size, int lowerBound, int upperBound){
    float** m;
    m = new float*[size];

    for(int i=0;i<size;i++){
        m[i] = new float[size];
        for(int j=0;j<size;j++){
            m[i][j] = randomBetween(lowerBound,upperBound);
        }
    }
    return m;
}











vector<float> generateRandomVector(int size,int lowerBound, int upperBound){
    vector<float> v(size);

    for(int j=0;j<size;j++){
        v[j] = randomBetween(1,20);
    }
    return v;
}
