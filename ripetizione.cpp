//12.06.22 inizio video c++

#include<iostream>

//std::cout<<.. == using namespace;
//                 cout<<...

int main(){

printf("Hello world :) \n");

//endl == \n;
}


//----------------------------------------------------------


// Created by Giuliano Galloppi on 26/03/22.
//
//  RIPETIZIONE =
//
//  Operatori:
// += aggiunge e assegna -> x += 5 e' x = x+5
// =+ assegna e poi aggiunge (nosense)
/*
 * STRINGHE:
 * altra differenza qua le stringhe hanno la classe
 * invece di usare char[] possiamo usare string
 * si usa con la libreria #include<string>
 * con '+' concateniamo due stringhe
 *
 * .size() ci dà la lunghezza della stringa
 * per accedere ad un carattere della stringa gli accediamo come
 * vettore: stringa[0], lo stesso se vogliamo modificarla.
 *
 * il 'cin' cattura solo una parola in una stringa, quindi tutto cio' dopo uno spazio non e' preso
 * usando 'getline(cin(sarebbe lo standard input[STDIN]) , nomevariabile) cosi'
 * cattura tutta la riga in una stringa
 *
 *
 *
 *
 * qui abbiamo il TIPO 'BOOL' che in c non c'era se non con la libreria stdbool.h
 * io usavo sempre 0 ed 1;
 *
 *	//COSTRUTTO SWITCH ----
 * int giorno;
 * cin>>giorno;
 * switch(giorno){
 *
 * case 1:
 *  blabla
 *  break;
 *
 * case 2:
 *
 * default: // eseguito quando il valore di giorno non e' tra quelli specificati nei case
 * break;
 *
 * }
 *
 *
 *
 * 
 * - WHILE / DO WHILE:
 * uguale in c while () {..}
 *- for(int i=0; i< 10; i++){..}
 *
 *
 * -break & continue:
 * break puo' essere usato anche in un for o in 'if' per uscire forzatamente come
 * in uno switch
 *
 *	char -> char c = 'a'
 *
 *
 * - Array[]:
 *  si dichiara int nomearray [10] oppure allocazione dinamica
 *  string nomi[2] = { "giulio", "marco" }
 *
 *
 *
 *
 * ---- PUNTATORI *********************
 *
 *  * operatore puntatore
 *  & operatore deferenziato(assegna indirizzo)
 *  int var = 1
 *  int* intPtr;
 *  intPtr = &var;
 *
 *
 *
 * a differenza dello C per fare il passaggio per riferimento (ovvero passi l'indirizzo
 * di riferimento a quella variabile) qui si mette l'& commerciale invece del puntatore
 * nel prototipo
 * e firma della funzione, e poi nel main passi la variabile 'normalmente'
 * senza &
 *
 *
 * da f(int *a) -> f(int &a)
 * nel main: f(&a) -> f(a)
 *
 * (secondo me si puo' scrivere comunqeu anche nel modo dello c)
 *
 * 
 * ------- PUNTATORE A FUNZIONE
 * 	int (*pf)(int) //pf è un puntatore ad una funzione che restituisce int
 *				   // e che riceve int come parametro
 *
 *	e' utile poichè possiamo passarlo come parametro in altre funzioni
 * cioè nella firma di una funzione DIAMO I PARAMETRI CHE DIAMO IN INGRESSO
 * ad un puntatore ad una funzione
 *
 *
 * 
 *
 * --------- ENUM
 *	enum giornoSettimana
 *			{LUN, MAR, MERC};
 *	
 *		giornoSettimana giorno = LUN;
 *	
 *	enum class t_sapori; //classe per la quale poi il tipo enum ha anche delle funzioni
 *
 * --------------------------------
 * programmazione ad oggetti in C++
 *
 * i modificatori come quelli di java qua si usano
 * con un ':' alla fine es. public:
 *
 * alla fine sono come associabili alle struct
 *
 * anche qui per accedere agli attributi dell'oggetto(variabile)
 * usiamo il punto ec. Person p1; p1.name;
 *
 * i metodi come in java si dichiarano nella classe col modificatore e poi il corpo
 * OPPURE possiamo mettere solo la firma nella classe ed all'esterno della classe
 * possiamo scrivere il corpo della funzione usando i '::'
 * es:
 * class Auto{
 * public:
 *         void funzione();
 * }
 *
 * void Auto::funzione() {
 * }
 *
 * COSTRUTTORE: uguale a java, nella classe Auto(string nome...)
 * {this.x = x...} QUI PERO' IL THIS NON CI VUOLE
 *
 * DICHIARAZIONE: Persona p("giggio","topo"); //NON SI USA IL NEW COME IN JAVA
 *
 *
 *
 *  gli attributi privati qua oltre a bloccare l'accesso non permettono
 *  nemmeno la stampa dell'attributo, percio' si usano set e get(e con get
 *  ottieni il valore per fare la print)(anche in java e' cosi')
 *
 *  l'extends qua si fa con i ':'
 *  class Stud : public Persona (perche' public)
 *
 *  qui possiamo fare la specializzazione su piu' classi,
 *  quindi mettiamo extends su piu' classi
 *  
 *
 *	fuori dalla classe:
 *	Data::Data(int gg, int mm, int aa){...}
 *  ti permette di definire fuori dalla classe il metodo 'Data'
 *  ovvero il costruttore in questo caso
 *
 *	string Data::StampaNome(){ print nome...} qui il metodo ritorna string non dimenticarlo
 *
 *	int mese() {return mm}; //metodo inline utile da tenere nella classe (che è messa in 
 *		file .h come le struct)
 * 
 *
 * */


#include<iostream>

using namespace std;

class Person{
public:
    int age;
    string name;

    void func(){
        cout<<"executed function";
    }
};





int main(int argc, char* argv[]){

    printf("***Programma di ripetizione***\n");
    int var;
    cin>>var;



    return 0;
}

void swap( int &x, int &y){
    int temp = x;
    x = y;
    y = temp;
}