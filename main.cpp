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
    
    Poste<int> poste(8,1);
    //Client<int> c0(1);
    Client<int> c1(1);
    


    FileChainee<int> f1;
    //cout<<c1.getTemps()<<endl;
  //  f1.setPremier(c1);
    Guichet<int> guichet1(f1);

    //f1->enfiler(1);
    //guichet1.setFile(f1);
    //poste.setTempsP((8*60));
     
   //guichet1.traitementClient(f1);

     
    int compte=4;
    //f1.enfiler(1);
    f1.enfiler(2);

    f1.enfiler(3);
 

    poste.algoPrincipal(f1,guichet1,&compte);

     

    return EXIT_SUCCESS;

    }







    
/*if (f1->estVide()){
            std::cout<<"[ "<<"]"<<endl;
        }

si on empile, afficher [ ] <---- 1 
on enchaine direct avec afficher [|1|] reste de la pile 
on dépile              [ ] -----> 1


        
        */







