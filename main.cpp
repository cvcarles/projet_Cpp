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
#define TEMPOUVERTURE 10
#define NOMBREGUICHET 2


using namespace std;

int main(){
    
    Poste<int> poste(TEMPOUVERTURE,NOMBREGUICHET);
         
   int compte=1;

  

    //poste.algoPrincipal(&compte); 
    FileChainee<int> f1;
    
    Guichet<int> guichet1(f1);

    f1.enfiler(1); 
    f1.enfiler(2);
    f1.enfiler(3);
    f1.enfiler(4); 
    f1.enfiler(5);
    f1.enfiler(6);
    f1.enfiler(7); 
    f1.enfiler(8);
    f1.enfiler(9);
 
   //(f1.defilerImpatient(4)).afficherAttente(); 

    poste.algoPrincipal(&compte);
    return EXIT_SUCCESS; 

    }







    
/*if (f1->estVide()){
            std::cout<<"[ "<<"]"<<endl;
        }

si on empile, afficher [ ] <---- 1 
on enchaine direct avec afficher [|1|] reste de la pile 
on dépile              [ ] -----> 1


        
        */







