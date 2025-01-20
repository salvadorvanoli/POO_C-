#ifndef DTEMPLEADO_H
#define DTEMPLEADO_H

#include "Direccion.h"

class Direccion;

class DtEmpleado{
    public:
        DtEmpleado(string, string, string, Direccion, float);
        ~DtEmpleado();
        string getCi();
        string getNombre();
        string getApellido();
        Direccion getDireccion();
        float getSueldoLiquido();
        void setCi(string);
        void setNombre(string);
        void setApellido(string);
        void setDireccion(Direccion);
        void setSueldoLiquido(float);
    private:
        string ci;
        string nombre;
        string apellido;
        Direccion direccion;
        float sueldoLiquido;
};

#endif