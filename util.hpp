/*Giuliano Galloppi 646443 - Progetto di SPM A.A. 2021/22 - UTILITY*/
#ifndef PROGETTO_UTIL_HPP
#define PROGETTO_UTIL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <barrier>

using namespace std;

//SUPPORT
void printMilliSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine);
void printMicroSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine);
void printTID_thread();

//FUNZIONI PRINT
void printMatrix(vector<vector<float>> matrix);
void printArray(std::vector<float> array, int array_size);
void printArray(std::vector<double> array, int array_size);
void printVector(vector<float> vector);
void printVector(vector<double> vector);


//FUNZIONI RANDOM
float randomBetween(int lowerBound, int upperBound);

vector<vector<float>> generateRandomSquareVectorMatrix(int size, int lowerBound, int upperBound);
vector<vector<float>> generateMatrixSeed(int n, float min_matrix, float max_matrix, int seed);

vector<float> generateRandomVector(int size,int lowerBound, int upperBound);
vector<float> generateVectorSeed(int n, float min_vector, float max_vector, int seed);


//FUNZIONI DEFAULT
vector<vector<float>> getDefaultMatrixN2();
vector<float> getDefaultVectorBN2();
vector<vector<float>> getDefaultMatrixN3();
vector<float> getDefaultVectorBN3();

void startCase(vector<vector<float>>& matriceA, vector<float>& vettoreB,int size, int lb, int up, int seed);

bool isConvergente(vector<vector<float>> matrix);

//--------------
vector<vector<float>> GenerateRandomMatrix(int n, int seed);
vector<float> GenerateRandomVector(int size,int min, int max, int seed);




#endif //PROGETTO_UTIL_HPP
