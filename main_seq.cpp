#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "util.hpp"

//std::cout == using namespace; cout<<
/* SOLO LO USING DEFINISCE CHE QUELLE FUNZIONI NON HANNO BISOGNO DI 'STD::'
using std::cout; // program uses cout
using std::cin; // program uses cin
using std::endl; // program uses endl”
*/

using namespace std;
//Default values with N_LENGHT = 3 :  x=4; y=-5; z=9;
//Default values with N_LENGHT = 2 :  x=1; y=2;
const int N_LENGHT = 2; //lunghezza della matrice e dei

///var globali
float matriceA [N_LENGHT][N_LENGHT];
float vettoreB[N_LENGHT];
//currentIt_vec_X
vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1 E' condiviso tra i thread

void defaultMatrix2N();
void defaultMatrix3N();
void defaultVettoreB_2N();
void defaultVettoreB_3N();


void printMatrix(int* A[],int n);
void printSistema(int* A[],int n, int x[], int B[]);
void printMatrixNoSize(int* A[]);
void initTest(int n_input,int* n_len, int* A[], int x[], int B[]); //* QUI:  FIRMA/PROT: f(&a)     -> MAIN: f(a); con gli array vale lo stesso

void initTest2(int n_input,int &n_len, int* A[], int x[], int B[]); //* QUI:  FIRMA/PROT: f(&a)     -> MAIN: f(a); con gli array vale lo stesso
void riempiMatrice(int** mat, int n);

void printArray(string msg, int array[], int array_size);


void printVectorMatrix(vector<vector<float>> vector1,int size);



int main() {
    const int K_MAX_ITER = 1;

    printStr("===== Inizio Jacobi Sequenziale =====\n");
    //------------------------------------------------------------
    printStr("Alloco Matrice ed elementi\n");
    switch (N_LENGHT) {
        case 2:
            defaultMatrix2N();
            defaultVettoreB_2N();
        case 3:
            defaultMatrix3N();
            defaultVettoreB_3N();
    }


    // tutto il calcolo del for mi serve a trovare le x
    //const int K_MAX_ITER = 2;
    float somma=0;
    float temp1 = 0;
    float temp2 = 0;
    vector<float>currentIt_vec_X(N_LENGHT,0);//x_k
    vector<float>nextIt_vec_X(N_LENGHT,0); //x_k+1
    auto inizio = chrono::high_resolution_clock::now();
    auto fine = chrono::high_resolution_clock::now();

    int val;

    //k e' il numero delle iterazioni
    inizio = chrono::high_resolution_clock::now();
    for(int k=0;k<K_MAX_ITER;k++){
        cout<<"\nITERAZIONE k ="<<k<<"\n";
        cout<<"Array delle x iterazione"<<k<<":"<<endl;
        printArray("",currentIt_vec_X,N_LENGHT);

        for(int i=0; i<N_LENGHT; i++) { //for esterno DELLA FORMULA
            cout<<"\nENTRA CICLO i = "<<i<<endl;
            somma = 0;
            cout<<"valore Mat["<<i<<"]"<<"["<<i<<"]"<<" = "<<matriceA[i][i]<<endl;
            cout<<"temp1 = 1 / mat[i][i]:"<<matriceA[i][i]<<endl;
            temp1 = (1 / matriceA[i][i]);
            cout<<"valore temp1 = "<<temp1<<", valore somma = "<<somma<<endl;

            for(int j=0;j<N_LENGHT;j++){
                cout<<"\nENTRA CICLO J = "<<j<<endl;
                cout<<"valore Mat["<<i<<"]"<<"["<<j<<"]"<<" = "<<matriceA[i][j]<<endl;
                cout<<"valore somma:"<<somma<<" PRIMA del ciclo con I="<<i<<" e J = "<<j<<endl;
                if (j != i ){

                    somma = somma + ( matriceA[i][j] * currentIt_vec_X[j] ) ;

                }
            }//fine for delle j

            cout<<"VALORE somma DOPO ciclo ="<<somma<<endl;
            temp2 = vettoreB[i] - somma;
            cout<<"RISULTATO temp1="<<temp1<<" temp 2 = "<<temp2<<endl;
            nextIt_vec_X[i] = temp1*temp2;
            cout<<"valore di x[i] nella nuova iterazione nextX["<<i<<"]= "<<nextIt_vec_X[i]<<endl<<endl;

        } // FINE CICLO i
        cout<<"Aggiorno il nuovo vettore prima dell'iteraz k+1 current=next"<<endl;;
        currentIt_vec_X= nextIt_vec_X;
        temp1=0;
        temp2=0;

    }//fine for delle iterazioni
    fine = chrono::high_resolution_clock::now();




    printArray("\nvettore x\n",nextIt_vec_X,N_LENGHT);
    printMicroSec(inizio,fine);


    cout<<"Fine programma"<<endl;
    return 0;
}



