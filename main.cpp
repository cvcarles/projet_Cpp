#include<iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <fstream>
#include "FileChainee.hpp"



using namespace std;
void afficher(File<int> f){
    cout<<"file: ";
    while (!f.estVide()){
        cout<<f.premier()<<",";
            f.defiler();
        }
    cout<<endl;
}

int main(){
   // int i=1;
    FileChainee<int> f1;
    //f1.enfiler(i);
    //cout<<f1.estVide()<<endl;
    f1.enfiler(2);
    //cout<<f1.estVide()<<endl;

    //cout<<f1.estVide()<<endl;
    //cout<<f1.premier()<<endl;
    f1.enfiler(3);
    //cout<<f1.premier()<<endl;
    //f1.defiler();
    //cout<<f1.premier()<<endl;
   // f1.defiler();
    //cout<<f1.estVide()<<endl;
    FileChainee<int> f2=f1;
    afficher(f2);
    f2.defiler();
    afficher(f2);

    

    

    cout<<f1<<endl;






}





