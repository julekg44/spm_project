#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <barrier>
#include "util.hpp"

using namespace std;

//Default values with N_LENGHT = 3 :  x=4; y=-5; z=9;
//Default values with N_LENGHT = 2 :  x=1; y=2;
const int N_LENGHT = 2; //lunghezza della matrice e dei

///var globali
float matriceA [N_LENGHT][N_LENGHT];
float vettoreB[N_LENGHT];
//currentIt_vec_X
vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1 E' condiviso tra i thread

void defaultMatrix2N();
void defaultMatrix3N();
void defaultVettoreB_2N();
void defaultVettoreB_3N();
void printTID_thread();
void on_completion();
void work (std::string name);

        //funzioni quando devi modificare una variabile metti nel prot & e main nulla
int main() {
    /*Nel seq il MAIN THREAD, PER OGNI ITERAZIONE elabora una riga per volta
            //Coi thread quindi lancio tanti thread A MIA SCELTA che si suddividono il vettore
            //ognuno collabora a finalizzare il risultato di 'Xi' che appartiene al vettore della prossima iterazione
            //il quale questo sarà aggiornato solo prima del cambio dell'iterazione,
            //sincronizzato con una barrier[vedi nelle note]*/

    ///dichiarazione variabili
    cout<<"jacobi VERSIONE THREAD"<<endl;
    const int K_MAX_ITER = 3;
    int n_thread = 2; //thread


    matriceA[0][0]= 4;
    matriceA[0][1] = 2;
    matriceA[1][0]= 1;
    matriceA[1][1] = 3;

    vettoreB[0] = 8;
    vettoreB[1] = 8;


    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k con tutti 0 per la prima iterazione

    auto inizioTempo = chrono::high_resolution_clock::now();
    auto fineTempo = chrono::high_resolution_clock::now();

    int pezzoVettorePerThread = N_LENGHT / n_thread;

    vector<thread> arrayThread(N_LENGHT); //array dei thread tanti quante le righe della mat ovvero n

    //FINITA UN ITERAZIONE SUL VETTORE X DA PARTE DI TUTTI I THREAD SI AGGIORNA IL VETTORE DELLE X DELLA NEXT_ITERATION
    auto on_completion = [&]() noexcept {
        static auto phase = "Iterazione finita thread hanno raggiunto la barriera e si cambia iterazione\n";
        std::cout << phase;
    };

    std::barrier barrieraThread(n_thread, on_completion); //barriera per sincronizzare i thread

    auto lambdaJacobiThread = [&] (int threadPartito){
        int startOnWork = threadPartito * pezzoVettorePerThread;
        //int end = (tid != num_threads - 1 ? start + chunk : n) - 1;
        int endOnWork = (threadPartito != n_thread - 1 ? startOnWork + pezzoVettorePerThread : N_LENGHT) - 1;
        //int endOnWork = (startOnWork+pezzoVettorePerThread);
        cout<<"lavora dall'elemento "<<startOnWork<<"all'elemento"<<endOnWork<<endl;

        float somma,temp1, temp2;
        for(int k=0;k<K_MAX_ITER;k++) { //Qui l'iterazione comunque resta come for
            for (int i = startOnWork; i < endOnWork; i++) {//for esterno DELLA FORMULA
                somma = 0;
                temp1 = (1 / matriceA[i][i]);

                for (int j = 0; j < N_LENGHT; j++) {
                    if (j != i) {
                        somma = somma + (matriceA[i][j] * currentIt_vec_X[j]);
                    }
                }//fine ciclo j

                temp2 = vettoreB[i] - somma;
                cout<<"valore ="<<(temp1*temp2);
                nextIt_vec_X[i] = temp1 * temp2;
            }// FINE CICLO i*/

            //SINCRONIZZO I THREAD sul vettore e sulla prossima iterazione
            //il vettore e' scambiato nell'on completion
            barrieraThread.arrive_and_wait(); //qui producono tutti ed aspettano
            currentIt_vec_X= nextIt_vec_X; //
        }//fine for delle iterazioni
    };






    /*
    //la funzione on completion viene avviata ogni volta che i thread raggiungono tutti la barriera e quinid
    //si sincronizzano, la puoi usare come fa roberto per uscire dal ciclo o per fare altro in quel certo momento
    //di sincronizzazione
    //PER ESEGUIRE THREAD QUI threads[i] = thread(body, i);
    */

    //INIZIO LANCIO MAIN COI THREAD
    inizioTempo = chrono::high_resolution_clock::now();


    for(int i=0;i<n_thread;i++){
        cout<<"parte tid "<<i<<endl;
        arrayThread[i]=thread(lambdaJacobiThread,i);
    }

    /*devono finire tutti prima della prossima iterazione*/
    for(int idx=0;idx<n_thread;idx++){
        arrayThread[idx].join();
    }

    fineTempo = chrono::high_resolution_clock::now();


    printArray("\nvettore x\n",nextIt_vec_X,N_LENGHT);
    std::cout<<"Tempo esecuzione: ";
    printMicroSec(inizioTempo,fineTempo);
    cout<<"Fine programma"<<endl;
    return 0;
}




void printTID_thread(){
    std::cout<<endl<<"il thread ha avviato la funzione ";
    std::thread::id this_id = std::this_thread::get_id();
    cout<<"Thread ID = "<<this_id<<endl;
}


void defaultMatrix2N(){
    matriceA[0][0]= 4;
    matriceA[0][1] = 2;
    matriceA[1][0]= 1;
    matriceA[1][1] = 3;
}

void defaultMatrix3N(){
    matriceA[0][0]= 7;
    matriceA[0][1] = 8;
    matriceA[0][2] = 1;

    matriceA[1][0]= 8;
    matriceA[1][1] = 7;
    matriceA[1][2] = 1;

    matriceA[2][0]= 6;
    matriceA[2][1] = 6;
    matriceA[2][2] = 1;

}

void defaultVettoreB_2N(){
    vettoreB[0] = 8;
    vettoreB[1] = 8;
}

void defaultVettoreB_3N(){
    vettoreB[0] = -3;
    vettoreB[1] = 6;
    vettoreB[2] = 3;
    // x=4; y=-5; z=9
}



/*
//FIRMA: void eseguiRigaThread(float matriceA[][N_LENGHT],int n_lenght, vector<float> currentIt_vec_X, float vettoreB[N_LENGHT]);
//SEQUENZIALE: eseguiRigaThread(matriceA, N_LENGHT, currentIt_vec_X, vettoreB);
CON UN THREAD:
 * thread t {eseguiRigaThread,matriceA,N_LENGHT,currentIt_vec_X,vettoreB};
 * t.join();*/




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
