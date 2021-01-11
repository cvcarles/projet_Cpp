#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "FileChainee.hpp"

template <typename T>
class Guichet{
    private:   
        FileChainee<T> file;               // file correspondant au guichet
        int libre;                         // le temps à partir duquel le guichet est libre

 //----------------------Bases de la classe Guichet---------------------------------   

    public:
    //constructeurs
        Guichet(FileChainee<T> f, int l=1): file(f), libre(l){};
        Guichet(): file(), libre(1){};

    //destructeur
        ~Guichet(){};
    
    // accesseurs
        int getLibre() const{
            return this->libre;
        }

        FileChainee<T> getFile() const{
            return this->file;
        }

    //mutateurs
        void setLibre(const int l){
            this->libre=l;
        }

        void setFile(FileChainee<T>* f){
            this->file=f;
        }
    
};


