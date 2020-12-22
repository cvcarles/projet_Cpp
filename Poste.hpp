#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "FileChainee.hpp"

template <typename T>
class Poste{
    private:
        int tempsOuverture;              // temps d'ouverture de la poste
        int nombreGuichet;                // nombre de guichet dans la poste        

    public:

    //constructeur
    Poste(): tempsOuverture(0), nombreGuichet(0){}//file(nullptr){}////////////////////
    ~Poste(){};
    
     // accesseur
    int getTimeG() const{
        return this->tempsGuichet;
    }
    int getNbrG() const{
        return this->tempsGuichet;
    }

    //mutateur
    void setTempsG (const int x){
        this->tempsGuichet=x;
    }
    void setNbrG (const int n){
        this->nombreGuichet=n;
    }


};