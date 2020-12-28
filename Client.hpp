#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <random>
#define TMING 1
#define TMAXG 20
#define TMINI 5
#define TMAXI 10
template <typename T>

class Client{
    private:
        T clt;
        Client<T> *suivant;
        int tempsGuichet;              // temps au guichet 
        int tempsImpatience;           // temps d'impatience
        int heureArrivee;              // heure d'arrivée du client

//----------------------Bases de la classe Client---------------------------------   
    public:

    // constructeur
        Client(const T &c=0, Client<T> *s=nullptr,int h=0): suivant(s),tempsGuichet(temps_Guichet()), tempsImpatience(temps_Impatience()),heureArrivee(h){clt=c;} ;     

    // accesseurs
        const T &getClient() const{
            return this->clt;
        }

        Client<T> *getSuivant() const{
            return this->suivant;
        }
        
        int getTempsG() const{
            return this->tempsGuichet;
        }

        int getTempsI() const{
            return this->tempsImpatience;
        }

        //donne l'heure d'arrivée du client
        int getHeure() const{
            return this->heureArrivee;
        }


   
    //mutateurs
        void setClient (const T &x){
            this->clt=x;
        }

         void setSuivant(Client<T> *s){
            this->suivant=s;
        }


        void setTempsG(const int t){
            this->tempsGuichet=t;
        }

        void setTempsI(const int t){
            this->tempsImpatience=t;
        }

        void setHeure(const int h){
            this->heureArrivee=h;
        }


    
    /* 
     * Rôle: utilise la loi uniforme entre TMING et TMAXG pour retourner le temps passé au guichet par un client                
     */

    int temps_Guichet(){
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distrib(TMING, TMAXG);
        return distrib(gen);
    }

    /* 
     * Rôle: utilise la loi uniforme entre TMINI et TMAXI pour retourner le temps de patience d'un client                
     */
    int temps_Impatience(){
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distrib(TMINI, TMAXI);
        return distrib(gen);
    }


    /* 
     * Rôle: surcharge d'opérateur utile pour les tests d'affichage                
     */

        const std::string toString() const {
            std::ostringstream s;
            s<<this->clt;
            return s.str();
        }

        friend std::ostream &operator << (std::ostream &f, const Client<T> &c){
            return f<<c.toString();
        }

};