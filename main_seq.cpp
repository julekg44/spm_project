#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "util.hpp"
#include "utimer.cpp"

using namespace std;

//VERSIONE ESECUZIONE UNICA CON ITERAZIONI A 2
int main(int argc, char* argv[]) {

    //const int K_MAX_ITER = stoi(argv[1]);
    const int K_MAX_ITER = 50;
    const int N_LENGHT = 3; //lunghezza della matrice e dei vettori

    cout<<"\nSequenziale: Num_ITER = "<<K_MAX_ITER<<" N_LEN = "<<N_LENGHT<<endl;

    vector<vector<float>> matriceA;
    vector<float> vettoreB;
    //startCase(matriceA,vettoreB,N_LENGHT,-2,2);//i vector puoi passarli normalmente -  * QUI:  FIRMA/PROT: f(&a)     -> MAIN: f(a)
    matriceA = getDefaultMatrixN3();
    vettoreB = getDefaultVectorBN3();
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k
    vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1

    float somma=0;
    float temp1 = 0;
    float temp2 = 0;

    long tempo_catturato;
    utimer tempo_seq = utimer("Tempo Esecuzione Sequenziale Jacobi", &tempo_catturato); //STAMPA IL TEMPO TOTALE ALLA FINE

    for(int k=0;k<K_MAX_ITER;k++){
        //cout<<"\nITERAZIONE k ="<<k<<"\n";
        //cout<<"Array delle x iterazione"<<k<<":"<<endl;
        //printArray(currentIt_vec_X,N_LENGHT);

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

    cout<<"Stampo array finale:\n";
    printArray(nextIt_vec_X,N_LENGHT);
    //printMicroSec(inizio,fine);

    cout<<"Fine programma"<<endl;
    return 0;
}

//prende il tempo
/*auto inizio = chrono::high_resolution_clock::now();//MIO
auto fine = chrono::high_resolution_clock::now();//MIO
inizio = chrono::high_resolution_clock::now(); //MIO - funziona solo prima di utimer
*/
vector<float> jacobiSeq(vector<vector<float>> matriceA, vector<float> vettoreB, int N_LENGHT, vector<float>& currentIt_vec_X, vector<float>& nextIt_vec_X){

 return nextIt_vec_X;
}