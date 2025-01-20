#include "DtNacional.h"

DtNacional::DtNacional(string id, Direccion direccion, string rut) : DtEmpresa(id, direccion) {
    this->rut = rut;
    this->esNacional = true;
}

DtNacional::~DtNacional(){
}

string DtNacional::getRut(){
    return this->rut;
}

string DtNacional::getDiferencial(){
    return this->rut;
}