//
// Created by Giuliano Galloppi on 31/08/22.
//
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

using namespace std;

//compila con g++ -std=c++17 -O3 -o main_ff.out main_ff.cpp util.hpp util.cpp utimer.cpp
// ed aggiungi  --  /usr/local/fastflow/ff

//fast flow comunque usa i 'thread' per parallelizzare
int main(int argc, char* argv[]) {
    
    ///dichiarazione variabili
    const int N_LENGHT = 3; //lunghezza della matrice e dei vettori
    const int K_MAX_ITER = 2;

    vector<vector<float>> matriceA = getDefaultMatrixN3();
    vector<float> vettoreB = getDefaultVectorBN3();
    vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k - //i vettori x sono inizializzati entrambi a 0

    int n_thread = 2; //thread-worker
    int pezzoVettorePerThread = N_LENGHT / n_thread;
    ff::ParallelFor par_for_obj(n_thread); //utilizza tot thread/worker , come la versione thread ma con ff

    std::cout<<"\nVERSIONE FAST_FLOW: Num_ITER = "<<K_MAX_ITER<<", N_LEN = "<<N_LENGHT<<", WORKER_THREAD = "<<n_thread<<endl;


    
    long tempo_catturato;
    utimer tempo_seq = utimer("Tempo Esecuzione VERSIONE FAST_FLOW Jacobi", &tempo_catturato); //STAMPA IL TEMPO TOTALE ALLA FINE
    for(int k=0;k<K_MAX_ITER;k++){

        //for(int i=0; i<N_LENGHT; i++) { //for esterno DELLA FORMULA
        par_for_obj.parallel_for(0, N_LENGHT, 1, pezzoVettorePerThread, [&](ulong i){
            float somma = 0;
            float temp1 = (1 / matriceA[i][i]);

            for(int j=0;j<N_LENGHT;j++){
                if (j != i ){                        
                    somma = somma + ( matriceA[i][j] * currentIt_vec_X[j] ) ;
                    }
            }//fine for delle j

            float temp2 = vettoreB[i] - somma;
            nextIt_vec_X[i] = temp1 * temp2;
        },n_thread); //FINE CICLO i

        currentIt_vec_X= nextIt_vec_X;
    }//fine for delle iterazioni

    printArray(nextIt_vec_X,N_LENGHT);
    cout<<"Fine programma"<<endl;
    return 0;
}

/*5 ARG: pf.parallel_for(0, n, 1, chunk, [&](ulong i){ GLI PASSA COME LAMBDA FUNCTION CHE PRENDE IN INGRESSO LA VARIABILE ESTERNA 'i' come long
template<typename Function >
void ff::ParallelFor::parallel_for	(	long 	first,
                                        long 	last,
                                        long 	step,
                                        long 	grain,
                                        const Function & 	f,
                                        const long 	nw = FF_AUTO 
)	        

Parallel for region (step, grain) - dynamic.
Dynamic scheduling onto nw worker threads. Iterations are scheduled in blocks of minimal size grain. Iteration space is walked with stride step.

Parameters
first	first value of the iteration variable
last	last value of the iteration variable
step	step increment for the iteration variable
grain	(> 0) minimum computation grain (n. of iterations scheduled together to a single worker)
f	    f(const long idx) Lambda function, body of the parallel loop. idx: iteration param nw number of worker threads

*/