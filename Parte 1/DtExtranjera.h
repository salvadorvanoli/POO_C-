#ifndef DTEXTRANJERA_H
#define DTEXTRANJERA_H

#include "DtEmpresa.h"

class DtEmpresa;

class DtExtranjera : public DtEmpresa{
    public:
        DtExtranjera(string, Direccion, string);
        ~DtExtranjera();
        string getNombreFantasia(); 
        friend ostream& operator << (ostream &o, DtExtranjera empresa){
            o << "Id Empresa: " << empresa.getId() << endl << "Dirección: " << empresa.getDireccion() << endl << "Nombre fantasía: " << empresa.getNombreFantasia() << endl;
            return o;
        }
        string getDiferencial() override;
    private:
        string nombreFantasia;
};

#endif