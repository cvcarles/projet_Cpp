#pragma once
#include <iostream>
#include <cassert>
#include <fstream>
#include "Client.hpp"


template<typename T>

class File {
    public:
        Client<T> *cdernier; // pointe sur le dernier client
        Client<T> *cpremier;

 //----------------------Bases de la classe File---------------------------------   

    public:
    //constructeur
        File(): cdernier(nullptr),cpremier(nullptr){}

    // destructeur
       virtual ~File(){}

//----------------------Méthodes de base de manipulation de la classe File--------------------------------- 
    /* 
     * Rôle: Les 5 primitives de la manipulation de files                 
     */
    virtual bool estVide() const=0;
    virtual void defiler()=0;
    virtual const T &premier() const=0;
    virtual const T &dernier() const=0;

    virtual void enfiler (const T &clt){
         Client<T> *p= new Client<T>(clt);
       if (this->estVide()){
            this->cpremier = p;
            this->cdernier = p;
            }
        else {
            this->cdernier->setSuivant(p);
            this->cdernier = p;
            }

    }
    
};