#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include "util.hpp"

using namespace std;

void eseguiRigaThread();

int main() {

    //In seq il MAIN THREAD, PER OGNI ITERAZIONE elabora una riga per volta
    //Coi thread quindi lancio tanti thread quante sono le righe della matrice,
    //ovvero n, così ogni riga darà il risultato di 'Xi' che appartiene al vettore della prossima iterazione
    //il quale questo sarà aggiornato solo prima del cambio dell'iterazione,
    // sincronizzato con una barrier

    cout<<"jacobi VERSIONE THREAD"<<endl;
    const int K_MAX_ITER = 1;
    const int N_LENGHT = 2; //lunghezza della matrice e dei vettori

    float matriceA [N_LENGHT][N_LENGHT];
    matriceA[0][0]= 4;
    matriceA[0][1] = 2;
    matriceA[1][0]= 1;
    matriceA[1][1] = 3;

    float vettoreB[N_LENGHT] = {8,8};

    float somma=0;
    float temp1 = 0;
    float temp2 = 0;
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k
    vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1 E' condiviso tra i thread

    vector<thread> arrayThread(N_LENGHT); //array dei thread tanti quante le righe della mat ovvero n
    int val;

    //PER ESEGUIRE THREAD QUI threads[i] = thread(body, i);

    for(int k=0;k<K_MAX_ITER;k++){ //Qui l'iterazione comunque resta come for

        //ora qui lancio n thread dove ognuno si occupa di una riga della matrice
        //ovvero prenderà in ingresso tutta la riga della matrice, il vettore current, n che è la lunghezza della matrice
        //ed in uscita nulla perchè scriverà nel vettore next_x che sarà condiviso tra i thread


        //DA PARALLELIZZARE
        /*for(int i=0; i<N_LENGHT; i++) { //for esterno DELLA FORMULA

            somma = 0;
            temp1 = (1 / matriceA[i][i]);

            for(int j=0;j<N_LENGHT;j++){
                if (j != i ){
                    somma = somma + ( matriceA[i][j] * currentIt_vec_X[j] ) ;
                }
            }

            temp2 = vettoreB[i] - somma;
            nextIt_vec_X[i] = temp1*temp2;
        } // FINE CICLO i*/



        currentIt_vec_X= nextIt_vec_X;
    }//fine for delle iterazioni

    printArray("\nvettore x\n",nextIt_vec_X,N_LENGHT);

    cout<<"Fine programma"<<endl;
    return 0;
}

void eseguiRigaThread(){

}