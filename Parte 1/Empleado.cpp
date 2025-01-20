#include "Empleado.h"

Empleado::Empleado(string ci, string nombre, string apellido, Direccion direccion){
    this->ci = ci;
    this->nombre = nombre;
    this->apellido = apellido;
    this->direccion = direccion;
    this->Contratos = new Relacion_Laboral * [50];
    this->cantContratos = 0;
}

string Empleado::getCi(){
    return this->ci;
}

string Empleado::getNombre(){
    return this->nombre;
}

string Empleado::getApellido(){
    return this->apellido;
}

Direccion Empleado::getDireccion(){
    return this->direccion;
}

Relacion_Laboral ** Empleado::getContratos(){
    return this->Contratos;
}

int Empleado::getCantContratos(){
    return this->cantContratos;
}

void Empleado::setCi(string ci){
    this->ci = ci;
}

void Empleado::setNombre(string nombre){
    this->nombre = nombre;
}

void Empleado::setApellido(string apellido){
    this->apellido = apellido;
}

void Empleado::setDireccion(Direccion direccion){
    this->direccion = direccion;
}

void Empleado::setCantContratos(int cantContratos){
    this->cantContratos = cantContratos;
}