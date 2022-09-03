#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <barrier>

#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>

#include "util.hpp"
#include "utimer.cpp"

#define LOWER_BOUND 0 //1
#define UPPER_BOUND 20 //4
#define SEED 3

//option command L fai il reformatting del codice
//compila g++ -o main_seq.out main_seq.cpp util.cpp util.hpp utimer.cpp
//qui compili da g++ -std=c++20 -O3 -o main_th.out main_th.cpp util.hpp util.cpp utimer.cpp

////qui compili da g++ -std=c++20 -O3 -o main_all.out main_all.cpp util.hpp util.cpp utimer.cpp -pthread

//esegui ./main_all.out "K_MAX_ITER" "N_TEST/ESECUZIONI/ESECUZIONI" "N_LENGHT_MATRIX_AND_VECTOR" "N_THREAD"
using namespace std;

vector<double> jacobiSeq(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, int K_MAX_ITER, long &tempo_catturato);
vector<double> jacobiThread(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, int K_MAX_ITER, long &tempo_catturato, int n_thread);
vector<double> jacobiFastFlow(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, int K_MAX_ITER, long &tempo_catturato, int n_thread);

int main(int argc, char *argv[]) {

    if (argc > 5 || argc < 5) { //Check arguments by command line
        cout << "Usage: " << argv[0]
             << " \"K_MAX_ITER\" \"N_TEST/ESECUZIONI/ESECUZIONI\" \"N_LENGHT_MATRIX_AND_VECTOR\" \"N_THREAD\" " << endl;
        exit(1);
    }

    const int K_MAX_ITER = stoi(argv[1]);
    const int ESECUZIONI = stoi(argv[2]); //numero di volte in cui lanci l'esecuzione dello stesso programma per stimare una media dei tempi
    const int N_LENGHT = stoi(argv[3]); //lunghezza della matrice e dei vettori
    const int n_thread = stoi(argv[4]); //numero dei thread

    if (n_thread > N_LENGHT) {
        cout << "Error: Threads-Worker must be > N_LEN" << endl;
        exit(2);
    }

    cout << "\nAVVIO PROGRAMMA ALL: Num_ITER = " << K_MAX_ITER << " N_LEN = " << N_LENGHT << ", LANCI/ESECUZIONI =  "
         << ESECUZIONI << ", n_thread = " << n_thread << endl;

    vector<vector<float>> matriceA;
    vector<float> vettoreB;
    startCase(matriceA, vettoreB, N_LENGHT, LOWER_BOUND, UPPER_BOUND,SEED);//i vector puoi passarli normalmente -  * QUI:  FIRMA/PROT: f(&a)  -> MAIN: f(a)

    //printArray(vettoreB,N_LENGHT);
    //LE X me le faccio locali perche' vanno a 0 ad ogni nuovo lancio di jacobi     //vector<float>currentIt_vec_X(N_LENGHT,0);//x_k     //vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1

    //vector<double>res_nextIt_vec_X(N_LENGHT,0);//vettore finale di uscita trovato dalle funzioni jacobi
    long tempo_catturato; //Perchè l'oggetto utimer e' creato e distrutto ogni volta che si crea la funzione e quindi si resetta
    long double mediaTempi = 0;

    int exit = 0;
    while (exit != -1) {
        vector<double> res_nextIt_vec_X(N_LENGHT, 0);//vettore finale di uscita trovato dalle funzioni jacobi
        cout << endl << endl;
        cout << "K_MAX_ITER = " << K_MAX_ITER << " N_LEN = " << N_LENGHT << ", LANCI/ESECUZIONI =  "<< ESECUZIONI << ", n_thread = " << n_thread << endl;
        cout << "INSERISCI\n1:SEQUENZIALE - 2:THREAD - 3:FAST FLOW\n7:Stampa Matrice A - 8:Verifica se la matrice converge - 9:USCITA PROGRAMMA" << endl;
        bool converge;
        int versione;
        cin >> versione;
        switch (versione) {
            case 1:
                for (int e = 0; e < ESECUZIONI; e++) {
                    res_nextIt_vec_X = jacobiSeq(matriceA, vettoreB, N_LENGHT, K_MAX_ITER, tempo_catturato);
                    //cout<<"Tempo parziale esecuzione "<<e<<" = "<<mediaTempi<<endl;
                    mediaTempi = mediaTempi + tempo_catturato;
                }
                mediaTempi = mediaTempi / ESECUZIONI;
                cout << "\nSTAMPO nextIt_vec_X:\n";
                printArray(res_nextIt_vec_X, N_LENGHT);
                cout << "La media del tempo sequenziale su " << ESECUZIONI << " lanci/esecuzioni e': " << mediaTempi
                     << " μsec (usec)" << endl;
                mediaTempi = 0;
                break;

            case 2:
                for (int e = 0; e < ESECUZIONI; e++) {
                    res_nextIt_vec_X = jacobiThread(matriceA, vettoreB, N_LENGHT, K_MAX_ITER, tempo_catturato,
                                                    n_thread);
                    //cout<<"Tempo parziale esecuzione "<<e<<" = "<<mediaTempi<<endl;
                    mediaTempi = mediaTempi + tempo_catturato;
                }
                mediaTempi = mediaTempi / ESECUZIONI;
                cout << "\nSTAMPO nextIt_vec_X:\n";
                printArray(res_nextIt_vec_X, N_LENGHT);
                cout << "La media del tempo THREAD su " << ESECUZIONI << " lanci/esecuzioni e': " << mediaTempi
                     << " μsec (usec)" << endl;
                mediaTempi = 0;
                break;

            case 3:
                for (int e = 0; e < ESECUZIONI; e++) {
                    res_nextIt_vec_X = jacobiFastFlow(matriceA, vettoreB, N_LENGHT, K_MAX_ITER, tempo_catturato,
                                                      n_thread);
                    //cout<<"Tempo parziale esecuzione "<<e<<" = "<<mediaTempi<<endl;
                    mediaTempi = mediaTempi + tempo_catturato;
                }
                mediaTempi = mediaTempi / ESECUZIONI;
                cout << "\nSTAMPO nextIt_vec_X:\n";
                printArray(res_nextIt_vec_X, N_LENGHT);
                cout << "La media del tempo  FAST FLOW su " << ESECUZIONI << " lanci/esecuzioni e': " << mediaTempi
                     << " μsec (usec)" << endl;
                mediaTempi = 0;
                break;

            case 7:
                printMatrix(matriceA);
                break;
            case 8:
                converge = isConvergente(matriceA);
                //converge = isDDM(matriceA,N_LENGHT);
                cout << "La matrice converge: " << converge << endl;
                break;
            case 9:
                exit = -1;
                break;
            default:
                cout << "DI DEFAULT esci" << endl;
                exit = -1;
                break;
        }
    }


    /*
    //SEQUENZIALE-----------------
    for(int e=0;e<ESECUZIONI;e++){
        res_nextIt_vec_X = jacobiSeq(matriceA,vettoreB,N_LENGHT,K_MAX_ITER,tempo_catturato);
        cout<<"parziale"<<mediaTempi<<endl;
        mediaTempi = mediaTempi+tempo_catturato;
    }
    mediaTempi = mediaTempi/ESECUZIONI;
    cout<<"La media del tempo sequenziale su "<<ESECUZIONI<<" ESECUZIONI/esecuzioni e': "<<mediaTempi<<endl;
    */

    /*
    //thread------------------------------
    for(int e=0;e<ESECUZIONI;e++){
        res_nextIt_vec_X = jacobiThread(matriceA,vettoreB,N_LENGHT,K_MAX_ITER,tempo_catturato,n_thread);
        cout<<"parziale"<<mediaTempi<<endl;
        mediaTempi = mediaTempi+tempo_catturato;
    }
    mediaTempi = mediaTempi/ESECUZIONI;
    cout<<"La media del tempo sequenziale su "<<ESECUZIONI<<" ESECUZIONI/esecuzioni e': "<<mediaTempi<<endl;
    */

    /*
    //fastflow-----------------------------
     for(int e=0;e<ESECUZIONI;e++){
         res_nextIt_vec_X = jacobiFastFlow(matriceA,vettoreB,N_LENGHT,K_MAX_ITER,tempo_catturato,n_thread);
         cout<<"parziale"<<mediaTempi<<endl;
         mediaTempi = mediaTempi+tempo_catturato;
     }
     mediaTempi = mediaTempi/ESECUZIONI;
     cout<<"La media del tempo  su "<<ESECUZIONI<<" ESECUZIONI/esecuzioni e': "<<mediaTempi<<endl;
     */

    cout << "Fine programma" << endl;
    return 0;
}


