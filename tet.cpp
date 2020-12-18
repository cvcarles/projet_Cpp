#pragma once

#include <cassert>
#include "File.hpp"
#include "Noeud.hpp"
#include <iostream>
#include <sstream>

template <typename T>

class FileChainee : public File<T>{
private:
    Noeud<T> *last;
    Noeud<T> *first;

public:
    /*
     * Constructeur
     */
    FileChainee() : last(nullptr), first(nullptr) {}

    /*
     * Constructeur de copie
     */
    FileChainee(const FileChainee<T> &f) {
        this->first = dupliquer(f.first);
        this->last = this->first;
        while (this->last->getSuivant() != nullptr) this->last = this->last->getSuivant();
    }

    /*
     * Rôle: renvoie si la file est vide ou non
     */
    virtual bool estVide() const override {
        return this->last==nullptr;
    }

    /*
     * Rôle: renvoie le premier élément de la file
     */
    virtual const T &premier() const override {
        assert(!this->estVide());
        return (this->first)->getElement();
    }

    /*
     * Rôle: enfile un nouvel élément dans la file
     */
    virtual void enfiler(const T &x) override {
        Noeud<T> *p = new Noeud<T>(x);
        if (this->estVide()){
            this->first = p;
            this->last = this->first;
        }
        else {
            this->last->setSuivant(p);
            this->last = this->last->getSuivant();
        }
	}

    /*
     * Rôle: défile le premier élément de la file
     */
	virtual void defiler() override {
        assert(!this->estVide());

		Noeud<T> *p = this->first;
        if (getLongueur() == 1)
        {
            this->first = nullptr;
            this->last = nullptr;
        }
        else
        {
            this->first = (this->first)->getSuivant();
        }
        delete p;       
	}