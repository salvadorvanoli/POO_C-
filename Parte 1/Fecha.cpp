#include "Fecha.h"

Fecha::Fecha(int dia, int mes, int anio){
    if((dia>31 || dia<1) || (mes>12 || mes<1) || (anio<1900)){
        throw invalid_argument("Fecha invalida");
    }
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}

Fecha::~Fecha(){
}

Fecha::Fecha(){} 

int Fecha::getDia(){
    return this->dia;
}

int Fecha::getMes(){
    return this->mes;
}

int Fecha::getAnio(){
    return this->anio;
}