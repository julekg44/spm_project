//
// Created by Giuliano Galloppi on 04/09/22.
//
#include <thread>
#include <vector>
#include <barrier>
#include <iostream>
#include <fstream>
#include "utimer.cpp"
using namespace std;

#define EXECUTION 5

int main(){

    int a = 0;
    
    auto on_completion = [&](){
        a++;
    };

    long tempoOverhead;

    for(int n_thread = 2; n_thread <= 32; n_thread +=2){
        long mediaTempo = 0;
        for(int e = 0; e < EXECUTION; e++) {

            vector<thread> threads(n_thread);
            std::barrier barrieraThread(n_thread, on_completion);

            auto lambdaVuota = [&](int threadPartito) {
                threadPartito++;
                barrieraThread.arrive_and_wait();
            };


                utimer thr = utimer("OVERHEAD " + to_string(n_thread) + " threads", &tempoOverhead);
                for (int i = 0; i < n_thread; i++) {
                    threads[i] = thread(lambdaVuota, i);
                }
                for (int i = 0; i < n_thread; i++) {
                    threads[i].join();
                }

            mediaTempo += tempoOverhead;
        }
        mediaTempo = mediaTempo / EXECUTION;
        cout << "mediaTempo " << mediaTempo << " with " << n_thread << " threads" << endl;

    }
    
    return 0;
}