#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <random>
#include <time.h>
#include <array>
#include <vector>
#include "FileChainee.hpp"
#include "Guichet.hpp"

template <typename T>

/* La classe Poste représente une poste composée de n guichets et régit par le temps d'ouverture*/

class Poste{
    private:
        int tempsOuverture;                 // temps d'ouverture de la poste
        int nombreGuichet;                  // nombre de guichet dans la poste      

        FileChainee<int> fileTableau[2];    // 
        Guichet<int> guichetTableau[2];

    public:

 //----------------------Bases de la classe Poste---------------------------------   
    //constructeur
        Poste(int t=0, int n=1):tempsOuverture(t),nombreGuichet(n){ 
            for (int i=0; i<=this->nombreGuichet;i++){                  // une file est assimilée à un guichet de la poste    
                Guichet<int> guichetTableau(fileTableau[i]);
            }
        }

    //destructeur
    ~Poste(){};
    
    // accesseurs
        int getTempsP() const{                                      // renvoie le temps d'ouverture de la poste
            return this->tempsOuverture;
        }
        int getNbrG() const{                                        //renvoie le nombre de guichets de la poste
            return this->nombreGuichet;
        }

        //mutateurs
        void setTempsP (const int x){                               // assigne le temp d'ouverture de la poste
            this->tempsOuverture=x;
        }
        void setNbrG (const int n){                                 // assigne le nombre de guichets de la poste
            this->nombreGuichet=n;
        }


 //----------------------Méthodes de la classe Poste---------------------------------   

    /* 
     *Rôle: renvoie la propabilité qu'un client arrive
     */
    double probabilite(){
	   srand(time(0));
	    return  (double)rand()/(double) RAND_MAX; 
    }

    /* 
     *Rôle: renvoie l'indice de la file la plus courte de la poste (du tableau de file)
     */
    int plusCourte(){
        int court=1000;                                      // i longueur maximale estimée
        int j=1000;                                          // j correspond au numero de la file la plus courte

        for(int i=0; i<this->nombreGuichet;i++){             // pour chaque guichet, si la file est plus courte que 
            if(this->fileTableau[i].longueur()<court){       // celle précédemment retenue, on la garde et on retourne son indice
                court=this->fileTableau[i].longueur();
                j=i;
            }
        }
        return j;
    }

    /* 
     * Rôle: traite le client au guichet
     *       prend en paramètres l'indice de la file à traiter, le numéro du client, 
     *                           le temps courant et si le guichet et libre ou non 
     */
    void traitementClient(int indice,int *compte,int *t){
            int numeroGuichet=indice+1;                                 // Pour commencer la numérotation des guichets à 1

            if (!fileTableau[indice].estVide()){   
                int temps=*t+(fileTableau[indice].cpremier)->getTempsG();
                this->guichetTableau[indice].setLibre(temps); // libre prend le temp courant + le temps que le client prendra au guichet
                fileTableau[indice].afficherFin(numeroGuichet);         // affiche l'état de la file
                fileTableau[indice].defiler();                          // défile le client une fois traité
        }
    }

    /* 
     * Rôle: vérifie s'il y a des clients impatients dans les files d'attente si oui, on les défile
     *       le temps courant et le numéro du client                          
     */ 

    void impatient(int t,int numero){
        for(int i=0; i<this->nombreGuichet;i++){                                        // on vérifie le mécontentement des clients pour chaque files
            FileChainee<T> *f= new FileChainee<T>((this->fileTableau[i]));
            while (!f->estVide()){
                if ((t-f->cpremier->getHeure()) > ((f->cpremier)->getTempsI())){
                    this->fileTableau[i]=this->fileTableau[i].defilerImpatient(f->cpremier, numero);
                }
                f->defiler();
            }
        }

    }


     /* 
     * Rôle: Lance l'algorithme principal du programme                  
     */
    void algoPrincipal(int *compte){
    
        for (int t=1; t<this->getTempsP(); t++){               // tant que la poste est ouverte, à chaque minute on fait
                                                                                                
            double p=this->probabilite();                      // on calcule la probabilité qu'un client arrive dans le bureau                             
            int indiceCourte=plusCourte();                     // indice de la file la plus courte
            int numeroGuichet=indiceCourte+1;                  // Pour commencer la numérotation des guichets à 1
               


            if (p<=0.83){                                                       // si la probabilité est inférieure à 50 clients par heure =0,83
                (this->fileTableau[indiceCourte]).enfiler(*compte,t);           // on enfile le client sur la file la plus courte à l'instant t
                this->fileTableau[indiceCourte].afficherEnfiler(numeroGuichet); // on affiche le fait d'avoir enfilé

                *compte=*compte+1;                                              // le compte des numéros de client est incrémenté de 1
            }

            if((this->guichetTableau[indiceCourte].getLibre())<=t){             // Le guichet ne sera disponible qu'une fois le précédent client traité
                traitementClient(indiceCourte,compte,&t);                       // traitement du client si le guichet est libre
            }
                impatient(t,numeroGuichet);                                     // on défile les clients impatients de la file 
        }
        std::cout<<"Poste fermée"<<std::endl;

    }

};
    