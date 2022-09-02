#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <barrier>
#include "util.hpp"
#include "utimer.cpp"

using namespace std;

//Ricorda che possono variare ITERAZIONI e THREAD
//qui compili da g++ -std=c++20 -O3 -o main_th.out main_th.cpp util.hpp util.cpp utimer.cpp

//Default values with N_LENGHT = 3 :  x=4; y=-5; z=9;
//Default values with N_LENGHT = 2 :  x=1; y=2;

int main() {
    ///dichiarazione variabili
    const int N_LENGHT = 3; //lunghezza della matrice e dei
    const int K_MAX_ITER = 2;

    vector<vector<float>> matriceA = getDefaultMatrixN3();
    vector<float> vettoreB = getDefaultVectorBN3();
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k con tutti 0 per la prima iterazione
    vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1 E' condiviso tra i thread


    int n_thread = 2; //thread
    int pezzoWorkOnPerThread = N_LENGHT / n_thread; //num di elementi 'splittati' su cui lavora ogni thread
    vector<thread> arrayThread(n_thread); //array dei thread tanti quante le righe della mat ovvero n

    std::cout<<"\n VERSIONE THREAD: Num_ITER = "<<K_MAX_ITER<<", N_LEN = "<<N_LENGHT<<", N_THREAD = "<<n_thread<<endl;

    //----------------------------------------------------------------------------------------------------------------------
    //FINITA UN ITERAZIONE SUL VETTORE X DA PARTE DI TUTTI I THREAD SI AGGIORNA IL VETTORE DELLE X DELLA NEXT_ITERATION
    auto on_completion = [&]() noexcept {
        static auto phase = "Iterazione finita thread hanno raggiunto la barriera e si cambia iterazione\n";
        std::cout << phase;
        currentIt_vec_X= nextIt_vec_X; //
    };

    std::barrier barrieraThread(n_thread, on_completion); //barriera per sincronizzare i thread

    auto lambdaJacobiThread = [&] (int threadPartito){
        int startOnWork = threadPartito * pezzoWorkOnPerThread; //POSIZIONE DI START SU CUI LAVORA IL VETTORE
        int endOnWork = startOnWork+pezzoWorkOnPerThread;       //POSIZIONE FINALE SU CUI TERMINA IL VETTORE
        //int endOnWork = (threadPartito != n_thread - 1 ? startOnWork + pezzoWorkOnPerThread : N_LENGHT) - 1;

        //SE N_LEN / N_THREAD E' PARI VA BENE, OGNI THREAD SI OCCUPA DI TOT PARTI
        //SE N_LEN / N_THREAD HA IL RESTO ALLORA L'ULTIMO THREAD SI FA UN GIRO IN PIU'
        if(threadPartito == n_thread-1){ //se e' l'ultimo thread
                endOnWork = N_LENGHT;
        }
        //cout<<"Thread "<<threadPartito<<" lavora dall'elemento: "<<startOnWork<<" all'elemento"<<endOnWork<<endl;

        float somma,temp1, temp2;
        for(int k=0;k<K_MAX_ITER;k++) { //Qui l'iterazione comunque resta come for
            //cout<<"Thread"<<threadPartito<<" START ITERAZIONE "<<k<<endl;
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
    */

    long tempo_catturato;
    utimer tempo_seq = utimer("Tempo Esecuzione VERSIONE THREAD Jacobi", &tempo_catturato); //STAMPA IL TEMPO TOTALE ALLA FINE

    for(int i=0;i<n_thread;i++){
        cout<<"parte tid "<<i<<endl;
        arrayThread[i]=thread(lambdaJacobiThread,i);
    }

    /*devono finire tutti prima della prossima iterazione*/
    for(int i=0;i<n_thread;i++){
        arrayThread[i].join();
    }

    printArray(nextIt_vec_X,N_LENGHT);
    cout<<"Fine programma"<<endl;
    return 0;
}


//NOTE:
/*Nel seq il MAIN THREAD, PER OGNI ITERAZIONE elabora una riga per volta
//Coi thread quindi lancio tanti thread A MIA SCELTA che si suddividono il vettore
//ognuno collabora a finalizzare il risultato di 'Xi' che appartiene al vettore della prossima iterazione
//il quale questo sarà aggiornato solo prima del cambio dell'iterazione,
//sincronizzato con una barrier[vedi nelle note]
 */

/*
//FIRMA: void eseguiRigaThread(float matriceA[][N_LENGHT],int n_lenght, vector<float> currentIt_vec_X, float vettoreB[N_LENGHT]);
//SEQUENZIALE: eseguiRigaThread(matriceA, N_LENGHT, currentIt_vec_X, vettoreB);
CON UN THREAD:
 * thread t {eseguiRigaThread,matriceA,N_LENGHT,currentIt_vec_X,vettoreB};
 * t.join();
 * */

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