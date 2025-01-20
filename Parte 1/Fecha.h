#ifndef FECHA_H
#define FECHA_H

#include <iostream>
using namespace std;

class Fecha{
    public:
        Fecha(int, int, int);
        Fecha();
        ~Fecha();
        int getDia();
        int getMes();
        int getAnio(); 
        int dia;
        int mes;
        int anio; 
        friend ostream& operator << (ostream &o, Fecha fecha){
            o << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio() << endl;
            return o;
        }
};

#endif