#pragma once
#include <string>
#include <iostream>
#include <sstream>

template <typename T>

class Client{
    private:
        T clt;
        Client<T> *suivant;

    public:
        // constructeur
        Client(const T &c, Client<T> *s=nullptr): suivant(s){clt=c;}

        // accesseurs
        const T &getClient() const{
            return this->clt;
        }

        Client<T> *getSuivant() const{
            return this->suivant;
        }

        //mutateurs
        void setSuivant(Client<T> *s){
            this->suivant=s;
        }

        void setClient (const T &x){
            this->clt=x;
        }

};