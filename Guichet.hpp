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
        FileChainee<T>* file;           // file correspondant au guichet
        
        

    public:
    bool libre;

    //constructeur
    Guichet(FileChainee<T> *f=nullptr, bool l=1): file(f), libre(l){}//file(nullptr){}////////////////////
    ~Guichet(){};
    
     // accesseur
    int getTemps() const{
        return this->tempsGuichet;
    }

    File<T> *getFile() const{
        return this->file;
    }


    //mutateur
    void setTemps(const int t){
        this->tempsGuichet=t;
    }

    void setSuivant(File<T> *f){
        this->file=f;
    }



    void traitementClient(Client <T> client){
        (this->file)->afficher();

        this->libre=0;

        int t0=time(NULL);
        while(time(NULL)-t0< client.tempsGuichet){ }
        
        (this->file)->defiler();
        this->libre=1;
        (this->file)->afficher();
    }
};

/*client arrive
    marque le temps début
    tant que temps courant -tempps début < tempsGuichet
        {
        }
    défile client 
    guichet libre*/
