//
// Created by Giuliano Galloppi on 29/08/22.
//
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

using namespace std;
void hello();
void printMilliSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine);

int main(){

    //ogni thread ha bisogno di una funzione iniziale/in ingresso
    //MODO DI DICHIARARE 1 + AVVIO: thread t(hello);
    //MODO DI DICHIARARE 2: thread t; t = thread(FUNCTION);
    
    thread t(hello); //QUI IL THREAD SI AVVIA AUTOMATICAMENTE APPENA COSTRUISCI L'OGGETTO (LO DICHIARI)
    std::thread my_thread([]() { cout<<"Stampa da my_thread\n"; } ); //Nelle lambda ci vogliono anche le graffe proprio come fosse una function


    t.join(); //METTERE SEMPRE IL JOIN ALLA FINE PER BLOCCARE IL MAIN THREAD FINCHE' "T" NON TERMINA
              //ALTRIMENTI RISCHIAMO CHE IL PROGRAMMA FINISCA PRIMA CHE "T" SIA TERMINATO
    my_thread.join();

    //usiamo un cronometro
    //METTI IL CRONOMETRAGGIO STESSO NEL BODY DEL THREAD 
    auto inizio = chrono::high_resolution_clock::now();
    auto fine = chrono::high_resolution_clock::now();
    
    auto int_millisec = chrono::duration_cast<chrono::milliseconds>(fine-inizio).count();
    std::cout<<"Secondi: "<<int_millisec<<endl;

    printMilliSec(inizio,fine);
    

    return 0;
}

void hello()
{
    std::cout<<"Hello Concurrent World\n";
}



void printMilliSec(std::chrono::_V2::system_clock::time_point inizio, std::chrono::_V2::system_clock::time_point fine){
    auto int_millisec = chrono::duration_cast<chrono::milliseconds>(fine-inizio).count();
    std::cout<<"Secondi: "<<int_millisec<<endl;
}