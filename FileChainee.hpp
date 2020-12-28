#pragma once
#include <iostream>
#include <cassert>
#include <fstream>
#include "File.hpp"



template<typename T>

class FileChainee: public File<T> {
    
//----------------------Bases de la classe FileChainee---------------------------------   
    public:
    //constructeurs
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

    /* 
     * Rôle: dupliquer un client               
     */ 
    Client<T> *dupliquer(const Client<T> *c){
        if(c==nullptr){
            return nullptr;
        }
        Client<T> *p=dupliquer(c->getSuivant());
        return new Client<T> (c->getClient(),p);
    }
    
    
    /* 
     * Rôle: Les 5 primitives de la manipulation de files                 
     */

        virtual bool estVide() const override{
            return this->cpremier==nullptr;
        }

        virtual void enfiler (const T &clt, int t=0){
            Client<T> *p= new Client<T>(clt);                       // on créé un nouveau client à enfiler avec la valeur passée en paramètre
            p->setHeure(t);                                         // on assimile au client enfilé l'heure à laquelle il rentre dans la file d'attente
        if (this->estVide()){
                this->cpremier = p;
                this->cdernier = p;
            }

            else {
                this->cdernier->setSuivant(p);
                this->cdernier = p;
            }
        }

        virtual void defiler () override {
            assert(!this->estVide());                               // on vérifie que la file n'est pas vide

            Client<T> *p= this->cpremier;
            this->cpremier=(this->cpremier)->getSuivant();
            delete p;
        }


        virtual const T &premier() const override{
            assert(!this->estVide());                               // on vérifie que la file n'est pas vide
            return (this->cpremier)->getClient();
        }

    /* 
     * Rôle: retourne la longueur d'une file             
     */
    int longueur(){
        int t=0;
        FileChainee<T> *f1= new FileChainee<T>(*(this));    
        while(!f1->estVide()){                                  // tant que la copie de la file n'est pas vide
            f1->defiler();                                      // on défile la copie et on incrémente le compteur 
            t++;                                                
        }
    return t;
    }

    /* 
     * Rôle: affiche la file d'attente courante                 // utilisée seulement pour les tests     
     */
     void afficherAttente(){
        FileChainee<T> *f1= new FileChainee<T>(*(this));        // on duplique la file courante pour ne modifier que la temporaire

        std::cout<<"Guichet: [ ";
        while (!f1->estVide()){
            std::cout<<f1->premier()<<" ";
                f1->defiler();
        }

        std::cout<<"]"<<std::endl;
        std::cout<<std::endl;
    }


    /* 
     * Rôle: affiche la file d'attente courante lorsque qu'un client est enfilé au guichet dont le numéro est passé en paramètres                 
     */
    void afficherEnfiler(int numero){
        FileChainee<T> *f1= new FileChainee<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire
        std::cout<<"Guichet "<<numero<<": [ ";
            while (f1->premier()!=this->dernier()){
            std::cout<<f1->premier()<<" ";
                f1->defiler();
            } 

        std::cout<<"] <-------"<< *(this->cdernier);
        std::cout<<std::endl;
        std::cout<<std::endl;
    }


    /* 
     * Rôle: affiche la file d'attente courante lorsque qu'un client est défilé au guichet     
     *       prend en parmètre le numero de guichet, le chiffre du client défilé et si on défile 
     *          à cause d'un client impatient ( true ) ou parce qu'il a été servi ( false )           
     */
    void afficherDefiler(int numero,T clientDefile,bool impatient){
        FileChainee<T> *f1= new FileChainee<T>(*(this));              // on duplique la file courante pour ne modifier que la temporaire
        std::cout<<"Guichet "<<numero<<": [ ";
        if (!impatient){
            f1->defiler();
        }

        while (!f1->estVide()){        
            std::cout<<f1->premier()<<" ";
            f1->defiler();
        }
        std::cout<<"] -------> "<< clientDefile<<std::endl;
        std::cout<<std::endl;
    }


    /* 
     * Rôle: affiche la file d'attente courante avec le client servi au guichet dont le numéro est passé en paramètres         
     */
    void afficherFin(int numero){
        FileChainee<T> *f1= new FileChainee<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire
        std::cout<<"Guichet "<<numero<<": [ |";
        std::cout<<f1->premier()<<"| ";
        f1->defiler();

        while (!f1->estVide()){  
            std::cout<<f1->premier()<<" ";
            f1->defiler();
        }
        std::cout<<"]"<<std::endl;
        std::cout<<std::endl;
        this->afficherDefiler(numero,this->cpremier->getClient(),false);          // après avoir été servi, le client est défilé, on appelle donc la fonction corespondante pour afficher défilé
    }



    /* 
     * Rôle: défile le client impatient au numéro de guichet, tous deux passés en paramètre   
     *       et retourne la file actualisée sans le client impatient      
     */
    FileChainee<T> defilerImpatient(Client<T> *impatient, int numero){
        FileChainee<T> *copie= new FileChainee<T>(*(this));                         // on duplique la file courante pour ne modifier que la temporaire
        FileChainee<T> nouvelle=FileChainee<T>();                                   // on créé une nouvelle file 

        while (!copie->estVide()){
            if(copie->premier()!=impatient->getClient()){                           // on copie la file courante en sautant le client impatient 
                nouvelle.enfiler(copie->premier());
            }
            copie->defiler();
        }
        nouvelle.afficherDefiler(numero,impatient->getClient(),true);
        return nouvelle;
    }
};