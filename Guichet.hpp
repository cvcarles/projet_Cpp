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

    //constructeur
    Guichet(): tempsGuichet(10000){}//, file(<T>){}//file(nullptr){}////////////////////
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

};