/*
     //la matrice è necessariamente quadrata

    //matriceA = new int*[N_LENGHT]; //IL SIMBOLO DEL PUNTATORE VA DOPO L'INT E MAI PRIMA PORCO ZIO, alloco due puntatori
    //matriceA[0] = new int[N_LENGHT]; //ogni puntatore è un vettore di due elementi
    //matriceA[1] = new int[N_LENGHT];

    //int rows = ..., cols = ...;
    //int** matrix = new int*[rows];
    //for (int i = 0; i < rows; ++i)
    //matrix[i] = new int[cols];
*/








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


void printArray(string msg, int array[], int array_size){
    std::cout<<msg;
    for(int h=0;h<array_size;h++){
        cout<<"["<<h<<"] = "<<array[h]<<endl;
    }

}






void printVectorMatrix(vector<vector<float>> vector1,int size) {
    for(int i =0;i<size;i++){
        for(int j=0;j<size;j++){
            printf("[%d][%d] = %.2f ",i,j,vector1[i][j]);
        }
        std::cout<<endl;
    }
}



void defaultMatrix2N(){
    matriceA[0][0]= 4;
    matriceA[0][1] = 2;
    matriceA[1][0]= 1;
    matriceA[1][1] = 3;
}

void defaultMatrix3N(){
    matriceA[0][0]= 7;
    matriceA[0][1] = 8;
    matriceA[0][2] = 1;

    matriceA[1][0]= 8;
    matriceA[1][1] = 7;
    matriceA[1][2] = 1;

    matriceA[2][0]= 6;
    matriceA[2][1] = 6;
    matriceA[2][2] = 1;

}

void defaultVettoreB_2N(){
    vettoreB[0] = 8;
    vettoreB[1] = 8;
}

void defaultVettoreB_3N(){
    vettoreB[0] = -3;
    vettoreB[1] = 6;
    vettoreB[2] = 3;
    // x=4; y=-5; z=9
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


/*
 * ULTIMO
 *  //k e' il numero delle iterazioni
    for(int k=0;k<K_MAX_ITER;k++){
        cout<<"\nITERAZIONE k ="<<k<<"\n";
        cout<<"Array delle x iterazione"<<k<<":"<<endl;
        printArray("",currentIt_vec_X,N_LENGHT);

        for(int i=0; i<N_LENGHT; i++) { //for esterno DELLA FORMULA
            somma = 0;
            temp1 = (1 / matriceA[i][i]);
            cout<<"valore temp1= "<<temp1<<" valore somma = "<<somma<<endl;

            for(int j=0;j<N_LENGHT;j++){
                cout<<"\nENTRA CICLO J = "<<j<<endl;
                cout<<"valore somma:"<<somma<<" PRIMA del ciclo con I="<<i<<" e J = "<<j<<endl;
                if (j != i ){

                    somma = somma + ( matriceA[i][j] * currentIt_vec_X[j] ) ;

                }
            }//fine for delle j

            cout<<"VALORE somma DOPO ciclo ="<<somma<<endl;
            temp2 = vettoreB[i] - somma;
            cout<<"RISULTATO temp1="<<temp1<<" temp 2 = "<<temp2<<endl;
            nextIt_vec_X[i] = temp1*temp2;
            cout<<"valore di x[i] nella nuova iterazione nextX["<<i<<"]= "<<nextIt_vec_X[i]<<endl<<endl;

        } // FINE CICLO i
        cout<<"Aggiorno il nuovo vettore prima dell'iteraz k+1 current=next"<<endl;;
        currentIt_vec_X= nextIt_vec_X;
        temp1=0;
        temp2=0;

    }//fine for delle iterazioni
*/