//ALGORITMO JACOBI VERSIONE SEQUENZIALE-----------------------------------
vector<double> jacobiSeq(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, int K_MAX_ITER, long &tempo_catturato) {

    vector<double> currentIt_vec_X(N_LENGHT, 0);//x_k
    vector<double> nextIt_vec_X(N_LENGHT, 0); //x_k+1
    double somma, temp1, temp2;

    utimer tempo_seq = utimer("Tempo Esecuzione Sequenziale Jacobi",
                              &tempo_catturato); //STAMPA IL TEMPO TOTALE ALLA FINE
    for (int k = 0; k < K_MAX_ITER; k++) {

        for (int i = 0; i < N_LENGHT; i++) { //for esterno DELLA FORMULA
            //cout<<"\nENTRA CICLO i = "<<i<<endl;
            somma = 0;
            //cout<<"valore Mat["<<i<<"]"<<"["<<i<<"]"<<" = "<<matriceA[i][i]<<endl;
            //cout<<"temp1 = 1 / mat[i][i]:"<<matriceA[i][i]<<endl;
            temp1 = (1 / matriceA[i][i]);
            //cout<<"valore temp1 = "<<temp1<<", valore somma = "<<somma<<endl;

            for (int j = 0; j < N_LENGHT; j++) {
                //cout<<"\nENTRA CICLO J = "<<j<<endl;
                //cout<<"valore Mat["<<i<<"]"<<"["<<j<<"]"<<" = "<<matriceA[i][j]<<endl;
                //cout<<"valore somma:"<<somma<<" PRIMA del ciclo con I="<<i<<" e J = "<<j<<endl;
                if (j != i) {
                    somma = somma + (matriceA[i][j] * currentIt_vec_X[j]);
                }
            }//fine for delle j

            //cout<<"VALORE somma DOPO ciclo ="<<somma<<endl;
            temp2 = vettoreB[i] - somma;
            //cout<<"RISULTATO temp1="<<temp1<<" temp 2 = "<<temp2<<endl;
            nextIt_vec_X[i] = temp1 * temp2;
            //cout<<"valore di x[i] nella nuova iterazione nextX["<<i<<"]= "<<nextIt_vec_X[i]<<endl<<endl;

        } // FINE CICLO i
        //cout<<"Aggiorno il nuovo vettore prima dell'iteraz k+1 current=next"<<endl;;
        currentIt_vec_X = nextIt_vec_X;
    }//fine for delle iterazioni
    //fine = chrono::high_resolution_clock::now();
    return nextIt_vec_X;
}


