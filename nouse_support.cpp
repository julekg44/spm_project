//
// Created by Giuliano Galloppi on 23/08/22.
//
#include <iostream>
#include <vector>
#include <chrono>
#include <barrier>
#include <random>
#include "util.hpp"

using namespace std;


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


void printVectorMatrix(vector<vector<float>> vector1,int size) {
    for(int i =0;i<size;i++){
        for(int j=0;j<size;j++){
            printf("[%d][%d] = %.2f ",i,j,vector1[i][j]);
        }
        std::cout<<endl;
    }
}
