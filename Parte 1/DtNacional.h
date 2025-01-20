#ifndef DTNACIONAL_H
#define DTNACIONAL_H

#include "DtEmpresa.h"

class DtEmpresa;

class DtNacional : public DtEmpresa {
    public:
        DtNacional(string, Direccion, string);
        ~DtNacional();
        string getRut(); 
        friend ostream& operator << (ostream &o, DtNacional empresa){
            o << "Id Empresa: " << empresa.getId() << endl << "Dirección: " << empresa.getDireccion() << endl << "RUT: " << empresa.getRut() << endl;
            return o;
        }
        string getDiferencial() override;
    private:
        string rut;
};

#endif