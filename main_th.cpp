#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <barrier>
#include "util.hpp"

using namespace std;

///var globali
const int N_LENGHT = 2; //lunghezza della matrice e dei
vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1 E' condiviso tra i thread
std::barrier barrieraThread(0);



void funzioneJacobiThread(int K_MAX_ITER, float matriceA[][N_LENGHT],int n_lenght, vector<float> currentIt_vec_X, float vettoreB[N_LENGHT],int threadPartito,int pezzoVettorePerThread);
void on_completion();
void work (std::string name);

        //funzioni quando devi modificare una variabile metti nel prot & e main nulla
int main() {
    std::thread::id main_tid = std::this_thread::get_id();
    cout<<"TID DEL MAIN="<<main_tid<<endl;
    /*Nel seq il MAIN THREAD, PER OGNI ITERAZIONE elabora una riga per volta
            //Coi thread quindi lancio tanti thread A MIA SCELTA che si suddividono il vettore
            //ognuno collabora a finalizzare il risultato di 'Xi' che appartiene al vettore della prossima iterazione
            //il quale questo sarà aggiornato solo prima del cambio dell'iterazione,
            //sincronizzato con una barrier[vedi nelle note]*/

    ///dichiarazione variabili
    cout<<"jacobi VERSIONE THREAD"<<endl;
    const int K_MAX_ITER = 1;

    //vector<vector<float>> matriceA(N_LENGHT,vector<float>(N_LENGHT));
    float matriceA [N_LENGHT][N_LENGHT];
    matriceA[0][0]= 4;
    matriceA[0][1] = 2;
    matriceA[1][0]= 1;
    matriceA[1][1] = 3;
    float vettoreB[N_LENGHT] = {8,8};
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k con tutti 0 per la prima iterazione

    ///dichiarazione altre var usati nel jacobi
    float somma=0;
    float temp1 = 0;
    float temp2 = 0;

    auto inizioTempo = chrono::high_resolution_clock::now();
    auto fineTempo = chrono::high_resolution_clock::now();
    int n_thread = 2; //thread
    int pezzoVettorePerThread = N_LENGHT / n_thread;

    vector<thread> arrayThread(N_LENGHT); //array dei thread tanti quante le righe della mat ovvero n

    barrieraThread(n_thread, on_completion); //barriera per sincronizzare i thread


    //la funzione on completion viene avviata ogni volta che i thread raggiungono tutti la barriera e quinid
    //si sincronizzano, la puoi usare come fa roberto per uscire dal ciclo o per fare altro in quel certo momento
    //di sincronizzazione
    
            //PER ESEGUIRE THREAD QUI threads[i] = thread(body, i);

    inizioTempo = chrono::high_resolution_clock::now();


        //for(int idx=0;idx<n_thread;idx++){ // devo creare gli n thread per iterazione
         //   arrayThread[idx] = thread(funzioneJacobiThread,matriceA,N_LENGHT,currentIt_vec_X,vettoreB,n_thread,pezzoVettorePerThread);
        //}
    for(int i=0;i<n_thread;i++){
        char buffer[50];
        arrayThread[i]=thread(work, (sprintf(buffer,"%d",i)));
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




void funzioneJacobiThread(int K_MAX_ITER, float matriceA[][N_LENGHT],int n_lenght, vector<float> currentIt_vec_X, float vettoreB[N_LENGHT],int threadPartito,int pezzoVettorePerThread){
    std::cout<<endl<<"il thread ha avviato la funzione ";
    std::thread::id this_id = std::this_thread::get_id();
    cout<<"Thread ID = "<<this_id<<endl;

    int startOnWork = threadPartito * pezzoVettorePerThread;
    int endOnWork = (startOnWork+pezzoVettorePerThread);
    cout<<"lavora dall'elemento "<<startOnWork<<"all'elemento"<<endOnWork<<endl;



    float somma;
    float temp1, temp2;

    for(int k=0;k<K_MAX_ITER;k++) { //Qui l'iterazione comunque resta come for
        for (int i = 0; i < n_lenght; i++) {//for esterno DELLA FORMULA
            somma = 0;
            temp1 = (1 / matriceA[i][i]);

            for (int j = 0; j < n_lenght; j++) {
                if (j != i) {
                    somma = somma + (matriceA[i][j] * currentIt_vec_X[j]);
                }
            }//fine ciclo j

            temp2 = vettoreB[i] - somma;
            nextIt_vec_X[i] = temp1 * temp2;
        }// FINE CICLO i*/

        //SINCRONIZZO I THREAD
        barrieraThread.arrive_and_wait(); //qui producono tutti ed aspettano
        currentIt_vec_X= nextIt_vec_X;
    }//fine for delle iterazioni


}


void on_completion() {
    // locking not needed here
    static auto phase = "... thread raggiunge barrier on completion\n";
    std::cout << phase;
};

void work (std::string name) {
    std::string product = "  " + name + " worked\n";
    std::cout << product;  // ok, op<< call is atomic
    barrieraThread.arrive_and_wait(); //qui producono tutti ed aspettano

};






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
