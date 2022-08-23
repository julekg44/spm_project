//ORDINE DI LETTURA: 4

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<chrono>


//MISURA TEMPI DI UN ESE SEQUENZIALE - gara find e binary search
//continuo video STDLIB
//https://www.youtube.com/watch?v=jaDkjcbx5Xo&list=PL0qAPtx8YtJcdF_posHZldxX9IaY5wfPm&index=10
int main(){

    std::cout<<"INIZIO PROGRAMMA MISURA TEMPI SEQUENZIALE - chrono"<<std::endl;


    std::vector<int> tantiNumeri;
    const int QUANTI = 10000;

    tantiNumeri.reserve(QUANTI); //pre alloca la memoria per il vector per 'quanti' numeri

    //init vector
    for(int i=0; i<QUANTI; i++){
        tantiNumeri.push_back(i); //sarebbe l'append di una lista
    }
    const int QUANTE_RICERCHE = 1000;
    std::cout<<"Inizia la gara!";

    //===================================
    //===================================
    //ricerca sequenziale con find
    auto orarioInizio = std::chrono::high_resolution_clock::now();

    for(int i=0; i<QUANTE_RICERCHE; i++){
        int rVal = rand()%(QUANTI*2);
        auto it = std::find(tantiNumeri.begin(),tantiNumeri.end(),rVal);
    
    }
    auto orarioFine = std::chrono::high_resolution_clock::now();

    //CAST IN SEC E MICROSEC
    //IL METODO DURATION CAST E' PARAMETRICO, DOVE MICROSECONDS E' UN TIPO DEFINITO NELLA LIB CHRONO
    auto microsec = std::chrono::duration_cast<std::chrono::microseconds>(orarioFine-orarioInizio);
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(orarioFine-orarioInizio);
    
    std::cout<<std::endl<<"RICERCA SEQ FIND:valore in microsecondi = "<<microsec.count()<<std::endl; //SI USA IL COUNT PER LA STAMPA
    std::cout<<"RICERCA SEQ FIND:valore in secondi = "<<sec.count()<<std::endl;
    //===================================




    //RICERCA SEQUENZIALE CON BINARY SEARCH
    orarioInizio = std::chrono::high_resolution_clock::now();

    for(int i=0; i<QUANTE_RICERCHE; i++){
        int rVal = rand()%(QUANTI*2);

        bool trovato = std::binary_search(tantiNumeri.begin(),tantiNumeri.end(),rVal);
    
    }
    orarioFine = std::chrono::high_resolution_clock::now();

    microsec = std::chrono::duration_cast<std::chrono::microseconds>(orarioFine-orarioInizio);
    sec = std::chrono::duration_cast<std::chrono::seconds>(orarioFine-orarioInizio);
    
    std::cout<<std::endl<<"RICERCA binaria FIND:valore in microsecondi = "<<microsec.count()<<std::endl;
    std::cout<<"RICERCA binaria FIND:valore in secondi = "<<sec.count()<<std::endl;
    //===================================





    


    return 0;
}



