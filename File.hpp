#pragma once
#include <iostream>
#include <cassert>
#include <fstream>
#include "Client.hpp"


template<typename T>

class File {
    public:
    // destructeur
    ~File(){}

    //methode de base de manipulation de la file

    virtual bool estVide() const{
        return this->dernier==nullptr;
    }

    virtual void enfiler (const T &x){
        Client<T> *p= new Client<T>(x, this->dernier);
        this->dernier=p;
    }

    virtual void defiler (){
        assert(!this->estVide());               // on vérifie que la file n'est pas vide

        Client<T> *p= this->dernier;
        this->dernier=this->dernier->getSuivant();
            
    }

    virtual const T &premier() const {
        assert(!this->estVide());                   // on vérifie que la file n'est pas vide
        return (this->dernier)->getClient();
    }
};