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
        File(): cdernier(nullptr),cpremier(nullptr){}////////////////////

    // destructeur
        ~File(){}

//----------------------Méthodes de base de manipulation de la classe File--------------------------------- 
    /* 
     * Rôle: surcharger l'opérateur d'affectation                  
     */ 
    File<T>* &operator = (File<T>* const &file){
        return this->cpremier=dupliquer(file->cpremier);
    }



    /* 
     * Rôle: Les 5 primitives de la manipulation de files                 
     */
    virtual bool estVide() const{
        return this->cpremier==nullptr;
    }

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

    virtual void defiler() {
         assert(!this->estVide());               // on vérifie que la file n'est pas vide

       Client<T> *p= this->cpremier;
        this->cpremier=(this->cpremier)->getSuivant();
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




    /* 
     * Rôle: surcharge d'opérateur utile pour les tests d'affichage                
     */

        const std::string toString() const {
            const File<T>* temp=this;
            std::ostringstream s;
            s<<temp->cpremier->getClient()<<" ";
            return s.str();
        }

        friend std::ostream &operator << (std::ostream &f, const File<T> &F){
            return f<<F.toString();
        }
    
};