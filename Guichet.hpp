#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "FileChainee.hpp"

template <typename T>
class Guichet{
    private:
        int tempsGuichet;              // temps au guichet 
        //Client<T>* clientActuel;                   // client actuellement au guichet
        
        
        

    public:
    FileChainee<T> file;           // file correspondant au guichet
    bool libreT;
 //----------------------Bases de la classe Guichet---------------------------------   

    //constructeur
    //Guichet(): file(0), libreT(1){}

    Guichet(FileChainee<T> f, bool l=1): file(f), libreT(l){};
    Guichet(): tempsGuichet(0),file(), libreT(1){};
    ~Guichet(){};
    
     // accesseur
    int getTemps() const{
        return this->tempsGuichet;
    }

    FileChainee<T> getFile() const{
        return this->file;
    }


    //mutateur
    void setTemps(const int t){
        this->tempsGuichet=t;
    }

    void setFile(FileChainee<T>* f){
        this->file=f;
    }

    bool estLibreT() const{
        return this->libreT;
    }
/*client arrive
    marque le temps début
    tant que temps courant -tempps début < tempsGuichet
        {
        }
    défile client 
    guichet libre*/

    /*void traitementClient(FileChainee<T> &filee,int *compte,int *t, int *libre){
        //int t0=time(NULL);   
        if (!filee.estVide()){
            //Client<T> *p= new Client<T>(*compte);
            //filee.cpremier=p;
            *libre=*t+(filee.cpremier)->tempsGuichet;
            filee.afficherFin();
            filee.defiler();

                }*/
        //while(time(NULL)-t0 < *(filee.cpremier)->tempsGuichet)){ }
    
};


