//ORDINE DI LETTURA: 4

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<chrono>

//continuo video STDLIB
//https://www.youtube.com/watch?v=jaDkjcbx5Xo&list=PL0qAPtx8YtJcdF_posHZldxX9IaY5wfPm&index=10
int main(){

    std::vector<int> tantiNumeri;
    const int QUANTI = 100;

    tantiNumeri.reserve(QUANTI); //pre alloca la memoria per il vector per 'quanti' numeri

    //init vector
    for(int i=0; i<QUANTI; i++){
        tantiNumeri.push_back(i); //sarebbe l'append di una lista
    }





    return 0;
}



