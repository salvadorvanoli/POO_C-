all: Direccion.o Fecha.o DtEmpleado.o DtEmpresa.o DtExtranjera.o DtNacional.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o Empleado.o main.o
	g++ Direccion.o Fecha.o DtEmpleado.o DtEmpresa.o DtExtranjera.o DtNacional.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o Empleado.o main.o -o programa.exe

Direccion.o:
	g++ -c Direccion.cpp

Fecha.o:
	g++ -c Fecha.cpp

DtEmpleado.o: Direccion.o
	g++ -c DtEmpleado.cpp

DtEmpresa.o: Direccion.o
	g++ -c DtEmpresa.cpp

DtExtranjera.o: Direccion.o DtEmpresa.o
	g++ -c DtExtranjera.cpp

DtNacional.o: Direccion.o DtEmpresa.o
	g++ -c DtNacional.cpp

Empresa.o: Direccion.o
	g++ -c Empresa.cpp

Extranjera.o: Direccion.o Empresa.o
	g++ -c Extranjera.cpp

Nacional.o: Direccion.o Empresa.o
	g++ -c Nacional.cpp

RelacionLaboral.o: Direccion.o Fecha.o Empresa.o Extranjera.o Nacional.o
	g++ -c RelacionLaboral.cpp

Empleado.o: Direccion.o Fecha.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o
	g++ -c Empleado.cpp

main.o:
	g++ -c main.cpp

clean:
	del /Q Direccion.o Fecha.o DtEmpleado.o DtEmpresa.o DtExtranjera.o DtNacional.o Empresa.o Extranjera.o Nacional.o RelacionLaboral.o Empleado.o main.o programa.exe

run:
	make clean
	make
	cls
	programa.exe