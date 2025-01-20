#include <iostream>
using namespace std;
#define MAX_EMPLEADOS 200
#define MAX_EMPRESAS 200

#include "Direccion.h" 
#include "Fecha.h"
#include "DtEmpleado.h"
#include "DtEmpresa.h"
#include "DtExtranjera.h"
#include "DtNacional.h" 
#include "Empresa.h"
#include "Extranjera.h"
#include "Nacional.h" 
#include "RelacionLaboral.h" 
#include "Empleado.h"

Empleado * arregloEmpleados[MAX_EMPLEADOS];
Empresa * arregloEmpresas[MAX_EMPRESAS];
int cantidadEmpleados;
int cantidadEmpresas;

/*
Crea un nuevo empleado en el sistema. En
caso de ya existir, levanta la excepción std::invalid_argument.
*/

void agregarEmpleado(string ci, string nombre, string apellido, Direccion dir){
    for (int i = 0; i < MAX_EMPLEADOS; i++){
        if (arregloEmpleados[i] == NULL){
            Empleado * nuevo = new Empleado(ci, nombre, apellido, dir);
            arregloEmpleados[i] = nuevo;
            return;
        }
        if (ci == arregloEmpleados[i]->getCi()){
            throw invalid_argument("Ese empleado ya está en el sistema");
        }
    }
}

/*
Crea una nueva 
empresa en el sistema. En caso de ya existir, levanta una excepción 
std::invalid_argument.
*/

void agregarEmpresa(DtEmpresa * empresa){
    for(int i = 0; i < MAX_EMPRESAS; i++){
        if(arregloEmpresas[i] == NULL){
            Empresa * nuevo = NULL;
            if(empresa->getBool()){
                nuevo = new Nacional(empresa->getId(), empresa->getDireccion(), empresa->getDiferencial());
            } else {
                nuevo = new Extranjera(empresa->getId(), empresa->getDireccion(), empresa->getDiferencial());
            }
            arregloEmpresas[i] = nuevo;
            return;
        }
        if(arregloEmpresas[i]->getId() == empresa->getId()){
            throw invalid_argument("Esa empresa ya está en el sistema");
        }
    }
}

/*
Retorna un arreglo de DtEmpleado* con todos los empleados del sistema. El largo 
del arreglo de empleados está dado por el parámetro cantEmpleados.
*/

DtEmpleado ** listarEmpleados(int & cantEmpleados){
    DtEmpleado ** lista = new DtEmpleado * [cantEmpleados];
    for(int i = 0 ; i < cantEmpleados; i++){
        float sueldoLiquido = 0;
        for(int j = 0; j < arregloEmpleados[i]->getCantContratos(); j++){
            if(arregloEmpleados[i]->Contratos[j]->getFechaDesvinculacion() != NULL){
                sueldoLiquido += arregloEmpleados[i]->Contratos[j]->getSueldoLiquido();
            }
        }
        lista[i] = new DtEmpleado(arregloEmpleados[i]->getCi(), arregloEmpleados[i]->getNombre(), arregloEmpleados[i]->getApellido(), arregloEmpleados[i]->getDireccion(), sueldoLiquido); // Crea el elemento DtEmpleado, ya que antes usaba un empleado que no se podía leer
    }
    return lista;
}

/* 
Vincula un empleado con una empresa. Si la 
empresa ya está dentro de las empresas que el empleado ha trabajado o 
trabaja se levanta una excepción std::invalid_argument.
*/

void agregarRelacionLaboral(string ciEmpleado, string idEmpresa, float sueldo) {
    Empleado* a = nullptr;
    Empresa* b = nullptr;

    int numEmpleado = 0;
    for (int i = 0; i < MAX_EMPLEADOS; i++) {
        if(arregloEmpleados[i] == NULL){
            break;
        }
        if (ciEmpleado == arregloEmpleados[i]->getCi()) {
            a = arregloEmpleados[i];
            if (a->getCantContratos() == 50){
                throw invalid_argument("El empleado ha alcanzado el limite de relaciones laborales");
            }
            numEmpleado = i;
            break;
        }
    }

    if(a == nullptr){
        throw invalid_argument("No se encontró al empleado en el sistema");
    }

    for (int j = 0; j < MAX_EMPRESAS; j++) {
        if(arregloEmpresas[j] == NULL){
            break;
        }
        if (idEmpresa == arregloEmpresas[j]->getId()) {
            b = arregloEmpresas[j];
            break;
        }
    }

    if (b == nullptr) {
        throw invalid_argument("No se encuentró la empresa en el sistema");
    }

    for (int k = 0; k < a->getCantContratos(); k++) {
        if(a->getContratos()[k]->getEmpresa()->getId() == b->getId())
            throw invalid_argument("El contrato ya existe");
    }

    a->getContratos()[a->getCantContratos()] = new Relacion_Laboral(sueldo, b);
    a->setCantContratos(a->getCantContratos() + 1);
    arregloEmpleados[numEmpleado] = a;
}

