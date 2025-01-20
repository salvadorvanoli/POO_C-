#include "DtExtranjera.h"

DtExtranjera::DtExtranjera(string id, Direccion direccion, string nombreFantasia) : DtEmpresa(id, direccion){
    this->nombreFantasia = nombreFantasia;
    this->esNacional = false;
}

DtExtranjera::~DtExtranjera(){
}

string DtExtranjera::getNombreFantasia(){
    return this->nombreFantasia;
}

string DtExtranjera::getDiferencial(){
    return this->nombreFantasia;
}