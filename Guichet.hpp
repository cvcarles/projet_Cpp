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
    bool libre;

    //constructeur
    Guichet(FileChainee<T> f, bool l=1): file(f), libre(l){}
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

/*client arrive
    marque le temps début
    tant que temps courant -tempps début < tempsGuichet
        {
        }
    défile client 
    guichet libre*/

    void traitementClient(FileChainee<T> &filee, bool libre){
        libre=0; 
        int t0=time(NULL);   
        while(time(NULL)-t0 < (filee.cpremier->tempsGuichet)){ }
        filee.afficherFin();
        filee.defiler();
        libre=1; 
    }
};


