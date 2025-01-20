#include "DtEmpresa.h"

DtEmpresa::DtEmpresa(string id, Direccion direccion){
    this->id = id;
    this->direccion = direccion;
}

DtEmpresa::~DtEmpresa(){
}

string DtEmpresa::getId(){
    return this->id;
}

Direccion DtEmpresa::getDireccion(){
    return this->direccion;
}

bool DtEmpresa::getBool(){
    return this->esNacional;
}