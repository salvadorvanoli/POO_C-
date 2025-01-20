#include "Extranjera.h"

Extranjera::Extranjera(string id, Direccion direccion, string nombreFantasia) : Empresa(id, direccion){
    this->nombreFantasia = nombreFantasia;
    this->esNacional = false;
}

Extranjera::~Extranjera(){
}

string Extranjera::getNombreFantasia(){
    return this->nombreFantasia;
}

float Extranjera::getDescuento(){
    return 0.2;
}

string Extranjera::getDiferencial(){
    return this->nombreFantasia;
}