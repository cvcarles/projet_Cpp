#pragma once
#include <iostream>
#include <assert.h> 
#include <fstream>

template<typename T>

class FileChainee {
    private:
        int max;        //nombre maximum de personne dans la file
        T *lesClients;  // tableau générique d'élément de type T

  
    public:
    //constructeur
    FileChainee(): sp(nullptr){}////////////////////

    //constructeur de copie

    // destructeur
    ~FileChainee(){
        delete [] this ->lesClients;
    }

    //methode de base de manipulation de la pile

    bool estVide() const;
    void enfiler(const T &x);
    void depiler();
    const T &premier() const;








    void detruire(noeud* n);

    friend std::ostream& operator <<(std::ostream &f,const pileChainee &p);

    const std::string toString() const;

    pileChainee (const pileChainee &pile);

    noeud *copie(const noeud* n);

    pileChainee &operator = (const pileChainee &pile);




};