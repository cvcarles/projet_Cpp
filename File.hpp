#pragma once
#include <iostream>
#include <cassert>
#include <fstream>
#include "Client.hpp"


template<typename T>

class File {
    protected:
        Client<T> *cdernier; // pointe sur le dernier client
        Client<T> *cpremier;

    public:

    File(): cdernier(nullptr),cpremier(nullptr){}////////////////////

    // destructeur
    ~File(){}

    //methode de base de manipulation de la file

    virtual bool estVide() const{
        return this->cpremier==nullptr;
    }

    virtual void enfiler (const T &clt){
        Client<T> *p= new Client<T>(clt, this->cdernier);
        this->cdernier=p;
    }

    virtual void defiler (){
        assert(!this->estVide());               // on vérifie que la file n'est pas vide

        Client<T> *p= this->cdernier;
        this->cdernier=this->cdernier->getSuivant();
        delete p;
            
    }

    virtual const T &premier() const {
        assert(!this->estVide());                   // on vérifie que la file n'est pas vide
        return (this->cpremier)->getClient();
    }

    const std::string toString() const {
        std::ostringstream s;
        s<<this->cpremier<<"dernier"<<this->cdernier;
        return s.str();
    }

    friend std::ostream &operator << (std::ostream &f, const File<T> &F){
        return f<<F.toString();
    }
    
};