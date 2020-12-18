#pragma once
#include <iostream>
#include <cassert>
#include <fstream>
#include "File.hpp"



template<typename T>

class FileChainee: public File<T> {
    private:
        //int max;        //nombre maximum de personne dans la file
        Client<T> *dernier; // pointe sur le dernier client
        Client<T> *premier;

    public:
    //constructeur
    FileChainee(): dernier(nullptr),premier(nullptr){}////////////////////


    // dupliquer
    Client<T> *dupliquer(const Client<T> *clt){
        if (clt==nullptr) return nullptr;
        Client<T> *p=dupliquer(clt->getSuivant());
        return new Client<T>(clt->getClient(),p);
    }

    //constructeur de copie
    FileChainee(const FileChainee<T> &p) {
        this->premier = dupliquer(p.premier);
        //this->dernier = this->premier;
        //while (this->last->getSuivant() != nullptr) this->last = this->last->getSuivant();
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
            this->premier = p;
            this->dernier = p;
            }
        else {
            this->dernier->setSuivant(p);
            this->dernier = this->dernier->getSuivant();
            }
    }

    virtual void defiler () override {
        assert(!this->estVide());               // on vérifie que la file n'est pas vide

        Client<T> *p= this->premier;
        this->premier=(this->premier)->getSuivant();
        delete p;
    }

    virtual const T &premier() const override{
        assert(!this->estVide());                   // on vérifie que la file n'est pas vide
        return (this->premier)->getClient();
    }

};