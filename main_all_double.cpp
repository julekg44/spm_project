/*Giuliano Galloppi 646443 - Progetto di SPM A.A. 2021/22 - Jacobi iterative method implementation*/
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
//compile: g++ -std=c++20 -O3 -o main_all_double.out main_all_double.cpp util.hpp util.cpp utimer.cpp -pthread
//exec: ./main_all.out [K_MAX_ITER] [N_EXECUTIONS/RUNS] [N_LENGHT_MATRIX_AND_VECTOR] [N_THREAD]
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
    std::cout<<"GIULIANO GALLOPPI 646443 - SPM Project A.Y.2021/22 - Jacobi iterative method implementation"<<endl;

    const int K_MAX_ITER = stoi(argv[1]);
    const int ESECUZIONI = stoi(argv[2]); //numero di volte in cui lanci l'esecuzione dello stesso programma per stimare una media dei tempi
    const int N_LENGHT = stoi(argv[3]); //lunghezza della matrice e dei vettori
    const int n_thread = stoi(argv[4]); //numero dei thread

    if (n_thread > N_LENGHT) {
        cout << "Error: Threads-Worker must be > N_LEN" << endl;
        exit(2);
    }

    cout << "\nAVVIO PROGRAMMA:\nK_MAX_ITERATIONS = "<<K_MAX_ITER<<", N = "<<N_LENGHT<<", LANCI/ESECUZIONI =  "<<ESECUZIONI<< ", n_Thread/Worker = " << n_thread <<endl;

    vector<vector<float>> matriceA;
    vector<float> vettoreB;
    startCase(matriceA, vettoreB, N_LENGHT, LOWER_BOUND, UPPER_BOUND,SEED);//i vector puoi passarli normalmente -  * QUI:  FIRMA/PROT: f(&a)  -> MAIN: f(a)

    long tempo_catturato; //Perchè l'oggetto utimer e' creato e distrutto ogni volta che si crea la funzione e quindi si resetta
    long double mediaTempi = 0;
    vector<double> res_nextIt_vec_X(N_LENGHT, 0); //Final vector that contains the solution founded by jacobi method

    int exit = 0;
    while (exit != -1) {
        cout <<endl<<"K_MAX_ITERATIONS = "<<K_MAX_ITER<<", N = "<<N_LENGHT<<", LANCI/ESECUZIONI =  "<<ESECUZIONI<< ", n_Thread/Worker = " << n_thread <<endl;
        cout << "INSERISCI\n1: SEQUENZIALE - 2: THREAD - 3: FAST FLOW\n5: Stampa Matrice A - 6: Stampa Vettore B\n7: Stampa Vettore X Risultato Finale\n8: Verifica se la matrice converge\n9: USCITA PROGRAMMA"<< endl;
        bool converge;
        int versione;
        cin >> versione;
        cout<<endl;
        switch (versione) {
            case 1:
                for (int e = 0; e < ESECUZIONI; e++) {
                    res_nextIt_vec_X = jacobiSeq(matriceA, vettoreB, N_LENGHT, K_MAX_ITER, tempo_catturato);
                    mediaTempi = mediaTempi + tempo_catturato;
                }
                mediaTempi = mediaTempi / ESECUZIONI;
                //cout << "\nSTAMPO nextIt_vec_X:\n";
                //printArray(res_nextIt_vec_X, N_LENGHT);
                cout << "La media del tempo sequenziale su " << ESECUZIONI << " lanci/esecuzioni e': " << mediaTempi << " μsec (usec)" << endl;
                cout<<"------------------------------------------------------------------------------------"<<endl;
                mediaTempi = 0;
                break;

            case 2:
                for (int e = 0; e < ESECUZIONI; e++) {
                    res_nextIt_vec_X = jacobiThread(matriceA, vettoreB, N_LENGHT, K_MAX_ITER, tempo_catturato, n_thread);
                    mediaTempi = mediaTempi + tempo_catturato;
                }
                mediaTempi = mediaTempi / ESECUZIONI;
                //cout << "\nSTAMPO nextIt_vec_X:\n";
                //printArray(res_nextIt_vec_X, N_LENGHT);
                cout << "La media del tempo THREAD su " << ESECUZIONI << " lanci/esecuzioni e': " << mediaTempi << " μsec (usec)" << endl;
                cout<<"------------------------------------------------------------------------------------"<<endl;
                mediaTempi = 0;
                break;

            case 3:
                for (int e = 0; e < ESECUZIONI; e++) {
                    res_nextIt_vec_X = jacobiFastFlow(matriceA, vettoreB, N_LENGHT, K_MAX_ITER, tempo_catturato, n_thread);
                    //cout<<"Tempo parziale esecuzione "<<e<<" = "<<mediaTempi<<endl;
                    mediaTempi = mediaTempi + tempo_catturato;
                }
                mediaTempi = mediaTempi / ESECUZIONI;
                //cout << "\nSTAMPO nextIt_vec_X:\n";
                //printArray(res_nextIt_vec_X, N_LENGHT);
                cout << "La media del tempo  FAST FLOW su " << ESECUZIONI << " lanci/esecuzioni e': " << mediaTempi << " μsec (usec)" << endl;
                cout<<"------------------------------------------------------------------------------------"<<endl;
                mediaTempi = 0;
                break;
            case 5:
                printMatrix(matriceA);
                break;
            case 6:
                printVector(vettoreB);
                break;
            case 7:
                printArray(res_nextIt_vec_X,N_LENGHT);
                break;
            case 8:
                converge = isConvergente(matriceA);
                cout << "La matrice converge 0=NO/1=SI : " << converge << endl;
                break;
            case 9:
                exit = -1;
                break;
            default:
                cout << "USCITA DI DEFAULT" << endl;
                exit = -1;
                break;
        }
    }
    //cout << "Fine programma" << endl;
    return 0;
}


