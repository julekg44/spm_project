//TEMPLATE IN C (GENERICS)

/*

classi funzioni parametriche.

utilizzato con le classi

classe<tipo,tipo> nomeVarDelTipoDellaClasse


'template <typename T, int MAX>
class elenco_ordinato'

ovvero per la classe che segue vale QUESTO MODELLO
(il template), pertanto quando dichiareremo un oggetto
di tipo 'elenco_ordinato' necessariamente ci vorranno 
i tipi T e MAX.
Cio' ci permette di avere la stesa classe per diverse versioni/tipi

TYPENAME T definisce il tipo generico 'T' da usare nella
classe 

un T generics può essere usato a sua volta come tipo
in un'altra classe che definisce un generics T2

(The C programming language provides a keyword called typedef, which 
you can use to give a type a new name. 
Following is an example to define a term BYTE 
for one-byte numbers −> typedef unsigned char BYTE;)


----FUNZIONI TEMPLATE(GENERICS)
	
	template<typename T>
	void sort(T v[], int num_ele){
		for(int=0; i<num_ele-1; i++){
			for(int j=i+1; j<num_ele;j++){
				if (v[j]<v[i]){
				swap(v[i],v[j]);
				}
			}
		}
	
	}

(per fare l'equals qua si devono ridefinire gli operatori)


-> costruttore vuoto Costruttore(){}

-----------------FUNZIONI LAMBDA(CLOSURE)
USANO I PUNTATORI A FUNZIONE


le parentesi quadre indicano una funzione lambda, ovvero definiamo
la funzione direttamente dopo le parentesi
//SENZA CLOSURE
r.cerca_indirizzo( [] (string indirizzo)
					{return indirizzo.find("Monti") != string::npos;}); 


//CON CLOSURE (la closure permette di passare var esterne all'interno
dell'ambiente/scope della lambda)

metti nella quadra & e dopo nella tonda (string& cognome..) sulle var locali,
con la [&] possiamo usare le nostre var esterne nella lambda

string cognome_cercato = "Rossi";
r.cerca_indirizzo( [&] (string& nome)
					{return cognome.find(cognome_cercato) != string::npos;}); 


[&] usa le variabili esterne per RIFERIMENTO(OVVERO INDIRIZZO)
[=] usa le variabili esterne ottenendole tramite passaggio per copia(non potremo modificarle
quindi tramite la lambda)

[=,&n] SCHEMA MISTO, tutto per copia tranne 'n' che è passato
per riferimento(indirizzo)

[n] solo il nome della var intende passaggio per copia

caso in cui siamo in un metodo di una classe
e vogliamo passare alla lambda il this(le var di classe)
[this]
*/