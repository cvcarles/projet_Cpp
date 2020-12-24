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



    void traitementClient(FileChainee<T> &filee, bool libre){
        libre=0; 
        //int t0=time(NULL);   
        //filee.afficherAttente();  
        //while(time(NULL)-t0 < (filee.cpremier->tempsGuichet)){ }
        //filee.defiler();
        libre=1; 
        filee.afficherDefiler();
    }
};

/*client arrive
    marque le temps début
    tant que temps courant -tempps début < tempsGuichet
        {
        }
    défile client 
    guichet libre*/
