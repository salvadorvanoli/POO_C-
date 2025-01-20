#ifndef EMPRESA_H
#define EMPRESA_H

#include "Direccion.h"

class Direccion;

class Empresa{
    public:
        Empresa(string, Direccion);
        ~Empresa();
        string getId();
        Direccion getDireccion();
        virtual float getDescuento() = 0;
        bool getBool();
        virtual string getDiferencial() = 0;
    protected:
        string id;
        Direccion direccion;
        bool esNacional;
};


#endif