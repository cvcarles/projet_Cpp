#pragma once
#include <iostream>
#include <cassert>
#include <fstream>
#include "File.hpp"



template<typename T>

class FileChainee: public virtual File<T> {
    
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


//-----------------Méthodes de base de manipulation de la classe FileChainee--------------------------------- 

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
     * Rôle: surcharger l'opérateur d'affectation                  
     */ 
    File<T>* &operator = (File<T>* const &file){
        return this->cpremier=dupliquer(file->cpremier);
    }

    
    /* 
     * Rôle: Les 5 primitives de la manipulation de files                 
     */

        virtual bool estVide() const override{
            return this->cpremier==nullptr;
        }

        virtual void enfiler (const T &clt, int t){
            Client<T> *p= new Client<T>(clt);                       // on créé un nouveau client à enfiler avec la valeur passée en paramètre
            //std::cout<<t<<std::endl;
            p->setHeure(t);                                         // on assimile au client enfilé l'heure à laquelle il rentre dans la file d'attente
            //std::cout<<p->getTempsI()<<std::endl;
       
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

        virtual const T &dernier() const {
            assert(!this->estVide());                   // on vérifie que la file n'est pas vide
            return (this->cdernier)->getClient();
        }

//-----------------Méthodes de manipulation de la classe FileChainee--------------------------------- 

    /* 
     * Rôle: défile le client impatient au numéro de guichet, tous deux passés en paramètre   
     *       et retourne la file actualisée sans le client impatient      
     */
    FileChainee<T> defilerImpatient(Client<T> *impatient, int numero, int t, int &position){
        FileChainee<T> *copie= new FileChainee<T>(*(this));                         // on duplique la file courante pour ne modifier que la temporaire
        FileChainee<T> nouvelle=FileChainee<T>();                                   // on créé une nouvelle file 
        while (!copie->estVide()){
            if(copie->premier()!=impatient->getClient()){                           // on copie la file courante en sautant le client impatient 
                nouvelle.enfiler(copie->premier(),t);
            }
            copie->defiler();
        }
        nouvelle.afficherDefiler(numero,impatient->getClient(),true, position);
        return nouvelle;
    }

    /* 
     * Rôle: retourne la longueur d'une file             
     */
    int longueur(){
        int compteur=0;
        FileChainee<T> *f1= new FileChainee<T>(*(this));    
        while(!f1->estVide()){                                  // tant que la copie de la file n'est pas vide
            f1->defiler();                                      // on défile la copie et on incrémente le compteur 
            compteur++;                                                
        }
    return compteur;
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
    void afficherEnfiler(int numero,int *position){
        FileChainee<T> *f1= new FileChainee<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire
        int i=0;
        int j=0;
        int k=0;
            while (f1->premier()!=this->dernier()){
                
            mvprintw(numero, 13+j+i,"%d",f1->premier());
      
            if ((f1->premier()/10)<1){j=j+1;}
            else if((f1->premier()/10)<10){j=j+2;
                                           k=k+1;}
            else { j=j+3;
                    k=2+k;}
            mvprintw(numero, 13+i+j," ");

                f1->defiler();
                delay_output(500);
            i++;
            } 
        *position=13+2*i+k;
        mvprintw(numero, (*position),"]<-------                    ");
        mvprintw(numero, (22+2*i+k),"%d",(this->dernier()));
                                        refresh();

       
    }


    /* 
     * Rôle: affiche la file d'attente courante lorsque qu'un client est défilé au guichet     
     *       prend en parmètre le numero de guichet, le chiffre du client défilé et si on défile 
     *          à cause d'un client impatient ( true ) ou parce qu'il a été servi ( false )           
     */
    void afficherDefiler(int numero,T clientDefile,bool impatient, int &position){
        FileChainee<T> *f1= new FileChainee<T>(*(this));              // on duplique la file courante pour ne modifier que la temporaire
        if (!impatient){
            f1->defiler();
        }
        int i=0;
        int j=0;
        int k=0;
        while (!f1->estVide()){
            mvprintw(numero, 13+j+i,"%d",f1->premier());
            
            if ((f1->premier()/10)<1){j=j+1;}
            else if((f1->premier()/10)<10){j=j+2;
                                           k=k+1;}
            else { j=j+3;
                    k=2+k;}
            mvprintw(numero, 13+i+j," ");
                            delay_output(1000);

            i++;
                f1->defiler();
                    refresh();
} 
        mvprintw(numero, (13+2*i+k),"]------->               ");
        mvprintw(numero, (22+2*i+k),"%d",clientDefile);
                                            refresh();



    }


    /* 
     * Rôle: affiche la file d'attente courante avec le client servi au guichet dont le numéro est passé en paramètres         
     */
    void afficherFin(int numero, int &position){
        FileChainee<T> *f1= new FileChainee<T>(*(this));          // on duplique la file courante pour ne modifier que la temporaire
        mvprintw(numero, 13,"|");

        mvprintw(numero, 13+1,"%d",f1->premier());

        mvprintw(numero, 13+2,"|");
refresh();
        f1->defiler();
        int i=0;
        int j=0;
        int k=0;
        while (!f1->estVide()){  
            mvprintw(numero, 15+i+j,"%d",f1->premier());
             if ((f1->premier()/10)<1){j=j+1;}
            else if((f1->premier()/10)<10){j=j+2;
                                           k=k+1;}
            else { j=j+3;
                    k=2+k;}

            mvprintw(numero, 15+j+i," ");
            i++;
                f1->defiler();
                   refresh();

 } 
        
        mvprintw(numero, (13+2*i+k),"]");
        delay_output(1000);

        this->afficherDefiler(numero,this->cpremier->getClient(),false, position);          // après avoir été servi, le client est défilé, on appelle donc la fonction corespondante pour afficher défilé
            refresh();


    }




};