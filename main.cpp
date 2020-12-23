#include<iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <fstream>
#include <time.h>
#include <random>
#include "FileChainee.hpp"
#include "File.cpp"
#include "Guichet.hpp"
#include "Poste.hpp"



using namespace std;

int main(){
    Poste<int> poste;
    FileChainee<int>* f1;
    //cout<<c1.getTemps()<<endl;
    Guichet<int> guichet1(f1);
    Client<int> c1(1);



    poste.setTempsP((8*60));



    for (int t=1; t<poste.getTempsP(); t++){
       // srand(time(0));
        double p=poste.probabilite();
        cout<<p<<endl;
        if (p<=0.83){
            cout<<"ifproba"<<endl;
            //f1->enfiler(1);
        }
        if(guichet1.libre){
            cout<<"taritement";
            guichet1.traitementClient(f1->premier());
        }   

    }







    
/*if (f1->estVide()){
            std::cout<<"[ "<<"]"<<endl;
        }

si on empile, afficher [ ] <---- 1 
on enchaine direct avec afficher [|1|] reste de la pile 
on dépile              [ ] -----> 1


        
        */



}