/* 
Desvincula al empleado de la empresa, registrando la fecha en que terminó el vinculo 
void finalizarRelacionLaboral(string ciEmpleado, string idEmpresa, Fecha desvinculación){
*/

void finalizarRelacionLaboral(string ciEmpleado, string idEmpresa, Fecha desvinculacion){
    for(int i = 0; i<=MAX_EMPLEADOS; i++){
        if(arregloEmpleados[i] == NULL){
            throw invalid_argument("No se encontró la relación laboral");
        }
        if(arregloEmpleados[i]->getCi() != ""){
            if(arregloEmpleados[i]->getCi() == ciEmpleado){
                for(int j = 0; j < arregloEmpleados[i]->getCantContratos(); j++){
                    if (arregloEmpleados[i]->getContratos()[j]->getEmpresa()->getId() == idEmpresa){
                        arregloEmpleados[i]->getContratos()[j]->setFechaDesvinculacion(desvinculacion);
                        return;
                    }
                }
            }
        }
    }
    throw invalid_argument("No se encontró el empleado");
}

/*
Retorna un arreglo con las 
empresas donde trabaja activamente el empleado. El largo del arreglo de 
empresas está dado por el parámetro cantEmpresas.
*/

DtEmpresa ** obtenerInfoEmpresaPorEmpleado(string ciEmpleado, int & cantEmpresas){
    int cont = 0;
    bool empresaHay = false;
    if (cantEmpresas == 0){
        throw invalid_argument("No hay empresas en el sistema");
    }
    DtEmpresa ** lista = new DtEmpresa * [cantEmpresas];
    for(int i = 0; i <= MAX_EMPLEADOS; i++){
        if(arregloEmpleados[i] != NULL){
            if(arregloEmpleados[i]->getCi() == ciEmpleado){
                for(int j = 0; j < arregloEmpleados[i]->getCantContratos(); j++){
                    if(arregloEmpleados[i]->getContratos()[j]->getFechaDesvinculacion() == NULL){
                        DtEmpresa * empresa = NULL;
                        if(arregloEmpleados[i]->getContratos()[j]->getEmpresa()->getBool()){
                            empresa = new DtNacional(arregloEmpleados[i]->getContratos()[j]->getEmpresa()->getId(), arregloEmpleados[i]->getContratos()[j]->getEmpresa()->getDireccion(), arregloEmpleados[i]->getContratos()[j]->getEmpresa()->getDiferencial());
                        } else {
                            empresa = new DtExtranjera(arregloEmpleados[i]->getContratos()[j]->getEmpresa()->getId(), arregloEmpleados[i]->getContratos()[j]->getEmpresa()->getDireccion(), arregloEmpleados[i]->getContratos()[j]->getEmpresa()->getDiferencial());
                        }
                        lista[cont] = empresa;
                        cont++;
                        empresaHay = true;
                    }
                }
                break;
            }
        } else {
            throw invalid_argument("No se encontró al empleado en el sistema");
        }
    }
    if (!empresaHay){
        return NULL;
    }
    return lista;
}

// ------------------- [ FUNCIONES AUXILIARES PARA IMPRIMIR ] -------------------

void imprimirArregloEmpleados() {
    cout << "Lista de empleados: " << endl;
    for (int i = 0; i < MAX_EMPLEADOS; i++) {
        if (arregloEmpleados[i] != nullptr) {
            cout << "Nombre: " << arregloEmpleados[i]->getNombre() << "   " << "CI: " << arregloEmpleados[i]->getCi() << endl;
        } else {
            break;
        }
    }
    cout << endl;
}

