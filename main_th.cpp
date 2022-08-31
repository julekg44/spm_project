#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <barrier>
#include "util.hpp"

using namespace std;

//Ricorda che possono variare ITERAZIONI e THREAD
//qui compili da g++ -std=c++20 ...

//Default values with N_LENGHT = 3 :  x=4; y=-5; z=9;
//Default values with N_LENGHT = 2 :  x=1; y=2;
const int N_LENGHT = 3; //lunghezza della matrice e dei
vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1 E' condiviso tra i thread

void printTID_thread();
void on_completion();
void work (std::string name);

int main() {
    /*Nel seq il MAIN THREAD, PER OGNI ITERAZIONE elabora una riga per volta
    //Coi thread quindi lancio tanti thread A MIA SCELTA che si suddividono il vettore
    //ognuno collabora a finalizzare il risultato di 'Xi' che appartiene al vettore della prossima iterazione
    //il quale questo sarà aggiornato solo prima del cambio dell'iterazione,
    //sincronizzato con una barrier[vedi nelle note]*/

    ///dichiarazione variabili
    const int K_MAX_ITER = 2;
    cout<<"\n\n\n===ITERAZIONI = "<<K_MAX_ITER<<endl;
    vector<vector<float>> matriceA = getDefaultMatrixN3();
    vector<float> vettoreB = getDefaultVectorBN3();
    //i vettori x sono inizializzati entrambi a 0
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k con tutti 0 per la prima iterazione

    cout<<"jacobi VERSIONE THREAD"<<endl;

    int n_thread = 2; //thread
    int pezzoVettorePerThread = N_LENGHT / n_thread;
    //int pezzoWorkOnPerThread = N_LENGHT / n_thread;
    vector<thread> arrayThread(n_thread); //array dei thread tanti quante le righe della mat ovvero n


    auto inizioTempo = chrono::high_resolution_clock::now();
    auto fineTempo = chrono::high_resolution_clock::now();


    //----------------------------------------------------------------------------------------------------------------------
    //FINITA UN ITERAZIONE SUL VETTORE X DA PARTE DI TUTTI I THREAD SI AGGIORNA IL VETTORE DELLE X DELLA NEXT_ITERATION
    auto on_completion = [&]() noexcept {
        static auto phase = "Iterazione finita thread hanno raggiunto la barriera e si cambia iterazione\n";
        std::cout << phase;
        currentIt_vec_X= nextIt_vec_X; //
    };

    std::barrier barrieraThread(n_thread, on_completion); //barriera per sincronizzare i thread

    auto lambdaJacobiThread = [&] (int threadPartito){
        int startOnWork = threadPartito * pezzoVettorePerThread; //POSIZIONE DI START SU CUI LAVORA IL VETTORE
        int endOnWork = startOnWork+pezzoVettorePerThread;       //POSIZIONE FINALE SU CUI TERMINA IL VETTORE
        //int end = (tid != num_threads - 1 ? start + chunk : n) - 1;
        //int endOnWork = (threadPartito != n_thread - 1 ? startOnWork + pezzoVettorePerThread : N_LENGHT) - 1;

        //SE N_LEN / N_THREAD E' PARI VA BENE, OGNI THREAD SI OCCUPA DI TOT PARTI
        //SE N_LEN / N_THREAD HA IL RESTO ALLORA L'ULTIMO THREAD SI FA UN GIRO IN PIU'
        if(threadPartito == n_thread-1){ //se e' l'ultimo thread
            if (pezzoVettorePerThread%2 != 0){ //ed il vettore da' elementi dispari
                endOnWork++;
            }
        }

        cout<<"Thread "<<threadPartito<<" lavora dall'elemento: "<<startOnWork<<" all'elemento"<<endOnWork<<endl;

        float somma,temp1, temp2;
        for(int k=0;k<K_MAX_ITER;k++) { //Qui l'iterazione comunque resta come for
            cout<<"Thread"<<threadPartito<<" START ITERAZIONE "<<k<<endl;
            int i=startOnWork;
            while(i<endOnWork){
            //for (int i = startOnWork; i < endOnWork; i++) {//for esterno DELLA FORMULA
                somma = 0;
                temp1 = (1 / matriceA[i][i]);

                for (int j = 0; j < N_LENGHT; j++) {
                    if (j != i) {
                        somma = somma + (matriceA[i][j] * currentIt_vec_X[j]);
                    }
                }//fine ciclo j

                temp2 = vettoreB[i] - somma;

                nextIt_vec_X[i] = temp1 * temp2;
                i++;
            }// FINE CICLO i*/

            //SINCRONIZZO I THREAD sul vettore e sulla prossima iterazione
            //il vettore e' scambiato nell'on completion
            barrieraThread.arrive_and_wait(); //qui producono tutti ed aspettano
        }//fine for delle iterazioni
    };


    /*
    //la funzione on completion viene avviata ogni volta che i thread raggiungono tutti la barriera e quindi
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
    for(int i=0;i<n_thread;i++){
        arrayThread[i].join();
    }

    fineTempo = chrono::high_resolution_clock::now();

    cout<<endl<<nextIt_vec_X[2]<<endl;
    printArray("\nvettore x\n",nextIt_vec_X,N_LENGHT);
    std::cout<<"Tempo esecuzione: ";
    printMicroSec(inizioTempo,fineTempo);
    cout<<"Fine programma"<<endl;
    return 0;
}







//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//FUNCTIONS

void printTID_thread(){
    std::cout<<endl<<"il thread ha avviato la funzione ";
    std::thread::id this_id = std::this_thread::get_id();
    cout<<"Thread ID = "<<this_id<<endl;
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
