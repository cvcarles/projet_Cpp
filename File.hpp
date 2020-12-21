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

// dupliquer
    Client<T> *dupliquer(const Client<T> *clt){
        if (clt==nullptr) return nullptr;
        Client<T> *p=dupliquer(clt->getSuivant());
        return new Client<T>(clt->getClient(),p);
    }

    //constructeur de copie
    File(const File<T> &f) {
        this->cpremier = dupliquer(f.cpremier);
        this->cdernier = this->cpremier;
        while (this->cdernier->getSuivant() != nullptr) this->cdernier = this->cdernier->getSuivant();
    }

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

        Client<T> *p= this->cpremier;
        this->cpremier=this->cpremier->getSuivant();
        delete p;
            
    }

    virtual const T &premier() const {
        assert(!this->estVide());                   // on vérifie que la file n'est pas vide
        return (this->cpremier)->getClient();
    }

    const std::string toString() const {
        const File<T>* temp=this;
        std::ostringstream s;
        s<<"file: "<<temp->cpremier->getClient()<<" ";

        while (temp->cpremier!=nullptr){
            s<<"file: "<<temp->cpremier->getClient()<<" ";
            Client<T> c=(temp->cpremier->getSuivant());
            temp->cpremier->setClient(c);
        }
        return s.str();
    }

    friend std::ostream &operator << (std::ostream &f, const File<T> &F){
        return f<<F.toString();
    }
    
};