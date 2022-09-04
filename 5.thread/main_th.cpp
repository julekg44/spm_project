/*Giuliano Galloppi 646443 - Progetto di SPM A.A. 2021/22 - Jacobi iterative method implementation*/
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <barrier>
#include "util.hpp"
#include "utimer.cpp"

#define LOWER_BOUND 0 //1
#define UPPER_BOUND 20 //4
#define SEED 3

using namespace std;

//compile: g++ -std=c++20 -O3 -o main_th.out main_th.cpp util.hpp util.cpp utimer.cpp -pthread
//exec: ./main_th.out [K_ITERATION] [N_LENGHT] [N_THREAD]
int main(int argc, char* argv[]) {

    if (argc > 4 || argc < 4) { //Check arguments by command line
        cout << "Usage: " << argv[0]<< " \"K_MAX_ITER\" \"N_LENGHT_MATRIX_AND_VECTOR\" \"N_THREAD\" " << endl;
        exit(1);
    }
    std::cout<<"GIULIANO GALLOPPI 646443 - SPM Project A.Y.2021/22 - THREAD Jacobi iterative method implementation"<<endl;

    const int K_MAX_ITER = stoi(argv[1]);
    const int N_LENGHT = stoi(argv[2]);
    const int n_thread = stoi(argv[3]);

    vector<vector<float>> matriceA;
    vector<float> vettoreB;
    startCase(matriceA,vettoreB,N_LENGHT,LOWER_BOUND,UPPER_BOUND,SEED);
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k
    vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1

    int pieceWorkOnPerThread = N_LENGHT / n_thread;
    vector<thread> arrayThread(n_thread);

    std::cout<<"\nVERSIONE THREAD: Num_ITER = "<<K_MAX_ITER<<", N_LEN = "<<N_LENGHT<<", N_THREAD = "<<n_thread<<endl;
    auto inizio = chrono::high_resolution_clock::now(); //MIO - funziona solo prima di utimer
    auto fine = chrono::high_resolution_clock::now();//MIO

    auto on_completion = [&]() noexcept {
        //static auto phase = "Iterazione finita thread hanno raggiunto la barriera e si cambia iterazione\n";
        currentIt_vec_X = nextIt_vec_X; //
    };

    std::barrier barrieraThread(n_thread, on_completion); //barriera per sincronizzare i thread

    auto lambdaJacobiThread = [&](int threadPartito) {
        int startOnWork = threadPartito * pieceWorkOnPerThread; //Starting position
        int endOnWork = startOnWork + pieceWorkOnPerThread;//Ending position

        if (threadPartito == n_thread - 1) { //The last thread takes all the remain elements
            endOnWork = N_LENGHT;
        }

        float somma, temp1, temp2;
        for (int k = 0; k < K_MAX_ITER; k++) {
            int i = startOnWork;
            while (i < endOnWork) {
                somma = 0;
                temp1 = (1 / matriceA[i][i]);
                for (int j = 0; j < N_LENGHT; j++) {
                    if (j != i) {
                        somma = somma + (matriceA[i][j] * currentIt_vec_X[j]);
                    }
                }
                temp2 = vettoreB[i] - somma;
                nextIt_vec_X[i] = temp1 * temp2;
                i++;
            }
            auto inizio = chrono::high_resolution_clock::now(); //MIO - funziona solo prima di utimer
            barrieraThread.arrive_and_wait(); //Thread are synchronized before the next iteration
            auto fine = chrono::high_resolution_clock::now();//MIO
        }
    };

    long tempo_catturato;
    utimer tempo_seq = utimer("Tempo Esecuzione VERSIONE THREAD Jacobi", &tempo_catturato);
    for(int i=0;i<n_thread;i++){
        arrayThread[i]=thread(lambdaJacobiThread,i);
        printMicroSec(inizio,fine);

    }

    for(int i=0;i<n_thread;i++){
        arrayThread[i].join();
    }


    cout<<"OVERHEAD DELLA BARRIERA: ";

    //printArray(nextIt_vec_X,N_LENGHT);
    cout<<"Fine programma"<<endl;
    return 0;
}