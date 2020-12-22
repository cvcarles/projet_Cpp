#include<iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <fstream>
#include "FileChainee.hpp"
#include "File.cpp"
#include "Guichet.hpp"
#include "Poste.hpp"



using namespace std;

int main(){

    FileChainee<int> f1;

    Guichet<int> guichet1;
    guichet1.setTemps(1000);

    f1.enfiler(2);
    f1.enfiler(3);
    f1.afficher();
    
/*if (f1->estVide()){
            std::cout<<"[ "<<"]"<<endl;
        }

si on empile, afficher [ ] <---- 1 
on enchaine direct avec afficher [|1|] reste de la pile 
on dépile              [ ] -----> 1


        
        */



}