void imprimirArregloEmpresas() {
    cout << "Lista de empresas: " << endl;
    for (int i = 0; i < MAX_EMPRESAS; i++) {
        if (arregloEmpresas[i] != nullptr) {
            if (arregloEmpresas[i]->getBool() == 1) {
                cout << "Id: " << arregloEmpresas[i]->getId() << "   " << "Nacional" << endl;
            } else {
                cout << "Id: " << arregloEmpresas[i]->getId() << "   " << "Extranjera" << endl;
            }
        } else {
            break;
        }
    }
}

void imprimirListaEmpleados(DtEmpleado** listaEmpleados, int cantEmpleados) {
    cout << "Lista de empleados: " << endl;
    for (int i = 0; i < cantEmpleados; i++) {
        if (listaEmpleados[i] != nullptr) {
            cout << "Nombre: " << listaEmpleados[i]->getNombre() << endl;
            cout << "Apellido: " << listaEmpleados[i]->getApellido() << endl;
            cout << "CI: " << listaEmpleados[i]->getCi() << endl;
            cout << endl;
        } else {
            break;
        }
    }
}

void imprimirListaEmpresasporPersona(DtEmpresa ** listaEmpresas, int cantEmpresas) {
   
    if (listaEmpresas == nullptr) {
        cout << "La lista de empresas está vacía." << endl;
        return;
    }

    for (int i = 0; i < cantEmpresas; i++) {
        if (listaEmpresas[i] != nullptr) {
            cout << "ID: " << listaEmpresas[i]->getId() << endl;
        } else {
            break;
        }
    }
}

// ------------------------ [ FUNCIONES DE LA INTERFAZ ] ------------------------

void manejarAgregarEmpleado(){
    string nom;
    string ape;
    string ci;
    string calle;
    string pais;
    string numero;
    string ciudad;
    Direccion direccion;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << "Introduzca nombre del empleado" << endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> nom;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << "Introduzca apellido del empleado" << endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> ape;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout <<"Introduzca ci del empleado"<< endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> ci;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout <<"Introduzca calle del empleado"<< endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> calle;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout <<"Introduzca numero del empleado"<< endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> numero;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout <<"Introduzca ciudad del empleado"<< endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> ciudad;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout <<"Introduzca pais del empleado"<< endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> pais;
    Direccion * dir = new Direccion(pais, ciudad, numero, calle);
    try{
        system("cls");
        agregarEmpleado(ci, nom, ape, *dir);
        cantidadEmpleados++;
    } catch (invalid_argument & ia){
        system("cls");
        cout << "------------------------------------------" << endl;
        cout << " No se pudo realizar la función correctamente" << endl << endl;
        cout << " ERROR: " << ia.what() << endl;
        cout << "------------------------------------------" << endl << endl;
        cin;
        return;
    }
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << " CI insertado: " << ci << endl;
    cout << " Nombre insertado: " << nom << endl;
    cout << " Apellido insertada: " << ape << endl;
    cout << " Dirección insertada: " << *dir << endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> ci;
    return;
}

