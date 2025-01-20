#include "DtEmpleado.h"

DtEmpleado::DtEmpleado(string ci, string nombre, string apellido, Direccion dir, float sueldoLiquido){
    this->ci = ci;
    this->nombre = nombre;
    this->apellido = apellido;
    this->direccion = dir;
    this->sueldoLiquido = sueldoLiquido;
}

DtEmpleado::~DtEmpleado(){
}

string DtEmpleado::getCi(){
    return this->ci;
}

string DtEmpleado::getNombre(){
    return this->nombre;
}

string DtEmpleado::getApellido(){
    return this->apellido;
}

Direccion DtEmpleado::getDireccion(){
    return this->direccion;
}

float DtEmpleado::getSueldoLiquido(){
    return this->sueldoLiquido;
}

void DtEmpleado::setCi(string ci){
    this->ci = ci;
}

void DtEmpleado::setNombre(string nombre){
    this->nombre = nombre;
}

void DtEmpleado::setApellido(string apellido){
    this->apellido = apellido;
}

void DtEmpleado::setDireccion(Direccion direccion){
    this->direccion = direccion;
}

void DtEmpleado::setSueldoLiquido(float sueldoLiquido){
    this->sueldoLiquido = sueldoLiquido;
}