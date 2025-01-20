#include "Empresa.h"

Empresa::Empresa(string id, Direccion direccion){
    this->id = id;
    this->direccion = direccion;
}

Empresa::~Empresa(){
}

string Empresa::getId(){
    return this->id;
}

Direccion Empresa::getDireccion(){
    return this->direccion;
}

bool Empresa::getBool(){
    return this->esNacional;
}