#ifndef EXTRANJERA_H
#define EXTRANJERA_H

#include "Empresa.h"

class Extranjera : public Empresa {
    public:
        Extranjera(string, Direccion, string); 
        ~Extranjera();
        string getNombreFantasia();      
        float getDescuento() override;
        string getDiferencial() override;
    private:
        string nombreFantasia;
};

#endif