void manejarAgregarEmpresa(){
    string opcionEmpresa;
    string id;
    string diferencial;
    string pais;
    string ciudad;
    string calle;
    string numero;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << " ¿Que tipo de empresa quieres agregar?" << endl;
    cout << " 1 - Empresa Extranjera" << endl;
    cout << " 2 - Empresa Nacional" << endl;
    cout << "------------------------------------------" << endl << endl;
    do {
        cin >> opcionEmpresa;
        if (opcionEmpresa == "1"){
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese un ID para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> id;
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese un Nombre Fantasía para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> diferencial;
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese un pais para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> pais;
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese una ciudad para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;;
            cin >> ciudad;
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese una calle para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> calle;
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese un número para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> numero;
            Direccion * dir = new Direccion(pais, ciudad, numero, calle);
            DtExtranjera * emp = new DtExtranjera(id, *dir, diferencial);
            try{
                agregarEmpresa(emp);
                system("cls");
                cout << "------------------------------------------" << endl << endl;
                cout << " ID insertado: " << id << endl;
                cout << " Nombre Fantasía insertado: " << diferencial << endl;
                cout << " Dirección insertada:" << *dir << endl;
                cout << "------------------------------------------" << endl << endl;
                cantidadEmpresas++;
            } catch (invalid_argument & ia){
                system("cls");
                cout << "------------------------------------------" << endl << endl;
                cout << " No se pudo realizar la función correctamente" << endl << endl;
                cout << " ERROR: " << ia.what() << endl;
                cout << "------------------------------------------" << endl << endl;
                cin >> id;
                return;
            }
            cin >> id;
            return;
        }
        if (opcionEmpresa == "2"){
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese un ID para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> id;
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese un RUT para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> diferencial;
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese un pais para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> pais;
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese una ciudad para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> ciudad;
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese una calle para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> calle;
            system("cls");
            cout << "------------------------------------------" << endl;
            cout << " Ingrese un número para la empresa" << endl;
            cout << "------------------------------------------" << endl << endl;
            cin >> numero;
            system("cls");
            Direccion * dir = new Direccion(pais, ciudad, numero, calle);
            DtNacional * emp = new DtNacional(id, *dir, diferencial);
            try{
                system("cls");
                agregarEmpresa(emp);
                cout << "------------------------------------------" << endl;
                cout << " id insertado: " << id << endl;
                cout << " Diferencial insertado: " << diferencial << endl;
                cout << " Direccion insertada:" << *dir << endl;
                cout << "------------------------------------------" << endl << endl;
                cantidadEmpresas++;
            } catch (invalid_argument & ia){
                system("cls");
                cout << "------------------------------------------" << endl << endl;
                cout << " No se pudo realizar la función correctamente" << endl << endl;
                cout << " ERROR: " << ia.what() << endl;
                cout << "------------------------------------------" << endl << endl;
                cin >> id;
                return;
            }
            cin >> id;
            return;
        }
        if (opcionEmpresa != "1" && opcionEmpresa != "2"){
            cout << "Elija una opción válida" << endl;
        }
    } while (opcionEmpresa != "1" && opcionEmpresa != "2");
}

void manejarListarEmpleados(int & cantEmpleados){
    system("cls");
    string a;
    try{
        DtEmpleado ** lista = listarEmpleados(cantEmpleados);
        cout << "------------------------------------------" << endl << endl;
        imprimirListaEmpleados(lista, cantEmpleados);
        cout << "------------------------------------------" << endl << endl;
    } catch (invalid_argument & ia){
        system("cls");
        cout << "------------------------------------------" << endl << endl;
        cout << " No se pudo realizar la función correctamente" << endl << endl;
        cout << " ERROR: " << ia.what() << endl;
        cout << "------------------------------------------" << endl << endl;
        cin >> a;
        return;
    }
    cin >> a;
    return;
}

void manejarAgregarRelacionLaboral(){
    string ciEmpleado;
    string idEmpresa;
    float sueldoLiquido;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << " Introduzca el CI del empleado a agregar" << endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> ciEmpleado;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << " Introduzca el ID de la empresa" << endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> idEmpresa;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << " Introduzca el sueldo líquido de la relación" << endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> sueldoLiquido;
    system("cls");
    try{
        system("cls");
        agregarRelacionLaboral(ciEmpleado, idEmpresa, sueldoLiquido);
        cout << "------------------------------------------" << endl;
        cout << " CI insertado: " << ciEmpleado << endl;
        cout << " idEmpresa insertado: " << idEmpresa << endl;
        cout << " Sueldo insertado:" << sueldoLiquido << endl;
        cout << "------------------------------------------" << endl << endl;
    }  catch (invalid_argument & ia){
        system("cls");
        cout << "------------------------------------------" << endl << endl;
        cout << " No se pudo realizar la función correctamente" << endl;
        cout << " ERROR: " << ia.what() << endl;
        cout << "------------------------------------------" << endl << endl;
        cin >> ciEmpleado;
        return;
    }
    cin >> ciEmpleado;
}

