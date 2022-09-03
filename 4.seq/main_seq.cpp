/*Giuliano Galloppi 646443 - Progetto di SPM A.A. 2021/22 - Jacobi iterative method implementation*/
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "util.hpp"
#include "utimer.cpp"

#define LOWER_BOUND 0 //1
#define UPPER_BOUND 20 //4
#define SEED 3

using namespace std;

//compile: g++ -std=c++17 -O3 -o main_seq.out main_seq.cpp util.hpp util.cpp utimer.cpp
//exec: ./main_seq.out [K_ITERATION] [N_LENGHT]
int main(int argc, char* argv[]) {

    if (argc > 3 || argc < 3) { //Check arguments by command line
        cout << "Usage: " << argv[0]<< " \"K_MAX_ITER\" \"N_LENGHT_MATRIX_AND_VECTOR\" " << endl;
        exit(1);
    }
    std::cout<<"GIULIANO GALLOPPI 646443 - SPM Project A.Y.2021/22 - SEQUENTIAL Jacobi iterative method implementation"<<endl;

    const int K_MAX_ITER = stoi(argv[1]);
    const int N_LENGHT = stoi(argv[2]); //lunghezza della matrice e dei vettori

    cout<<"\nSequenziale: Num_ITER = "<<K_MAX_ITER<<" N_LEN = "<<N_LENGHT<<endl;

    vector<vector<float>> matriceA;
    vector<float> vettoreB;
    startCase(matriceA,vettoreB,N_LENGHT,LOWER_BOUND,UPPER_BOUND,SEED);
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k
    vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1

    float somma=0;
    float temp1 = 0;
    float temp2 = 0;
    long tempo_catturato;

    utimer tempo_seq = utimer("Tempo Esecuzione Sequenziale Jacobi",&tempo_catturato); //STAMPA IL TEMPO TOTALE ALLA FINE
    for (int k = 0; k < K_MAX_ITER; k++) {

        for (int i = 0; i < N_LENGHT; i++) { //for 'i' external
            somma = 0;
            temp1 = (1 / matriceA[i][i]);

            for (int j = 0; j < N_LENGHT; j++) {
                if (j != i) {
                    somma = somma + (matriceA[i][j] * currentIt_vec_X[j]);
                }
            }

            temp2 = vettoreB[i] - somma;
            nextIt_vec_X[i] = temp1 * temp2;
        }
        currentIt_vec_X = nextIt_vec_X; //Update next iteration vector
    }

    cout<<"Stampo array finale:\n";
    printArray(nextIt_vec_X,N_LENGHT);
    cout<<"Fine programma"<<endl;
    return 0;
}