//
// Created by Giuliano Galloppi on 29/08/22.
//
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>

using namespace std;
void hello();

int main(){

    //ogni thread ha bisogno di una funzione iniziale/in ingresso
    thread t(hello);

    return 0;
}

void hello()
{
    std::cout<<"Hello Concurrent World\n";
}