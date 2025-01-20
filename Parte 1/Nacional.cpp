#include "Nacional.h"

Nacional::Nacional(string id, Direccion direccion, string rut) : Empresa(id, direccion) {
    this->rut = rut;
    this->esNacional = true;
}

Nacional::~Nacional(){
}

string Nacional::getRut(){
    return this->rut;
}

float Nacional::getDescuento(){
    return 0.35;
}

string Nacional::getDiferencial(){
    return this->rut;
}