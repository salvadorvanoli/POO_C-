#ifndef DTEMPRESA_H
#define DTEMPRESA_H

#include "Direccion.h"

class Direccion;

class DtEmpresa{
    public:
        DtEmpresa(string, Direccion);
        ~DtEmpresa();
        string getId();
        Direccion getDireccion();
        bool getBool();
        virtual string getDiferencial() = 0;
    protected:
        string id;
        Direccion direccion;
        bool esNacional;
};

#endif