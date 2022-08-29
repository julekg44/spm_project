//
// Created by Giuliano Galloppi on 23/08/22.
//
#ifndef PROGETTO_UTIL_HPP
#define PROGETTO_UTIL_HPP

#include <string>
#include <vector>
#include <chrono>

void printTest();
void printStr(std::string str);
void printArray(std::string msg, std::vector<float> array, int array_size);
void printMilliSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine);
void printMicroSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine);



#endif //PROGETTO_UTIL_HPP
