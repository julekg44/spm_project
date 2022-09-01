#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "util.hpp"
#include "utimer.cpp"

//compila g++ -o main_seq.out main_seq.cpp util.cpp util.hpp utimer.cpp
//esegui ./main_seq.out K_MAX_ITER N_TEST/TENTATIVI/ESECUZIONI
using namespace std;

vector<float> jacobiSeq(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, vector<float>& currentIt_vec_X, vector<float>& nextIt_vec_X, int K_MAX_ITER, long& tempo_catturato);

int main(int argc, char* argv[]) {

    //const int K_MAX_ITER = 1;
    const int K_MAX_ITER = stoi(argv[1]);
    int TENTATIVI = stoi(argv[2]);
    const int N_LENGHT = 3; //lunghezza della matrice e dei vettori

    cout<<"\nSequenziale: Num_ITER = "<<K_MAX_ITER<<" N_LEN = "<<N_LENGHT<<", LANCI/ESECUZIONI =  "<<TENTATIVI<<endl;

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
    for(int exec=0;exec<TENTATIVI;exec++){
        nextIt_vec_X = jacobiSeq(matriceA,vettoreB,N_LENGHT,currentIt_vec_X,nextIt_vec_X,K_MAX_ITER,tempo_catturato);
        mediaTempi = mediaTempi+tempo_catturato;
    }
    mediaTempi = mediaTempi/TENTATIVI;
    cout<<"La media del tempo sequenziale su "<<TENTATIVI<<" tentativi/esecuzioni e': "<<mediaTempi<<endl;

    cout<<"Stampo array finale:\n";
    printArray(nextIt_vec_X,N_LENGHT);
    //printMicroSec(inizio,fine);

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