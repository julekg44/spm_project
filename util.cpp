//
// Created by Giuliano Galloppi on 23/08/22.
//
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <barrier>
#include "util.hpp"

using namespace std;


//OTHER FUNCTIONS------------------------------------------------------------------------------------------------------
void printMilliSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine){
    auto int_millisec = std::chrono::duration_cast<std::chrono::milliseconds>(fine-inizio).count();
    std::cout<<"Secondi: "<<int_millisec<<std::endl;
}

void printMicroSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine){
    auto microsec = std::chrono::duration_cast<std::chrono::microseconds>(fine-inizio).count();
    std::cout<<"Tempo in Microsecondi: "<<microsec<<std::endl;
}

void printTID_thread(){
    std::cout<<endl<<"il thread ha avviato la funzione ";
    std::thread::id this_id = std::this_thread::get_id();
    cout<<"Thread ID = "<<this_id<<endl;
}


//PRINT FUNCTIONS------------------------------------------------------------------------------------------------------
void printMatrix(vector<vector<float>> matrix){
    int n = matrix.size();
    cout << "Stampo la matrice di dim: "<<n<<"x"<<n<<endl;
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            printf("[%d][%d] = %.3f ",i,j,matrix[i][j]);
            //cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout<<endl;
}

void printArray(std::vector<float> array, int array_size){
    cout<<"Stampo l'array di dim"<<array_size<<endl;
    for(int h=0;h<array_size;h++){
        printf ("x[%d]: %.3f \n",h, array[h]);
    }
    cout<<endl;
}

void printVector(vector<float> vector){
    int n = vector.size();
    cout << "Printing the vector: " << endl;
    for(int i = 0; i < n; i++){
        cout << vector[i] << endl;
    }
    cout << "END" << endl;
}


//RANDOM FUNCTIONS------------------------------------------------------------------------------------------------------
float randomBetween( int lowerBound, int upperBound ) //FORTISSIMA
{
    random_device rd;
    default_random_engine eng(rd());
    //uniform_real_distribution<float> dist(lowerBound, upperBound);
    uniform_int_distribution<int> dist(lowerBound, upperBound);
    float r = dist(eng);
    /*int upperbound, lowerbound;
    //float randomBetween = rand() % (upperbound-lowerbound) + upperbound;
    return randomBetween;*/
    return r;
}

vector<vector<float>> generateRandomSquareVectorMatrix(int size, int lowerBound, int upperBound){
    int rows = size;
    int col = size;
    vector<vector<float>> m(rows,vector<float>(col));
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            m[i][j] = randomBetween(lowerBound,upperBound);
        }
    }
    return m;
}

vector<float> generateRandomVector(int size,int lowerBound, int upperBound){
    vector<float> v(size);

    for(int j=0;j<size;j++){
        v[j] = randomBetween(lowerBound,upperBound);
    }
    return v;
}



//DEFAULT FUNCTION------------------------------------------------------------------------------------------------------
vector<vector<float>> getDefaultMatrixN2(){
    int rows=2;
    int cols=2;
    vector<vector<float>> matrix(rows, vector<float>(cols));
    matrix[0][0]= 4;
    matrix[0][1] = 2;
    matrix[1][0]= 1;
    matrix[1][1] = 3;

    return matrix;
}

vector<float> getDefaultVectorBN2(){
    vector<float> vettoreB(2);
    vettoreB[0] = 8;
    vettoreB[1] = 8;

    return vettoreB;
}
//----------------------------------------------------------------------------------------------------------------------
//default N=3
vector<vector<float>> getDefaultMatrixN3(){
    int rows=3;
    int cols=3;
    vector<vector<float>> matriceA(rows, vector<float>(cols));
    matriceA[0][0]= 7;
    matriceA[0][1] = 8;
    matriceA[0][2] = 1;

    matriceA[1][0]= 8;
    matriceA[1][1] = 7;
    matriceA[1][2] = 1;

    matriceA[2][0]= 6;
    matriceA[2][1] = 6;
    matriceA[2][2] = 1;

    return matriceA;
}

vector<float> getDefaultVectorBN3(){
    vector<float> vettoreB(3);
    vettoreB[0] = -3;
    vettoreB[1] = 6;
    vettoreB[2] = 3;

    return vettoreB;
}

//----------------------------------------------------------------------------------------------------------------------
//* QUI:  FIRMA/PROT: f(&a)     -> MAIN: f(a) per modificare
//roberto non lo mette nella firma perche' sono solo in lettura
//
void startCase(vector<vector<float>>& matriceA, vector<float>& vettoreB,int size, int lb, int up){
    cout<<"Inserisci:\n0 - per generare una matrice RANDOMICA VALUES\n1 - per generare una matrice 3x3 di DEFAULT"<<endl;
    int scelta;
    cin>>scelta;
    switch(scelta) {
        case 0: //caso random
            matriceA = generateRandomSquareVectorMatrix(size,lb,up);
            vettoreB = generateRandomVector(size,lb,up);
            cout<<"Generati matrice e vettore randomici di size "<<size<<endl;
            break;
        case 1: //default
            matriceA = getDefaultMatrixN3();
            vettoreB = getDefaultVectorBN3();
            cout<<"generato default N_LEN = "<<size<<endl;
            break;
        default:
            matriceA = getDefaultMatrixN3();
            vettoreB = getDefaultVectorBN3();
            cout<<"generato default N_LEN = 3\n";
    }
}