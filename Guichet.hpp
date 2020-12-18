#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "FileChainee.hpp"

template <typename T>
class Guichet{
    private:
        Client c;
        int temps;              // temps au guichet 
        FileChainee file;

    public:
        