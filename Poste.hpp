#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <random>
#include <time.h>
#include <array>
#include "FileChainee.hpp"
#include "Guichet.hpp"

template <typename T>
class Poste{
    private:
        int tempsOuverture;              // temps d'ouverture de la poste
        FileChainee<int> fileTableau[1];
        Guichet<int> guichetTableau[1];

    public:
    int nombreGuichet;              // nombre de guichet dans la poste        

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
        //int t0=time(NULL);   
        if (!fileTableau[indice].estVide()){
            //Client<T> *p= new Client<T>(*compte);
            //filee.cpremier=p;
            *libre=*t+(fileTableau[indice].cpremier)->tempsGuichet;
            fileTableau[indice].afficherFin();
            fileTableau[indice].defiler();
            //std::cout<<"traitement"<<indice<<endl;


        }
    }

    // algorithme principal
    void algoPrincipal(int *compte){
        int libre=1;
        for (int t=1; t<this->getTempsP(); t++){
                                                                                                    // std::cout<<t<<std::endl;
            double p=this->probabilite();
                                                                                                     //std::cout<<"t="<<t<<endl;
            int indiceCourte=plusCourte();
        

            if (p<=0.83){
               // std::cout<<"proba"<<endl;

                (this->fileTableau[indiceCourte]).enfiler(*compte);
                this->fileTableau[indiceCourte].afficherEnfiler();
                this->fileTableau[indiceCourte].afficherAttente();

                *compte=*compte+1;

            }

            if(libre<=t){
                traitementClient(indiceCourte,compte,&t,&libre);
                //std::cout<<"libre"<<endl;

            }
        }
                    std::cout<<"Poste fermée"<<endl;



    }



};
    