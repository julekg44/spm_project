#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <barrier>
#include <random>
#include "util.hpp"
#include "utimer.cpp"

//compila g++ -o main_seq.out main_seq.cpp util.cpp util.hpp utimer.cpp
//qui compili da g++ -std=c++20 -O3 -o main_th.out main_th.cpp util.hpp util.cpp utimer.cpp
//esegui ./main_seq.out K_MAX_ITER N_TEST/ESECUZIONI/ESECUZIONI
using namespace std;

vector<float> jacobiSeq(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, vector<float>& currentIt_vec_X, vector<float>& nextIt_vec_X, int K_MAX_ITER, long& tempo_catturato);
vector<float> jacobiThread(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, vector<float>& currentIt_vec_X, vector<float>& nextIt_vec_X, int K_MAX_ITER, long& tempo_catturato, int n_thread);

int main(int argc, char* argv[]) {

    //const int K_MAX_ITER = 1;
    const int K_MAX_ITER = stoi(argv[1]);
    int ESECUZIONI = stoi(argv[2]); //numero di volte in cui lanci l'esecuzione dello stesso programma per stimare una media dei tempi
    const int N_LENGHT = 3; //lunghezza della matrice e dei vettori

    cout<<"\nAVVIO PROGRAMMA ALL: Num_ITER = "<<K_MAX_ITER<<" N_LEN = "<<N_LENGHT<<", LANCI/ESECUZIONI =  "<<ESECUZIONI<<"\nn_thread=2 FISSO."<<endl;

    vector<vector<float>> matriceA;
    vector<float> vettoreB;
    matriceA=getDefaultMatrixN3();
    vettoreB=getDefaultVectorBN3();
    //startCase(matriceA,vettoreB,N_LENGHT,-10,10);//i vector puoi passarli normalmente -  * QUI:  FIRMA/PROT: f(&a)     -> MAIN: f(a)
    //printMatrix(matriceA);
    //printArray(vettoreB,N_LENGHT);

    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k
    vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1

    long tempo_catturato; //Perchè l'oggetto utimer e' creato e distrutto ogni volta che si crea la funzione e quindi si resetta
    long double mediaTempi = 0;

    /*
    //SEQUENZIALE-----------------
    for(int e=0;e<ESECUZIONI;e++){
        nextIt_vec_X = jacobiSeq(matriceA,vettoreB,N_LENGHT,currentIt_vec_X,nextIt_vec_X,K_MAX_ITER,tempo_catturato);
        cout<<"parziale"<<mediaTempi<<endl;
        mediaTempi = mediaTempi+tempo_catturato;
    }
    mediaTempi = mediaTempi/ESECUZIONI;
    cout<<"La media del tempo sequenziale su "<<ESECUZIONI<<" ESECUZIONI/esecuzioni e': "<<mediaTempi<<endl;

    */


    //thread------------------------------
    int n_thread = 2; //thread
    for(int e=0;e<ESECUZIONI;e++){
        nextIt_vec_X = jacobiThread(matriceA,vettoreB,N_LENGHT,currentIt_vec_X,nextIt_vec_X,K_MAX_ITER,tempo_catturato,n_thread);
        cout<<"parziale"<<mediaTempi<<endl;
        mediaTempi = mediaTempi+tempo_catturato;
    }
    mediaTempi = mediaTempi/ESECUZIONI;
    cout<<"La media del tempo sequenziale su "<<ESECUZIONI<<" ESECUZIONI/esecuzioni e': "<<mediaTempi<<endl;







    
    
    cout<<"\nSTAMPO nextIt_vec_X:\n";
    printArray(nextIt_vec_X,N_LENGHT);
    cout<<"Fine programma"<<endl;
    return 0;
}


vector<float> jacobiSeq(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, vector<float>& currentIt_vec_X, vector<float>& nextIt_vec_X, int K_MAX_ITER, long& tempo_catturato){

    utimer tempo_seq = utimer("Tempo Esecuzione Sequenziale Jacobi", &tempo_catturato); //STAMPA IL TEMPO TOTALE ALLA FINE

    float somma,temp1,temp2;

    for(int k=0;k<K_MAX_ITER;k++){

        for(int i=0; i<N_LENGHT; i++) { //for esterno DELLA FORMULA
            //cout<<"\nENTRA CICLO i = "<<i<<endl;
            somma = 0;
            //cout<<"valore Mat["<<i<<"]"<<"["<<i<<"]"<<" = "<<matriceA[i][i]<<endl;
            //cout<<"temp1 = 1 / mat[i][i]:"<<matriceA[i][i]<<endl;
            temp1 = (1 / matriceA[i][i]);
            //cout<<"valore temp1 = "<<temp1<<", valore somma = "<<somma<<endl;

            for(int j=0;j<N_LENGHT;j++){
                //cout<<"\nENTRA CICLO J = "<<j<<endl;
                //cout<<"valore Mat["<<i<<"]"<<"["<<j<<"]"<<" = "<<matriceA[i][j]<<endl;
                //cout<<"valore somma:"<<somma<<" PRIMA del ciclo con I="<<i<<" e J = "<<j<<endl;
                if (j != i ){
                    somma = somma + ( matriceA[i][j] * currentIt_vec_X[j] ) ;
                }
            }//fine for delle j

            //cout<<"VALORE somma DOPO ciclo ="<<somma<<endl;
            temp2 = vettoreB[i] - somma;
            //cout<<"RISULTATO temp1="<<temp1<<" temp 2 = "<<temp2<<endl;
            nextIt_vec_X[i] = temp1*temp2;
            //cout<<"valore di x[i] nella nuova iterazione nextX["<<i<<"]= "<<nextIt_vec_X[i]<<endl<<endl;

        } // FINE CICLO i
        //cout<<"Aggiorno il nuovo vettore prima dell'iteraz k+1 current=next"<<endl;;
        currentIt_vec_X= nextIt_vec_X;
    }//fine for delle iterazioni
    //fine = chrono::high_resolution_clock::now();
    return nextIt_vec_X;
}

vector<float> jacobiThread(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, vector<float>& currentIt_vec_X, vector<float>& nextIt_vec_X, int K_MAX_ITER, long& tempo_catturato, int n_thread) {
    //----------------------------------------------------------------------------------------------------------------------
    //FINITA UN ITERAZIONE SUL VETTORE X DA PARTE DI TUTTI I THREAD SI AGGIORNA IL VETTORE DELLE X DELLA NEXT_ITERATION

    vector<thread> arrayThread(n_thread); //array dei thread tanti quante le righe della mat ovvero n
    int pezzoWorkOnPerThread = N_LENGHT / n_thread; //num di elementi 'splittati' su cui lavora ogni thread

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
            if (pezzoWorkOnPerThread%2 != 0){ //ed il vettore da' elementi dispari
                endOnWork++;
            }
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

    utimer tempo_seq = utimer("Tempo Esecuzione THREAD Jacobi", &tempo_catturato); //STAMPA IL TEMPO TOTALE ALLA FINE
    for(int i=0;i<n_thread;i++){
        cout<<"parte tid "<<i<<endl;
        arrayThread[i]=thread(lambdaJacobiThread,i);
    }
    /*devono finire tutti prima della prossima iterazione*/
    for(int i=0;i<n_thread;i++){
        arrayThread[i].join();
    }

    return nextIt_vec_X;
}