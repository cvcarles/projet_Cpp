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
        return this->cdernier==nullptr;
    }

    virtual void enfiler (const T &x){
        Client<T> *p= new Client<T>(x, this->cdernier);
        this->cdernier=p;
    }

    virtual void defiler (){
        assert(!this->estVide());               // on vérifie que la file n'est pas vide

        Client<T> *p= this->cdernier;
        this->cdernier=this->cdernier->getSuivant();
            
    }

    virtual const T &premier() const {
        assert(!this->estVide());                   // on vérifie que la file n'est pas vide
        return (this->cdernier)->getClient();
    }
};