void manejarTerminarRelacionLaboral(){
    system("cls");
    string ci;
    string idEmpresa;
    Fecha * desvinculacion;
    cout << "------------------------------------------" << endl << endl;
    cout << " Ingrese el ci del empleado" << endl << endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> ci;
    system("cls");
    cout << "------------------------------------------" << endl << endl;
    cout << " Ingrese el id de la empresa" << endl << endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> idEmpresa;
    system("cls");
    int dia;
    int mes;
    int anio;
    cout << "------------------------------------------" << endl;
    cout << " Ingresa el dia, mes y año (en ese orden)" << endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> dia;
    cin >> mes;
    cin >> anio;
    try{
        desvinculacion = new Fecha(dia, mes, anio);
    } catch (invalid_argument & ia){
        system("cls");
        cout << "------------------------------------------" << endl << endl;
        cout << " No se pudo realizar la función correctamente" << endl << endl;
        cout << " ERROR: " << ia.what() << endl;
        cout << "------------------------------------------" << endl << endl;
        cin >> dia;
        return;
    }
    try{
        finalizarRelacionLaboral(ci, idEmpresa, *desvinculacion);
        system("cls");
        cout << "------------------------------------------" << endl << endl;
        cout << " CI insertado: " << ci << endl;
        cout << " idEmpresa insertado: " << idEmpresa << endl;
        cout << " Fecha insertada:" << *desvinculacion << endl;
        cout << "------------------------------------------" << endl << endl;
    } catch (invalid_argument & ia){
        system("cls");
        cout << "------------------------------------------" << endl << endl;
        cout << " No se pudo realizar la función correctamente" << endl << endl;
        cout << " ERROR: " << ia.what() << endl;
        cout << "------------------------------------------" << endl << endl;
        cin >> dia;
        return;
    }
    cin >> dia;
}

void manejarListarEmpresasPorEmpleado(){
    string idEmpleado;
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << " Introduzca el CI del empleado" << endl;
    cout << "------------------------------------------" << endl << endl;
    cin >> idEmpleado;
    DtEmpresa ** lista;
    try{
        lista = obtenerInfoEmpresaPorEmpleado(idEmpleado, cantidadEmpresas);
    } catch (invalid_argument & ia){
        system("cls");
        cout << "------------------------------------------" << endl;
        cout << " No se pudo realizar la función correctamente" << endl << endl;
        cout << " ERROR: " << ia.what() << endl;
        cout << "------------------------------------------" << endl << endl;
        cin >> idEmpleado;
        return;
    }
    if (lista == NULL){
        system("cls");
        cout << "------------------------------------------" << endl;
        cout << " El empleado no tiene relaciones laborales" << endl;
        cout << "------------------------------------------" << endl << endl;
        cin >> idEmpleado;
        return;
    }
    system("cls");
    cout << "------------------------------------------" << endl;
    for(int i = 0; i < cantidadEmpresas; i++){
        if (lista[i] == NULL){
            break;
        }
        cout << " ID de la empresa: " << lista[i]->getId() << endl;
        cout << " Diferencial de la empresa: " << lista[i]->getDiferencial() << endl;
        cout << "------------------------------------------" << endl << endl;
    }
    cin >> idEmpleado;
}

void manejarMenu(){
    string opcion;
    do {
        system("cls");
        cout << "------------------------------------------" << endl;
        cout << " Elija su siguiente acción" << endl << endl << endl;
        cout << " 1 - Agregar empleado" << endl;
        cout << " 2 - Agregar empresa" << endl;
        cout << " 3 - Listar empleados" << endl;
        cout << " 4 - Agregar relación laboral" << endl;
        cout << " 5 - Terminar relación laboral" << endl;
        cout << " 6 - Listar empresas de un empleado" << endl;
        cout << " exit - Salir del programa" << endl << endl;
        cout << "------------------------------------------" << endl << endl;
        cin >> opcion;
        if(opcion == "1"){
            manejarAgregarEmpleado();
        } else if(opcion == "2"){
            manejarAgregarEmpresa();
        } else if(opcion == "3"){
            manejarListarEmpleados(cantidadEmpleados);
        } else if(opcion == "4"){
            manejarAgregarRelacionLaboral();
        } else if(opcion == "5"){
            manejarTerminarRelacionLaboral();
        } else if(opcion == "6"){
            manejarListarEmpresasPorEmpleado();
        } else if(opcion == "exit"){
            break;
        } else {
            cout << "------------------------------------------" << endl;
            cout << " Elija una opción válida" << endl;
            cout << "------------------------------------------" << endl << endl;
        }
    } while (opcion != "exit");
    return;
}

// ---------------------------------- [ MAIN ] ----------------------------------

int main(){
    manejarMenu();
}

// int main(){
//     try{

