#ifndef DIRECCION_H
#define DIRECCION_H

#include <iostream>
using namespace std;

class Direccion{
    public:
        Direccion(string, string, string, string);
        Direccion(){};
        ~Direccion();
        string getPais();
        string getCiudad();
        string getNumero();
        string getCalle();
        friend ostream& operator << (ostream &o, Direccion dir){
            o << '\n' << "     País: " << dir.getPais() << endl << "     Ciudad: " << dir.getCiudad() << endl << "     Numero: " << dir.getNumero() << endl << "     Calle: " << dir.getCalle();
            return o;
        } 
    private:
        string pais;
        string ciudad;
        string numero;
        string calle;
};


#endif