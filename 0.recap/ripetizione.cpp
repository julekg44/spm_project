//ORDINE DI LETTURA: 1
//12.06.22 inizio video c++

//std::cout<<.. == using namespace;
//                 cout<<...

/*
int main(){

printf("Hello world :) \n");

//endl == \n;
}
*/


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
 * *********IMPORTANTE*******
 * a differenza dello C per fare il passaggio per riferimento 
 * (ovvero passi l'indirizzo di riferimento a quella variabile) 
 * qui si mette l'& commerciale invece del puntatore nel prototipo e firma della funzione,
 * e poi nel main passi la variabile 'normalmente'
 * senza &
 *
 *
 * da c: FIRMA/PROT: f(int *a) -> MAIN: f(int &a)
 * QUI:  FIRMA/PROT: f(&a)     -> MAIN: f(a)
 *
 * (secondo me si puo' scrivere comunque anche nel modo dello c)
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
 * non si possono avere gli stessi valori di enumerazione in due 'enum' diversi, ad es. due 'verde'
 * con enum class si può fare invece
 *
 *	enum class t_sapori; //classe per la quale poi il tipo enum ha anche delle funzioni
 *  t_sapori var = t_sapori::dolce;
 * 
 * la classe si può anche definire tra i prototipi ad inizio file
 *
 * --------------------------------
 * --------------------------------
 * programmazione ad oggetti in C++
 *
 * i modificatori come quelli di java qua si usano
 * con un ':' alla fine es. public:
 *
 * METTERE PRIMA LA PARTE PUBBLICA NELLA CLASSE
 * E METTERE ESTERNAMENTE LA DEFINIZIONE DEI METODI DELLA CLASSE
 * 
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
 *      class Auto{
 *      public:
 *              void funzione();
 *      }
 *
 *      void Auto::funzione() {
 *      }
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
 *  //class Stud EXTENDS Persona
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
 * 
 *	string Data::StampaNome(){ print nome...} qui il metodo ritorna string non dimenticarlo
 *  //-> così ti sta dicendo che AL DI FUORI della classe data stiamo definendo il metodo 'StampaNome' che ritorna string
 *
 *	int mese() {return mm}; //metodo inline(tutto su una riga) utile da tenere nella classe 
 *  (che è messa in file .h come le struct)
 *
 *
 *
 *
 * //std::cout == using namespace; cout<<
 SOLO LO USING DEFINISCE CHE QUELLE FUNZIONI NON HANNO BISOGNO DI 'STD::'
 using std::cout; // program uses cout
 using std::cin; // program uses cin
 using std::endl; // program uses endl”
 */


#include<iostream>

using namespace std;
void swap(int &x, int &y);

class Person{
public:
    int age;
    string name;

    void func(){
        cout<<"executed function";
    }
};


int main(int argc, char *argv[]){

    std::cout<<"Programma di ripetizione"<<endl;
    int var1,var2;
    std::cout<<"inserisci var1 e 2\n";
    std::cin>>var1;
    std::cin>>var2;

    std::cout<<"hai inserito"<<var1<<"e"<<var2<<std::endl;

    swap(var1,var2);

    std::cout<<"hai swappato"<<var1<<"e"<<var2<<std::endl;

    return 0;
}

void swap( int &x, int &y){
    int temp = x;
    x = y;
    y = temp;
}