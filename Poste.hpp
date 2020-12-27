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
class Poste{
    private:
        int tempsOuverture;              // temps d'ouverture de la poste
        int nombreGuichet;              // nombre de guichet dans la poste      

        FileChainee<int> fileTableau[2];
        Guichet<int> guichetTableau[2];

    public:

    
    //constructeur
    Poste(int t=0, int n=1):tempsOuverture(t),nombreGuichet(n)
        { 
        
        for (int i=0; i<=this->nombreGuichet;i++){
            Guichet<int> guichetTableau(fileTableau[i]);
        }
    }

    ~Poste(){};
    
     // accesseur
    int getTempsP() const{
        return this->tempsOuverture;
    }
    int getNbrG() const{
        return this->nombreGuichet;
    }

    //mutateur
    void setTempsP (const int x){
        this->tempsOuverture=x;
    }
    void setNbrG (const int n){
        this->nombreGuichet=n;
    }

    // propabilité pour qu'un client arrive
    double probabilite(){
	   //srand(time(0));
	    return  (double)rand()/(double) RAND_MAX; 

    }

    //renvoie la file la plus courte du tableau
    int plusCourte(){
        int court=1000;
        int j=1000;                                          // j correspond au numero de la file la plus courte

        for(int i=0; i<this->nombreGuichet;i++){
            if(this->fileTableau[i].longueur()<court){
                court=this->fileTableau[i].longueur();
                j=i;
            }
           //std::cout<<"plusourte"<<j<<std::endl;
        }
        return j;
    }

    void traitementClient(int indice,int *compte,int *t, int *libre){
            int numeroGuichet=indice+1;
            if (!fileTableau[indice].estVide()){
            //Client<T> *p= new Client<T>(*compte);
            //filee.cpremier=p;
            *libre=*t+(fileTableau[indice].cpremier)->tempsGuichet;
            fileTableau[indice].afficherFin(numeroGuichet);
            fileTableau[indice].defiler();
            //std::cout<<"traitement"<<indice<<endl;


        }
    }

    // vérification des impatients
    void impatient(int i, int t,int numero){
         FileChainee<T> *f= new FileChainee<T>((this->fileTableau[i]));
        while (!f->estVide()){
            if (t>(f->cpremier)->tempsImpatience){
                this->fileTableau[i]=this->fileTableau[i].defilerImpatient(f->cpremier, numero);
            }
            f->defiler();

        }

    }


    // algorithme principal
    void algoPrincipal(int *compte){
        int libre=1;
        for (int t=1; t<this->getTempsP(); t++){
                                                                                                
            double p=this->probabilite();                                                         
            int indiceCourte=plusCourte();                      // indice de la file la plus courte
            int numeroGuichet=indiceCourte+1;                   // Pour commencer la numérotation des guichets à 1

             
            //for(int i=0; i<this->nombreGuichet;i++){
               


                if (p<=0.83){
                 //std::cout<<t<<endl;

                    (this->fileTableau[indiceCourte]).enfiler(*compte,t);
                    this->fileTableau[indiceCourte].afficherEnfiler(numeroGuichet);

                    *compte=*compte+1;

                }
                                // std::cout<<t<<endl;


                if(libre<=t){
                    traitementClient(indiceCourte,compte,&t,&libre);
                    //std::cout<<"libre"<<endl;

                }
                 impatient(indiceCourte,t,numeroGuichet);

            //}
        }
        std::cout<<"Poste fermée"<<std::endl;

    }



};
    