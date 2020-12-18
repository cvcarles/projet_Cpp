#pragma once
#include <iostream>
#include <cassert>
#include <fstream>
#include "File.hpp"



template<typename T>

class FileChainee: public File<T> {
    private:
        //int max;        //nombre maximum de personne dans la file
        Client<T> *cdernier; // pointe sur le dernier client
        Client<T> *cpremier;

    public:
    //constructeur
    FileChainee(): cdernier(nullptr),cpremier(nullptr){}////////////////////

    // dupliquer
    Client<T> *dupliquer(const Client<T> *clt){
        if (clt==nullptr) return nullptr;
        Client<T> *p=dupliquer(clt->getSuivant());
        return new Client<T>(clt->getClient(),p);
    }

    //constructeur de copie
    FileChainee(const FileChainee<T> &p) {
        this->cpremier = dupliquer(p.cpremier);
        this->cdernier = this->cpremier;
        while (this->last->getSuivant() != nullptr) this->last = this->last->getSuivant();
    }
    
    // destructeur
    ~FileChainee(){
        delete [] this ->lesClients;
    }

    //methode de base de manipulation de la pile



    virtual bool estVide() const override{
        return this->dernier==nullptr;
    }

    virtual void enfiler (const T &clt) override{
        Client<T> *p= new Client<T>(clt);
        if (this->estVide()){
            this->cpremier = p;
            this->cdernier = p;
            }
        else {
            this->cdernier->setSuivant(p);
            this->cdernier = this->cdernier->getSuivant();
            }
    }

    virtual void defiler () override {
        assert(!this->estVide());               // on vérifie que la file n'est pas vide

        Client<T> *p= this->cpremier;
        this->cpremier=(this->cpremier)->getSuivant();
        delete p;
    }

    virtual const T &premier() const override{
        assert(!this->estVide());                   // on vérifie que la file n'est pas vide
        return (this->cpremier)->getClient();
    }

};