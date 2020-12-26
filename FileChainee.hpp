#pragma once
#include <iostream>
#include <cassert>
#include <fstream>
#include "File.hpp"



template<typename T>

class FileChainee: public File<T> {
    public:
    //constructeur
    FileChainee():File<T>::File(){};

    FileChainee(const FileChainee<T> &f) {
        this->cpremier = dupliquer(f.cpremier);
        this->cdernier = this->cdernier;
        while (this->cdernier != nullptr) {
            this->cdernier = this->cdernier->getSuivant();
         }
    }
    
    // destructeur
    ~FileChainee(){}

    Client<T> *dupliquer(const Client<T> *c){
        if(c==nullptr){
            return nullptr;
        }
        Client<T> *p=dupliquer(c->getSuivant());
        return new Client<T> (c->getClient(),p);
    }

    //methode de base de manipulation de la pile

    virtual bool estVide() const override{
        return this->cpremier==nullptr;
    }

    virtual void enfiler (const T &clt) override{
        Client<T> *p= new Client<T>(clt);
       if (this->estVide()){
                     // std::cout<<"enfiler est vide"<<std::endl;

            this->cpremier = p;
            this->cdernier = p;
            }
        else {
                                   //std::cout<<" enfiler est pas vide"<<std::endl;

            this->cdernier->setSuivant(p);
            this->cdernier = p;
            }

    }

    virtual void defiler () override {
        assert(!this->estVide());               // on vérifie que la file n'est pas vide

       Client<T> *p= this->cpremier;
        this->cpremier=(this->cpremier)->getSuivant();
        delete p;
    }
    /*virtual void defiler() override {
        assert(!this->estVide());

		Client<T> *p = this->cpremier;
    
        if (!f1.estVide()){
            this->cpremier = nullptr;
            this->cdernier = nullptr;
           // std::cout<<"defiler vide"<<std::endl;
        }
        else
        {
            this->cpremier = (this->cpremier)->getSuivant();
                        //std::cout<<"defiler pas vide"<<std::endl;

        }
        delete p;       
	}*/


    virtual const T &premier() const override{
        assert(!this->estVide());                   // on vérifie que la file n'est pas vide
        return (this->cpremier)->getClient();
    }


    int longueur(){
        int t=1;
        FileChainee<T> *f1= new FileChainee<T>(*(this));    
        while(!f1->estVide()){
            f1->defiler();
            t++;
        }
    return t;
    }
    // afficher la file courante
     void afficherAttente(){
        FileChainee<T> *f1= new FileChainee<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire

        std::cout<<"Guichet: [ ";
        while (!f1->estVide()){
            std::cout<<f1->premier()<<" ";
                f1->defiler();
            }
        std::cout<<"]";
        std::cout<<std::endl;
        std::cout<<std::endl;

        
    }

    void afficherEnfiler(){
        FileChainee<T> *f1= new FileChainee<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire
        std::cout<<"Guichet: [ ";
            while (f1->premier()!=this->dernier()){
            std::cout<<f1->premier()<<" ";
                f1->defiler();
            } 

        std::cout<<"] <-------"<< *(this->cdernier);
        std::cout<<std::endl;
        std::cout<<std::endl;

    }

    void afficherDefiler(){
        FileChainee<T> *f1= new FileChainee<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire
        std::cout<<"Guichet: [ ";
        T p=f1->premier();

            f1->defiler();
            //this->defiler();
            while (!f1->estVide()){
                
            std::cout<<f1->premier()<<" ";
                f1->defiler();
            }
        std::cout<<"] -------> "<< p;
        std::cout<<std::endl;
        std::cout<<std::endl;

    }

    void afficherFin(){
        FileChainee<T> *f1= new FileChainee<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire
        std::cout<<"Guichet: [ |";
            std::cout<<f1->premier()<<"| ";
            f1->defiler();
            while (!f1->estVide()){
                
            std::cout<<f1->premier()<<" ";
                f1->defiler();
            }
        std::cout<<"]"<<std::endl;
        std::cout<<std::endl;
        this->afficherDefiler();

    }
};