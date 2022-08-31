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
#include "util.hpp"

using namespace std;


int main(int argc, char* argv[]) {

    printStr("===== Inizio Jacobi FASTFLOW =====\n");

    ///dichiarazione variabili
    const int N_LENGHT = 2; //lunghezza della matrice e dei vettori
    const int K_MAX_ITER = 2;
    cout<<"\n\n\n===ITERAZIONI = "<<K_MAX_ITER<<endl;
    vector<vector<float>> matriceA = getDefaultMatrixN3();
    vector<float> vettoreB = getDefaultVectorBN3();
    //i vettori x sono inizializzati entrambi a 0
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k
    vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1


    float somma=0;
    float temp1 = 0;
    float temp2 = 0;

    auto inizio = chrono::high_resolution_clock::now();
    auto fine = chrono::high_resolution_clock::now();

    int val;

    //k e' il numero delle iterazioni
    inizio = chrono::high_resolution_clock::now();
    for(int k=0;k<K_MAX_ITER;k++){

        for(int i=0; i<N_LENGHT; i++) { //for esterno DELLA FORMULA
            somma = 0;
            temp1 = (1 / matriceA[i][i]);

            for(int j=0;j<N_LENGHT;j++){
                if (j != i ){
                    somma = somma + ( matriceA[i][j] * currentIt_vec_X[j] ) ;
                }
            }//fine for delle j

            temp2 = vettoreB[i] - somma;
            nextIt_vec_X[i] = temp1 * temp2;
        } // FINE CICLO i

        currentIt_vec_X= nextIt_vec_X;
    }//fine for delle iterazioni


    fine = chrono::high_resolution_clock::now();
    printArray("\nvettore x\n",nextIt_vec_X,N_LENGHT);
    printMicroSec(inizio,fine);
    cout<<"Fine programma"<<endl;
    return 0;
}