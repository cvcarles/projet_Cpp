#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <random>
#include <time.h>
#include <array>
#include <vector>
#include <ncurses.h>
//#include "FileChainee.hpp"
#include "Guichet.hpp"

template <typename T>

/* La classe Poste représente une poste composée de n guichets et régit par le temps d'ouverture*/

class Poste{
    private:
        int tempsOuverture;                 // temps d'ouverture de la poste
        int nombreGuichet;                  // nombre de guichet dans la poste      

        FileChainee<int> fileTableau[1];    // 
        Guichet<int> guichetTableau[1];

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
	   std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distrib(0,1);
        return (double)distrib(gen);
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
    void traitementClient(int indice,int *t,int *position){
        int numeroGuichet=indice+1;                                 // Pour commencer la numérotation des guichets à 1
        
        if (*t>(this->guichetTableau[indice].getLibre())){
            if (!fileTableau[indice].estVide()){   
                int temps=*t+(fileTableau[indice].cpremier)->getTempsG();
                this->guichetTableau[indice].setLibre(temps); // libre prend le temp courant + le temps que le client prendra au guichet
                fileTableau[indice].afficherFin(numeroGuichet, *position);         // affiche l'état de la file
                fileTableau[indice].defiler();                          // défile le client une fois traité
        }
        }
    }

    /* 
     * Rôle: vérifie s'il y a des clients impatients dans les files d'attente si oui, on les défile
     *       le temps courant et le numéro du client                          
     */ 

    void impatient(int t, int numero, int &nbrclient,int *compte, int *position){
        
            FileChainee<T> *f= new FileChainee<T>((this->fileTableau[numero]));
            while (!f->estVide()){
                if (t-(f->premier()) < 5) {//((f->cpremier->getSuivant())->getTempsI())){         //  if ((t-f->cpremier->getHeure()) > ((f->cpremier)->getTempsI())){
                    this->fileTableau[numero]=this->fileTableau[numero].defilerImpatient(f->cpremier,numero+1,t,*position);
                    nbrclient++;
                }
               f->defiler();
                
        }

    }


    void afficherNcurses(){
        initscr();           /* Start curses mode          */
    for (int i=1; i<=nombreGuichet; i++){
        mvprintw(i, 0, "Guichet ");
        mvprintw(i, 8,"%d",i);
        mvprintw(i, 10, ": [");
        mvprintw(i, 13, "]");
        delay_output(1000);


    }
               

    refresh();          /* Print it on to the real screen */


        delay_output(2000);

    }


     /* 
     * Rôle: Lance l'algorithme principal du programme                  
     */
    void algoPrincipal(int *compte){
        afficherNcurses();
        int position=0;
        int nombreClientsImpatients=0;

        for (int t=1; t<this->getTempsP(); t++){               // tant que la poste est ouverte, à chaque minute on fait
                                                                                                
            double p=this->probabilite();                      // on calcule la probabilité qu'un client arrive dans le bureau                             
            int indiceCourte=plusCourte();                     // indice de la file la plus courte
            int numeroGuichet=indiceCourte+1;                  // Pour commencer la numérotation des guichets à 1
               

            if (p<=0.83){                                                 // si la probabilité est inférieure à 50 clients par heure =0,83
                (this->fileTableau[indiceCourte]).enfiler(*compte,t);           // on enfile le client sur la file la plus courte à l'instant t
                this->fileTableau[indiceCourte].afficherEnfiler(numeroGuichet,&position); // on affiche le fait d'avoir enfilé
                *compte=*compte+1;                                              // le compte des numéros de client est incrémenté de 1
            }

            for (int j=0; j<this->nombreGuichet; j++){
                
                if((this->guichetTableau[j].getLibre())<=t){              // Le guichet ne sera disponible qu'une fois le précédent client traité
                    traitementClient(j,&t,&position);                              // traitement du client si le guichet est libre
                }
                //impatient(t,j,nombreClientsImpatients,compte,&position);                                     // on défile les clients impatients de la file 
            }
        }
       // std::cout<<"Nombre de clients impatients "<<nombreClientsImpatients<<std::endl;
       // std::cout<<"Nombre de clients total "<<*compte-1<<std::endl;
       // std::cout<<"Ratio "<<(double)nombreClientsImpatients/(*compte-1)<<std::endl;
       // std::cout<<std::endl;

        mvprintw(nombreGuichet+2,0,"Poste fermée");

       // std::cout<<"Poste fermée"<<std::endl;
           getch();            /* Wait for user input */

    endwin();          

    }

};
    