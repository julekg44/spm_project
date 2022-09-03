/*Giuliano Galloppi 646443 - Progetto di SPM A.A. 2021/22 - Jacobi iterative method implementation*/
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <barrier>

#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>

#include "util.hpp"
#include "utimer.cpp"

#define LOWER_BOUND 0 //1
#define UPPER_BOUND 20 //4
#define SEED 3

using namespace std;

//compile: g++ -std=c++17 -O3 -o main_ff.out main_ff.cpp util.hpp util.cpp utimer.cpp -pthread
//exec: ./main_ff.out [K_ITERATION] [N_LENGHT] [N_THREAD]
int main(int argc, char* argv[]) {

    if (argc > 3 || argc < 3) { //Check arguments by command line
        cout << "Usage: " << argv[0]<< " \"K_MAX_ITER\" \"N_LENGHT_MATRIX_AND_VECTOR\" \"N_THREAD\" " << endl;
        exit(1);
    }
    std::cout<<"GIULIANO GALLOPPI 646443 - SPM Project A.Y.2021/22 - FAST FLOW Jacobi iterative method implementation"<<endl;

    const int K_MAX_ITER = stoi(argv[1]);
    const int N_LENGHT = stoi(argv[2]); //lunghezza della matrice e dei vettori
    const int n_thread = stoi(argv[3]);

    std::cout<<"\nVERSIONE FAST FLOW: Num_ITER = "<<K_MAX_ITER<<", N_LEN = "<<N_LENGHT<<", N_THREAD = "<<n_thread<<endl;

    vector<vector<float>> matriceA;
    vector<float> vettoreB;
    startCase(matriceA,vettoreB,N_LENGHT,LOWER_BOUND,UPPER_BOUND,SEED);
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k
    vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1

    int pezzoVettorePerThread = N_LENGHT / n_thread;
    ff::ParallelFor par_for_obj(n_thread); //utilizza tot thread/worker , come la versione thread ma con ff

    std::cout<<"\nVERSIONE FAST_FLOW: Num_ITER = "<<K_MAX_ITER<<", N_LEN = "<<N_LENGHT<<", WORKER_THREAD = "<<n_thread<<endl;

    long tempo_catturato;
    utimer tempo_seq = utimer("Tempo Esecuzione VERSIONE FAST_FLOW Jacobi", &tempo_catturato);
    for(int k=0;k<K_MAX_ITER;k++){

        par_for_obj.parallel_for(0, N_LENGHT, 1, pezzoVettorePerThread, [&](ulong i){
            float somma = 0;
            float temp1 = (1 / matriceA[i][i]);

            for(int j=0;j<N_LENGHT;j++){
                if (j != i ){                        
                    somma = somma + ( matriceA[i][j] * currentIt_vec_X[j] ) ;
                    }
            }

            float temp2 = vettoreB[i] - somma;
            nextIt_vec_X[i] = temp1 * temp2;
        },n_thread);

        currentIt_vec_X= nextIt_vec_X;
    }

    printArray(nextIt_vec_X,N_LENGHT);
    cout<<"Fine programma"<<endl;
    return 0;
}