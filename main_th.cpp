#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include "util.hpp"

using namespace std;

const int N_LENGHT = 2; //lunghezza della matrice e dei vettori
vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1 E' condiviso tra i thread

void eseguiRigaThread(float matriceA[][N_LENGHT],int n_lenght, vector<float> currentIt_vec_X, float vettoreB[N_LENGHT],int row);
//void eseguiRigaThread(vector<vector<float>>() matriceA,int n_lenght, vector<float> currentIt_vec_X, int vettoreB[]);
void eseguiJacobiSenzaK(float matriceA[][N_LENGHT],int n_lenght, vector<float> currentIt_vec_X, float vettoreB[N_LENGHT]);



//funzioni quando devi modificare una variabile metti nel prot & e main nulla

int main() {
    std::thread::id main_tid = std::this_thread::get_id();
    cout<<"TID DEL MAIN="<<main_tid<<endl;
    //In seq il MAIN THREAD, PER OGNI ITERAZIONE elabora una riga per volta
    //Coi thread quindi lancio tanti thread quante sono le righe della matrice,
    //ovvero n, così ogni riga darà il risultato di 'Xi' che appartiene al vettore della prossima iterazione
    //il quale questo sarà aggiornato solo prima del cambio dell'iterazione,
    // sincronizzato con una barrier

    cout<<"jacobi VERSIONE THREAD"<<endl;
    const int K_MAX_ITER = 1;

    //vector<vector<float>> matriceA(N_LENGHT,vector<float>(N_LENGHT));
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
    

    vector<thread> arrayThread(N_LENGHT); //array dei thread tanti quante le righe della mat ovvero n
    int val;
    auto inizio = chrono::high_resolution_clock::now();
    auto fine = chrono::high_resolution_clock::now();




    //PER ESEGUIRE THREAD QUI threads[i] = thread(body, i);
    inizio = chrono::high_resolution_clock::now();
    for(int k=0;k<K_MAX_ITER;k++){ //Qui l'iterazione comunque resta come for

        //ora qui lancio n thread dove ognuno si occupa di una riga della matrice
        //ovvero prenderà in ingresso tutta la riga della matrice, il vettore current, n che è la lunghezza della matrice
        //ed in uscita nulla perchè scriverà nel vettore next_x che sarà condiviso tra i thread
        
        //FIRMA: void eseguiRigaThread(float matriceA[][N_LENGHT],int n_lenght, vector<float> currentIt_vec_X, float vettoreB[N_LENGHT]);
        //SEQUENZIALE: eseguiRigaThread(matriceA, N_LENGHT, currentIt_vec_X, vettoreB);
        /*CON UN THREAD:
         * thread t {eseguiRigaThread,matriceA,N_LENGHT,currentIt_vec_X,vettoreB};
         * t.join();*/

        for(int riga=0;riga<N_LENGHT;riga++){
            arrayThread[riga] = thread(eseguiRigaThread,matriceA,N_LENGHT,currentIt_vec_X,vettoreB,riga);
        }

        /*devono finire tutti prima della prossima iterazione*/
        for(int riga=0;riga<N_LENGHT;riga++){
            arrayThread[riga].join();
        }


        //arrayThread[0] = thread(eseguiRigaThread,matriceA,N_LENGHT,currentIt_vec_X,vettoreB);
        //arrayThread[0].join();








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

    fine = chrono::high_resolution_clock::now();

    //per far terminare tutti i thread prima del main





    printArray("\nvettore x\n",nextIt_vec_X,N_LENGHT);

    cout<<"Tempo esecuzione: ";
    /*
        inizio = chrono::high_resolution_clock::now();
        eseguiRigaThread(matriceA, N_LENGHT, currentIt_vec_X, vettoreB);
        fine = chrono::high_resolution_clock::now();
    */
    printMicroSec(inizio,fine);
    cout<<"Fine programma"<<endl;
    return 0;
}

//(eseguiSuRigaFunctio,MatriceA,currentVettoreX,nextVettoreX,n,VETTORE_B);











void eseguiRigaThread(float matriceA[][N_LENGHT],int n_lenght, vector<float> currentIt_vec_X, float vettoreB[N_LENGHT], int row){
    //OGNI THREAD LAVORA SU UNA SOLA RIGA, AD OGNI ITERAZIONE POI LAVORA SEMPRE SU QUELLA RIGA MA CAMBIA L'ITERAZIONE
        std::cout<<endl<<"il thread ha avviato la funzione"<<endl;
        std::thread::id this_id = std::this_thread::get_id();
        cout<<"Thread ID = "<<this_id<<endl;
        float somma;
        float temp1, temp2;
            //for esterno DELLA FORMULA
            somma = 0;
            temp1 = (1 / matriceA[row][row]);

            for(int j=0;j<n_lenght;j++){
                if (j != row ){
                    somma = somma + ( matriceA[row][j] * currentIt_vec_X[j] ) ;
                }
            }

            temp2 = vettoreB[row] - somma;
            nextIt_vec_X[row] = temp1*temp2;
            // FINE CICLO i*/
}



void eseguiJacobiSenzaK(float matriceA[][N_LENGHT],int n_lenght, vector<float> currentIt_vec_X, float vettoreB[N_LENGHT]){
    //OGNI THREAD LAVORA SU UNA SOLA RIGA, AD OGNI ITERAZIONE POI LAVORA SEMPRE SU QUELLA RIGA MA CAMBIA L'ITERAZIONE
    std::cout<<endl<<"il thread ha avviato la funzione"<<endl;
    std::thread::id this_id = std::this_thread::get_id();
    cout<<"Thread ID = "<<this_id<<endl;
    float somma;
    float temp1, temp2;
    for(int row=0;row<n_lenght;row++) {//for esterno DELLA FORMULA
        somma = 0;
        temp1 = (1 / matriceA[row][row]);

        for (int j = 0; j < n_lenght; j++) {
            if (j != row) {
                somma = somma + (matriceA[row][j] * currentIt_vec_X[j]);
            }
        }

        temp2 = vettoreB[row] - somma;
        nextIt_vec_X[row] = temp1 * temp2;
    }// FINE CICLO i*/
}


/*funzione lambda

auto body = [&](int tid) {
        float sum = 0;
        int start = tid * chunk;
        int end = (tid != num_threads - 1 ? start + chunk : n) - 1;
        while (iterations > 0) {
            for (int i = start; i <= end; i++) {
                sum = 0;
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        sum += matrix[i][j] * prev_variables[j];
                    }
                }
                curr_variables[i] = (knownTerm[i] - sum) / matrix[i][i];
            }
            ba.arrive_and_wait();
        }
    };

*/
