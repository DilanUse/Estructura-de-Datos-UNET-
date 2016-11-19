#include "Vehiculo.h"

using namespace std; // uso del espacio de nombres std


// constructor por defecto
Vehiculo::Vehiculo()
{
	this->placa = this->marca = "";
} // fin del constructor por defecto


// constructor parametrico
Vehiculo::Vehiculo( string placa, string marca )
{
	this->placa = placa;
	this->marca = marca;
} // fin del // constructor parametrico 


// sobrecarga el operador de inserción de flujo 
ostream& operator<<( ostream& salida, const Vehiculo& datos )
{
	char delim = ','; // separador 
	
	// imprime atribtos separados por delim
	salida << datos.placa << delim << datos.marca;
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<
