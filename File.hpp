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

    public:

    File(): cdernier(nullptr),cpremier(nullptr){}////////////////////

    // destructeur
    ~File(){}

    // dupliquer
    Client<T> *dupliquer(const Client<T> *clt);

    //constructeur de copie
    File<T> (File<T> const &f) {
        this->cpremier = dupliquer(f.cpremier);
        this->cdernier = this->cpremier;
        //while (this->cdernier->getSuivant() != nullptr) {
        //    this->cdernier = this->cdernier->getSuivant();
        //}
}

    // surcharge de l'opérateur = 
    File<T>* &operator = (File<T>* const &file){
        return this->cpremier=dupliquer(file->cpremier);
    }




    //methodes de base de manipulation de la file

    virtual bool estVide() const{
        return this->cpremier==nullptr;
    }

    virtual void enfiler (const T &clt){
         Client<T> *p= new Client<T>(clt);
       if (this->estVide()){
            this->cpremier = p;
            this->cdernier = this->cpremier;
            }
        else {
            this->cdernier->setSuivant(p);
            this->cdernier = this->cdernier->getSuivant();
            }

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

    virtual const T &dernier() const {
        assert(!this->estVide());                   // on vérifie que la file n'est pas vide
        return (this->cdernier)->getClient();
    }

    const std::string toString() const {
        
        const File<T>* temp=this;
        std::ostringstream s;
        s<<temp->cpremier->getClient()<<" ";
        return s.str();
    }


    // afficher la file courante
   /* void afficherAttente(){
        File<T> *f1= new File<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire

        std::cout<<"Guichet: [ ";
        while (!f1->estVide()){
            std::cout<<f1->premier()<<" ";
                f1->defiler();
            }
        std::cout<<"]";
        std::cout<<std::endl;
        std::cout<<std::endl;

        
    }*/

    void afficherEnfiler(){
        File<T> *f1= new File<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire
        //T p=f1->dernier();
        std::cout<<"Guichet: [ ";

            while (!f1->estVide()){
            std::cout<<f1->premier()<<" ";
                f1->defiler();
            } 

        std::cout<<"] <-------"<< 'b';
        std::cout<<std::endl;
        std::cout<<std::endl;

    }

    void afficherDefiler(T p){
        File<T> *f1= new File<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire

        std::cout<<"Guichet: [ ";
            f1->defiler();
            this->defiler();
            while (!f1->estVide()){
                
            std::cout<<f1->premier()<<" ";
                f1->defiler();
            }
        std::cout<<"] -------> "<< p;
        std::cout<<std::endl;
        std::cout<<std::endl;

    }

    void afficherFin(){
        File<T> *f1= new File<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire
        T p=f1->premier();
        std::cout<<"Guichet: [ |";
            std::cout<<f1->premier()<<"| ";
            f1->defiler();
            while (!f1->estVide()){
                
            std::cout<<f1->premier()<<" ";
                f1->defiler();
            }
        std::cout<<"]"<<std::endl;
        std::cout<<std::endl;
        this->afficherDefiler(p);

    }



    //surcharge de l'opérateur <<
    friend std::ostream &operator << (std::ostream &f, const File<T> &F){
        return f<<F.toString();
    }
    
};