//ALGORITMO JACOBI VERSIONE THREAD---------------------------------------------------------------------------------------------------------------------------------------------------------------
vector<double> jacobiThread(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, int K_MAX_ITER,
                            long &tempo_catturato, int n_thread) {
    //FINITA UN ITERAZIONE SUL VETTORE X DA PARTE DI TUTTI I THREAD SI AGGIORNA IL VETTORE DELLE X DELLA NEXT_ITERATION
    vector<double> currentIt_vec_X(N_LENGHT, 0);//x_k
    vector<double> nextIt_vec_X(N_LENGHT, 0); //x_k+1

    vector<thread> arrayThread(n_thread); //array dei thread tanti quante le righe della mat ovvero n
    int pezzoWorkOnPerThread = N_LENGHT / n_thread; //num di elementi 'splittati' su cui lavora ogni thread

    auto on_completion = [&]() noexcept {
        static auto phase = "Iterazione finita thread hanno raggiunto la barriera e si cambia iterazione\n";
        //std::cout << phase;
        currentIt_vec_X = nextIt_vec_X; //
    };

    std::barrier barrieraThread(n_thread, on_completion); //barriera per sincronizzare i thread

    auto lambdaJacobiThread = [&](int threadPartito) {
        int startOnWork = threadPartito * pezzoWorkOnPerThread; //POSIZIONE DI START SU CUI LAVORA IL VETTORE
        int endOnWork = startOnWork + pezzoWorkOnPerThread;       //POSIZIONE FINALE SU CUI TERMINA IL VETTORE
        //int endOnWork = (threadPartito != n_thread - 1 ? startOnWork + pezzoWorkOnPerThread : N_LENGHT) - 1;

        //SE N_LEN / N_THREAD E' PARI VA BENE, OGNI THREAD SI OCCUPA DI TOT PARTI
        //SE N_LEN / N_THREAD HA IL RESTO ALLORA L'ULTIMO THREAD SI FA UN GIRO IN PIU'
        if (threadPartito == n_thread - 1) { //se e' l'ultimo thread
            endOnWork = N_LENGHT;
        }//cout<<"Thread "<<threadPartito<<" lavora dall'elemento: "<<startOnWork<<" all'elemento"<<endOnWork<<endl;

        double somma, temp1, temp2;
        for (int k = 0; k < K_MAX_ITER; k++) { //Qui l'iterazione comunque resta come for
            //cout<<"Thread"<<threadPartito<<" START ITERAZIONE "<<k<<endl;
            int i = startOnWork;
            while (i < endOnWork) {

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
    for (int i = 0; i < n_thread; i++) {
        cout << "parte tid " << i << endl;
        arrayThread[i] = thread(lambdaJacobiThread, i);
    }
    /*devono finire tutti prima della prossima iterazione*/
    for (int i = 0; i < n_thread; i++) {
        arrayThread[i].join();
    }

    return nextIt_vec_X;
}


//ALGORITMO JACOBI VERSIONE FAST FLOW----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
vector<double> jacobiFastFlow(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, int K_MAX_ITER,
                              long &tempo_catturato, int n_thread) {
    vector<double> nextIt_vec_X(N_LENGHT, 0); //x_k+1
    vector<double> currentIt_vec_X(N_LENGHT, 0);//x_k - //i vettori x sono inizializzati entrambi a 0

    int pezzoVettorePerThread = N_LENGHT / n_thread;
    ff::ParallelFor par_for_obj(n_thread); //utilizza tot thread/worker , come la versione thread ma con ff


    utimer tempo_seq = utimer("Tempo Esecuzione VERSIONE FAST_FLOW Jacobi",
                              &tempo_catturato); //STAMPA IL TEMPO TOTALE ALLA FINE
    for (int k = 0; k < K_MAX_ITER; k++) {

        //for(int i=0; i<N_LENGHT; i++) { //for esterno DELLA FORMULA
        par_for_obj.parallel_for(0, N_LENGHT, 1, pezzoVettorePerThread, [&](ulong i) {
            double somma = 0;
            double temp1 = (1 / matriceA[i][i]);

            for (int j = 0; j < N_LENGHT; j++) {
                if (j != i) {
                    somma = somma + (matriceA[i][j] * currentIt_vec_X[j]);
                }
            }//fine for delle j

            double temp2 = vettoreB[i] - somma;
            nextIt_vec_X[i] = temp1 * temp2;
        }, n_thread); //FINE CICLO i

        currentIt_vec_X = nextIt_vec_X;
        //cout<<"FINE EXECUTION FF"<<endl;
    }//fine for delle iterazioni

    return nextIt_vec_X;
}