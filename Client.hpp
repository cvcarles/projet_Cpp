#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <random>
#define TMIN 1  
#define TMAX 5
template <typename T>

class Client{
    private:
        T clt;
        Client<T> *suivant;
        
        
    public:
     int tempsGuichet;              // temps au guichet 
    // constructeur
        Client(const T &c=0, Client<T> *s=nullptr): suivant(s),tempsGuichet(temps_Guichet()){clt=c;} ;     // loi uniforme sur des entiers entre 0 et 20 sec) 

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
            std::uniform_int_distribution<> distrib(TMIN, TMAX);
            return distrib(gen);
        }
};