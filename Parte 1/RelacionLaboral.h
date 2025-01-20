#ifndef RELACIONLABORAL_H
#define RELACIONLABORAL_H

#include "Fecha.h"
#include "Empresa.h"

class Fecha;
class Empresa;

class Relacion_Laboral{
    public:
        Relacion_Laboral(int, Empresa*); 
        ~Relacion_Laboral();
        float getSueldo();
        Fecha * getFechaDesvinculacion();
        Empresa * getEmpresa();
        void setSueldo(float);
        void setFechaDesvinculacion(Fecha);
        float getSueldoLiquido();
    private:
        float sueldo;
        Fecha * fechaDesvinculacion; 
        Empresa * empresa;
};
#endif