//         Direccion * dir = new Direccion("Uruguay", "Santa Lucía", "3", "Antonio Volpe");
//         Direccion * dir2 = new Direccion("Argentina", "Buenos Aires", "7", "Messi");

//         cout << endl << "PENE TEST DE LA FUNCIÓN agregarEmpleado()" << endl << endl;

//         agregarEmpleado("56201985", "Salvador", "Vanoli", *dir);

//         cout << arregloEmpleados[0]->getCi() << endl;
//         cout << arregloEmpleados[0]->getNombre() << endl;
//         cout << arregloEmpleados[0]->getApellido() << endl << endl;

//         agregarEmpleado("40029312", "Luigi", "Mario", *dir2);

//         cout << arregloEmpleados[1]->getCi() << endl;
//         cout << arregloEmpleados[1]->getNombre() << endl;
//         cout << arregloEmpleados[1]->getApellido() << endl;

//         cout << endl << "TEST DE LA FUNCIÓN agregarEmpresa()" << endl << endl;

//         DtExtranjera * nuevaExtranjera = new DtExtranjera("1234", *dir, "Coca-Cola");
//         DtNacional * nuevaExtranjera2 = new DtNacional("5678", *dir2, "Pepsi");

//         agregarEmpresa(nuevaExtranjera);

//         cout << arregloEmpresas[0]->getId() << endl;
//         cout << arregloEmpresas[0]->getDireccion() << endl;
//         cout << arregloEmpresas[0]->getDiferencial() << endl;
//         cout << arregloEmpresas[0]->getDescuento() << endl << endl;

//         agregarEmpresa(nuevaExtranjera2);

//         cout << arregloEmpresas[1]->getId() << endl;
//         cout << arregloEmpresas[1]->getDireccion() << endl;
//         cout << arregloEmpresas[1]->getDiferencial() << endl;
//         cout << arregloEmpresas[1]->getDescuento() << endl;

//         cout << endl << "TEST DE LA FUNCIÓN listarEmpleados()" << endl << endl;

//         int cantEmpleados = 2;

//         DtEmpleado ** lista = listarEmpleados(cantEmpleados);

//         for(int i = 0; i < cantEmpleados; i++){
//             cout << lista[i]->getCi() << endl;
//             cout << lista[i]->getNombre() << endl;
//             cout << lista[i]->getApellido() << endl << endl;
//         }

//         cout << endl << "TEST DE LA FUNCIÓN agregarRelacionLaboral()" << endl << endl;

//         agregarRelacionLaboral("56201985", "1234", 50000.0);
//         agregarRelacionLaboral("56201985", "5678", 50000.0);

//         cout << arregloEmpleados[0]->getContratos()[0]->getSueldo() << endl;
//         cout << arregloEmpleados[0]->getContratos()[0]->getEmpresa()->getId() << endl;
//         cout << arregloEmpleados[0]->getContratos()[0]->getEmpresa()->getDiferencial() << endl << endl;

//         cout << arregloEmpleados[0]->getContratos()[1]->getSueldo() << endl;
//         cout << arregloEmpleados[0]->getContratos()[1]->getEmpresa()->getId() << endl;
//         cout << arregloEmpleados[0]->getContratos()[1]->getEmpresa()->getDiferencial() << endl;

//         cout << endl << "TEST DE LA FUNCIÓN finalizarRelacionLaboral()" << endl << endl;

//         Fecha * desvinculacion = new Fecha(30, 3, 2024);

//         finalizarRelacionLaboral("56201985", "1234", *desvinculacion);

//         cout << *arregloEmpleados[0]->getContratos()[0]->getFechaDesvinculacion();

//         cout << endl << "TEST DE LA FUNCIÓN obtenerInfoEmpresaPorEmpleado()" << endl << endl;

//         int cantEmpresas = 1;

//         DtEmpresa ** listaEmpresas = obtenerInfoEmpresaPorEmpleado("56201985", cantEmpresas);

//         for(int i = 0; i < cantEmpresas; i++){
//             cout << listaEmpresas[i]->getDiferencial() << endl;
//             cout << listaEmpresas[i]->getId() << endl << endl;
//         }
//     } catch (invalid_argument & ia){
//         cout << "ERROR: " << ia.what() << endl;
//     }
//     system("pause");
// }