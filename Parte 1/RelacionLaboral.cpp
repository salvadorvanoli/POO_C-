#include "RelacionLaboral.h"

Relacion_Laboral::Relacion_Laboral(int _sueldo, Empresa* empresa){
    this->sueldo = _sueldo;
    this->empresa = empresa;
    this->fechaDesvinculacion = NULL; 
}

Relacion_Laboral::~Relacion_Laboral(){
}

float Relacion_Laboral::getSueldo(){
    return this->sueldo;
}

Fecha* Relacion_Laboral::getFechaDesvinculacion(){
    return this->fechaDesvinculacion;
}

Empresa * Relacion_Laboral::getEmpresa(){
    return this->empresa;
}

void Relacion_Laboral::setSueldo(float sueldo){
    this->sueldo = sueldo;
}

void Relacion_Laboral::setFechaDesvinculacion(Fecha fechaDesvinculacion){
    this->fechaDesvinculacion = new Fecha(fechaDesvinculacion.dia, fechaDesvinculacion.mes, fechaDesvinculacion.anio); // Ahora crea una nueva fecha de desvinculación cuando se termina el contrato
}

float Relacion_Laboral::getSueldoLiquido(){
    return (this->sueldo * this->empresa->getDescuento());
}