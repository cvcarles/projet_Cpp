#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <random>
#include <time.h>
#include "FileChainee.hpp"
#include "Guichet.hpp"

template <typename T>
class Poste{
    private:
        int tempsOuverture;              // temps d'ouverture de la poste
        int nombreGuichet;              // nombre de guichet dans la poste        

    public:

    //constructeur
    Poste(int t=0, int n=1): tempsOuverture(t), nombreGuichet(n){}//file(nullptr){}////////////////////
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

    void algoPrincipal(FileChainee<T> &filee, Guichet<T> guichet,int *compte){
        int libre=1;
        for (int t=1; t<this->getTempsP(); t++){
           // std::cout<<t<<std::endl;
            double p=this->probabilite();
                //std::cout<<"t="<<t<<endl;

            if (p<=0.83){
                filee.enfiler(*compte);

                *compte=*compte+1;

                filee.afficherEnfiler();
            }
                //std::cout<<"libre="<<libre<<endl;

            if(libre<=t){
                guichet.traitementClient(filee,compte,&t,&libre);
            
                               // std::cout<<"libre="<<libre<<endl;

            }
            }
                    std::cout<<"Poste fermée"<<endl;



        }



};
    