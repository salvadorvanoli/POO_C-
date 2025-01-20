#ifndef EMPLEADO_H
#define EMPLEADO_H

#include "RelacionLaboral.h"

class Relacion_Laboral;

class Empleado {
    public:
        Empleado(string, string, string, Direccion);
        string getCi();
        string getNombre();
        string getApellido();
        Direccion getDireccion();
        Relacion_Laboral ** getContratos();
        int getCantContratos();
        void setCi(string);
        void setNombre(string);
        void setApellido(string);
        void setDireccion(Direccion);
        void setCantContratos(int);
        Relacion_Laboral ** Contratos;
        int cantContratos;
    private:
        string ci;
        string nombre;
        string apellido;
        Direccion direccion;
};

#endif