#pragma once
#include <iostream>
#include <cassert>
#include <fstream>
#include "File.hpp"



template<typename T>

class FileChainee: public File<T> {
    private:
        //int max;        //nombre maximum de personne dans la file
        //Client<T> *cdernier; // pointe sur le dernier client
        //Client<T> *cpremier;

    public:
    //constructeur
    //FileChainee();////////////////////
    FileChainee():File<T>::File(){};

    FileChainee(const FileChainee<T>* &f) {
        this->cpremier = dupliquer(f.cpremier);
        this->cdernier = this->cdernier;
        while (this->cdernier->getSuivant() != nullptr) this->cdernier = this->cdernier->getSuivant();
    }
    
    
    // destructeur
    ~FileChainee(){}

    //methode de base de manipulation de la pile



    virtual bool estVide() const override{
        return this->cpremier==nullptr;
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

    FileChainee<T>* &operator = (const FileChainee<T>* &file){
        return this->cpremier=dupliquer(file->cpremier);}

    void afficher(){
        FileChainee<T>* f1= this;
        std::cout<<"file: ";
        while (!f1->estVide()){
            std::cout<<f1->premier()<<",";
                f1->defiler();
            }
        std::cout<<std::endl;
    }
};