//ALGORITMO JACOBI VERSIONE SEQUENZIALE-----------------------------------------------------------------------------------------------
vector<double> jacobiSeq(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, int K_MAX_ITER, long &tempo_catturato) {
    vector<double> currentIt_vec_X(N_LENGHT, 0);//x_k
    vector<double> nextIt_vec_X(N_LENGHT, 0); //x_k+1
    double somma, temp1, temp2;

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
        } //End external for
        currentIt_vec_X = nextIt_vec_X; //Update next iteration vector
    }
    return nextIt_vec_X;
}


//ALGORITMO JACOBI VERSIONE THREAD---------------------------------------------------------------------------------------------------------------------
vector<double> jacobiThread(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, int K_MAX_ITER,long &tempo_catturato, int n_thread) {
    //FINITA UN ITERAZIONE SUL VETTORE X DA PARTE DI TUTTI I THREAD SI AGGIORNA IL VETTORE DELLE X DELLA NEXT_ITERATION
    vector<double> currentIt_vec_X(N_LENGHT, 0);
    vector<double> nextIt_vec_X(N_LENGHT, 0);

    vector<thread> arrayThread(n_thread);
    int pieceWorkOnPerThread = N_LENGHT / n_thread; //Amount of elements which each thread works on the vector

    auto on_completion = [&]() noexcept {
        //static auto phase = "Iterazione finita thread hanno raggiunto la barriera e si cambia iterazione\n";
        currentIt_vec_X = nextIt_vec_X; //
    };

    std::barrier barrieraThread(n_thread, on_completion); //barriera per sincronizzare i thread

    auto lambdaJacobiThread = [&](int threadPartito) {
        int startOnWork = threadPartito * pieceWorkOnPerThread; //Starting position
        int endOnWork = startOnWork + pieceWorkOnPerThread;//Ending position

        if (threadPartito == n_thread - 1) { //The last thread takes all the remain elements
            endOnWork = N_LENGHT;
        }

        double somma, temp1, temp2;
        for (int k = 0; k < K_MAX_ITER; k++) {
            int i = startOnWork;
            while (i < endOnWork) {
                somma = 0;
                temp1 = (1 / matriceA[i][i]);
                for (int j = 0; j < N_LENGHT; j++) {
                    if (j != i) {
                        somma = somma + (matriceA[i][j] * currentIt_vec_X[j]);
                    }
                }
                temp2 = vettoreB[i] - somma;
                nextIt_vec_X[i] = temp1 * temp2;
                i++;
            }

            barrieraThread.arrive_and_wait(); //Thread are synchronized before the next iteration
        }
    };

    utimer tempo_seq = utimer("Tempo Esecuzione THREAD Jacobi", &tempo_catturato);
    for (int i = 0; i < n_thread; i++) {
        arrayThread[i] = thread(lambdaJacobiThread, i);
    }

    for (int i = 0; i < n_thread; i++) {
        arrayThread[i].join();
    }

    return nextIt_vec_X;
}


//-ALGORITMO JACOBI VERSIONE FAST FLOW---------------------------------------------------------------------------------------------------------------------
vector<double> jacobiFastFlow(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, int K_MAX_ITER, long &tempo_catturato, int n_thread) {
    vector<double> nextIt_vec_X(N_LENGHT, 0); //x_k+1
    vector<double> currentIt_vec_X(N_LENGHT, 0);//x_k

    int pezzoVettorePerThread = N_LENGHT / n_thread;
    ff::ParallelFor par_for_obj(n_thread);

    utimer tempo_seq = utimer("Tempo Esecuzione VERSIONE FAST_FLOW Jacobi",&tempo_catturato);
    for (int k = 0; k < K_MAX_ITER; k++) {

        par_for_obj.parallel_for(0, N_LENGHT, 1, pezzoVettorePerThread, [&](ulong i) {
            double somma = 0;
            double temp1 = (1 / matriceA[i][i]);

            for (int j = 0; j < N_LENGHT; j++) {
                if (j != i) {
                    somma = somma + (matriceA[i][j] * currentIt_vec_X[j]);
                }
            }

            double temp2 = vettoreB[i] - somma;
            nextIt_vec_X[i] = temp1 * temp2;
        }, n_thread); //FINE CICLO i

        currentIt_vec_X = nextIt_vec_X;
    }

    return nextIt_vec_X;
}