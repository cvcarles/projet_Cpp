#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <random>
#define TMING 1
#define TMAXG 10
#define TMINI 5
#define TMAXI 10
template <typename T>

class Client{
    private:
        
        
        
    public:
            T clt;

    Client<T> *suivant;
     int tempsGuichet;              // temps au guichet 
     int tempsImpatience;           // temps d'impatience
     int heureArrivee;              // heure d'arrivée du client

    // constructeur
        Client(const T &c=0, Client<T> *s=nullptr,int h=0): suivant(s),tempsGuichet(temps_Guichet()), tempsImpatience(temps_Impatience()),heureArrivee(h){clt=c;} ;     // loi uniforme sur des entiers entre 0 et 20 sec) 

    // accesseurs
        const T &getClient() const{
            return this->clt;
        }

        Client<T> *getSuivant() const{
            return this->suivant;
        }
        
        int getTemps() const{
            return this->tempsGuichet;
        }

        //donne l'heure d'arrivée du client
        int getHeure() const{
            return this->heureArrivee;
        }


   
    //mutateurs
        void setSuivant(Client<T> *s){
            this->suivant=s;
        }

        void setClient (const T &x){
            this->clt=x;
        }

        void setTemps(const int t){
            this->tempsGuichet=t;
        }

        void setHeure(const int h){
            this->heureArrivee=h;
        }


        const std::string toString() const {
            std::ostringstream s;
            s<<this->clt;
            return s.str();
        }

        friend std::ostream &operator << (std::ostream &f, const Client<T> &c){
            return f<<c.toString();
        }

        int temps_Guichet(){
            std::random_device rd;  
            std::mt19937 gen(rd()); 
            std::uniform_int_distribution<> distrib(TMING, TMAXG);
            return distrib(gen);
        }

        int temps_Impatience(){
            std::random_device rd;  
            std::mt19937 gen(rd()); 
            std::uniform_int_distribution<> distrib(TMINI, TMAXI);
            return distrib(gen);
        }
};