#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

//https://www.youtube.com/watch?v=I4ALm-NOMfU&list=PL0qAPtx8YtJcdF_posHZldxX9IaY5wfPm&index=1
//IL TEMPLATE COL TYPENAME VA SEMPRE PRIMA DELLA FUNZIONE CHE LO UTILIZZA
template <typename T>
void stampa(vector<T> vettore){

    std::cout<<"============"<<endl;
    for(T elem: vettore){ //un for each in pratica
        std::cout<<elem<<endl;
    }
    std::cout<<"============"<<endl;
}

int main(){


    vector<int> vettore;
    vector<int> vector;

    //il vector è dinamico, si rialloca dinamicamente
    //puoi vederlo come una lista

    for(int i=0;i<10;i++){
        vettore.push_back(i);
        vector.push_back(i);
        cout<<"size="<<vettore.size()<<endl;
        cout<<"capacità="<<vettore.capacity()<<endl;
        cout<<endl;
    }


    //iteratore:
    auto iteratore = vector.begin();  //piazza l'iteratore all'inizio
    cout<<"Utilizzo iteratore"<<endl;
    for(auto it=vector.begin(); it!=vector.end(); it++){
        cout<<"elemento del vettore stamapato:"<<*it<<endl;
        it++;
    }



    //usiamo i template coi vector
    //vedi riga 6


    std::vector<string> persone {"geppetto","pinocchio","tarzan"};
    stampa(persone);

    persone.insert(persone.begin(),"Topolino");
    std::cout<<"Stai per eliminare: "<<*(persone.begin()+2)<<endl;
    persone.erase(persone.begin()+2);
    stampa(persone);


    //LIBRERIA ALGORITHM
    //vedi riga 4

    return 0;
}



