#include "Direccion.h"

Direccion::Direccion(string pais, string ciudad, string numero, string calle){
    this->pais = pais;
    this->ciudad = ciudad;
    this->numero = numero;
    this->calle = calle;
}

Direccion::~Direccion(){
}

string Direccion::getPais(){
    return this->pais;
}

string Direccion::getCiudad(){
    return this->ciudad;
}

string Direccion::getNumero(){
    return this->numero;
}

string Direccion::getCalle(){
    return this->calle;
}
