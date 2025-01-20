#ifndef NACIONAL_H
#define NACIONAL_H

#include "Empresa.h"

class Nacional : public Empresa {
    public:
        Nacional(string, Direccion, string);
        ~Nacional();
        string getRut(); 
        float getDescuento() override;
        string getDiferencial() override;
    private:
        string rut;
};



#endif