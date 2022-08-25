#include <iostream>
#include <string>
#include "util.hpp"

//std::cout == using namespace; cout<<
/* SOLO LO USING DEFINISCE CHE QUELLE FUNZIONI NON HANNO BISOGNO DI 'STD::'
using std::cout; // program uses cout
using std::cin; // program uses cin
using std::endl; // program uses endl”
*/

using namespace std;

void printMatrix(int* A[],int n);
void initTest(int n_input,int* n_len, int* A[], int x[], int B[]); //* QUI:  FIRMA/PROT: f(&a)     -> MAIN: f(a); con gli array vale lo stesso

void initTest2(int n_input,int &n_len, int* A[], int x[], int B[]); //* QUI:  FIRMA/PROT: f(&a)     -> MAIN: f(a); con gli array vale lo stesso






int main() {

    //A x = B
    //A[][] matrice
    //x vettore di variabili di lunghezza 'n'
    //n lunghezza di 'x'
    //B vettore di termini conosciuti di lunghezza n
    printStr("===== Inizio Jacobi Sequenziale =====\n");
    int n_len_vector = 0; //lunghezza n del vettore    
    int** matriceA; //Matrice
    int* vettoreX; //vettore x di lunghezza n
    int* vettoreB; // vettore risultato di lunghezza n

    //printStr("Inserisci n elementi matrice");
    //cin>>n_len_vector;

    initTest(2,&n_len_vector,matriceA,vettoreX,vettoreB);
    cout<<"il valore cambiato di n_len è:"<<n_len_vector<<endl;
    printMatrix(matriceA,n_len_vector);

    printTest();

    initTest2(3,n_len_vector,matriceA,vettoreX,vettoreB); //versione c++
    cout<<"il valore cambiato di n_len è:"<<n_len_vector<<endl;
    printMatrix(matriceA,n_len_vector);





    //tutto il calcolo del for mi serve a trovare le x




    cout<<"Fine programma"<<endl;
    return 0;
}





//FUNCTIONS----
void initTest(int n_input,int* n_len, int* A[], int x[], int B[]){
    *n_len=n_input;
    for(int i =0;i<*n_len;i++){
        A[i] = new int[*n_len];//allocazione dinamica
        for(int j=0;j<*n_len;j++){
            A[i][j] = j;
        }
    }
}


void initTest2(int n_input,int &n_len, int* A[], int x[], int B[]){ //in c++ si fa cosi'
    
    n_len=n_input;
    for(int i =0;i<n_len;i++){
        A[i] = new int[n_len];//allocazione dinamica
        for(int j=0;j<n_len;j++){
            A[i][j] = j;
        }
    }
}


void printMatrix(int* A[],int n){
    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("Elem %d,%d is = %d \n",i,j,A[i][j]);
        }
    }
}









/*
    std::cout << "Hello world xd" << std::endl;
    printTest();
    printStr("Prima\n");
    printf("PRIMA\n");

    int x = 0, y = 0;

    std::cout << "x=" << x << std::endl;
    std::cout << "y=" << y << std::endl;

    x += 5;

    y = +5;

    std::cout << "x=" << x << std::endl;
    std::cout << "y=" << y << std::endl;
*/