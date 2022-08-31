//
// Created by Giuliano Galloppi on 23/08/22.
//
#ifndef PROGETTO_UTIL_HPP
#define PROGETTO_UTIL_HPP

#include <string>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

void printTest();
void printStr(std::string str);
void printArray(std::string msg, std::vector<float> array, int array_size);
void printMilliSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine);
void printMicroSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine);
float randomBetween( int lowerBound, int upperBound );
vector<vector<float>> generateRandomSquareVectorMatrix(int size, int lowerBound, int upperBound);
float **generateRandomSquareMatrix(int size, int lowerBound, int upperBound);
vector<float> generateRandomVector(int size,int lowerBound, int upperBound);

vector<vector<float>> getDefaultMatrixN2();
vector<float> getDefaultVectorBN2();
vector<vector<float>> getDefaultMatrixN3();
vector<float> getDefaultVectorBN3();






#endif //PROGETTO_UTIL_HPP
