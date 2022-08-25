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
void printSistema(int* A[],int n, int x[], int B[]);
void printMatrixNoSize(int* A[]);
void initTest(int n_input,int* n_len, int* A[], int x[], int B[]); //* QUI:  FIRMA/PROT: f(&a)     -> MAIN: f(a); con gli array vale lo stesso

void initTest2(int n_input,int &n_len, int* A[], int x[], int B[]); //* QUI:  FIRMA/PROT: f(&a)     -> MAIN: f(a); con gli array vale lo stesso
void riempiMatrice(int** mat, int n);
int** generaMatrice(int size);






int main() {

    //A x = B
    //A[][] matrice
    //x vettore di variabili di lunghezza 'n'
    //n lunghezza di 'x'
    //B vettore di termini conosciuti di lunghezza n
    printStr("===== Inizio Jacobi Sequenziale =====\n");
    int n_len_vector = 0; //lunghezza n del vettore    
    int** matDinamica; //Matrice
    int** matriceA;
    int* x; //vettore x di lunghezza n
    int* B; // vettore risultato di lunghezza n

    //printStr("Inserisci n elementi matrice");
    //cin>>n_len_vector;
    //int matriceA[n_len_vector][n_len_vector]; //Matrice
    /*CANCELLARE DA QUA
    initTest(2,&n_len_vector,matDinamica,vettoreX,vettoreB);
    cout<<"il valore cambiato di n_len è:"<<n_len_vector<<endl;
    printMatrix(matDinamica,n_len_vector);

    printTest();

    initTest2(3,n_len_vector,matDinamica,vettoreX,vettoreB); //versione c++
    cout<<"il valore cambiato di n_len è:"<<n_len_vector<<endl;
    printMatrix(matDinamica,n_len_vector);
    */

    //int rows = ..., cols = ...;
    //int** matrix = new int*[rows];
    //for (int i = 0; i < rows; ++i)
    //matrix[i] = new int[cols];

    //------------------------------------------------------------
    printStr("Alloco Matrice ed elementi\n");
    //la matrice è necessariamente quadrata
    const int N_LENGHT = 2; //lunghezza della matrice e dei vettori
    matriceA = new int*[N_LENGHT]; //IL SIMBOLO DEL PUNTATORE VA DOPO L'INT E MAI PRIMA PORCO ZIO, alloco due puntatori
    matriceA[0] = new int[N_LENGHT]; //ogni puntatore è un vettore di due elementi
    matriceA[1] = new int[N_LENGHT];

    matriceA[0][0]= 2;
    matriceA[0][1] = 1;
    matriceA[1][0]= 3;
    matriceA[1][1] = 1;

    int vettoreX[N_LENGHT]; //vettore delle x
    for(int h=0;h<N_LENGHT;h++){
        vettoreX[h]=h+2;
    }
    int vettoreB[N_LENGHT] = {6,4};

    printTest();

    //printSistema(matriceA,N_LENGHT,vettoreX,vettoreB);
    
    //tutto il calcolo del for mi serve a trovare le x
    int somma=0;
    int temp1 = 0;
    int temp2 = 0;
        printTest();

    
    for(int i=1; i<=N_LENGHT; i++) { //for esterno
    cout<<"INIZIO FOR";

        //x[i] = temp1 * temp2;
        somma = 0;
        int temp1 = (1 / matriceA[i][i]);

        for(int j=1;j<=N_LENGHT;j++){
            if (j!=i){
                somma = somma + matriceA[i][j] * vettoreX[j];
            }
        }//fine for delle j
        temp2 = B[i] - somma; 
        vettoreX[i] = temp1*temp2;

    } //fine for delle 'i'
        












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

    puts("Stampa matrice");
    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("[%d][%d] = %d ",i,j,A[i][j]);
        }
        std::cout<<endl;
    }
}


void printSistema(int* A[],int n, int x[], int B[]){

    puts("Stampa sistema");
    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            if((j+1)==n){
                printf("%d x%d = ",A[i][j],i); 
            }else{
                printf("%dx%d , ",A[i][j],i); 
            }
        }
        std::cout<<B[i]<<endl;
    }
}


void riempiMatrice(int** mat, int n){ //ROTTO

    mat = new int*[n];
    for(int i =0;i<n;i++){
        mat[i] = new int[n];//allocazione dinamica
        for(int j=0;j<n;j++){
            mat[i][j] = j;
        }
    }



}

int** generaMatrice(int size){ //ROTTO

    int** mat;

    riempiMatrice(mat,size);

    return mat;
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