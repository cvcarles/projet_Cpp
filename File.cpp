#include<iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <fstream>
#include "File.hpp"

using namespace std;

template<typename T>

// dupliquer
Client<T>* File<T>::dupliquer(const Client<T> *clt){
        if (clt==nullptr) return nullptr;
        Client<T> *p=dupliquer(clt->getSuivant());
        return new Client<T>(clt->getClient(),p);
    }


