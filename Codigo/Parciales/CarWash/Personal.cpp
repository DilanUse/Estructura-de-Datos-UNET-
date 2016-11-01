#include "Personal.h"

using namespace std; // uso del espacio de nombres estandar


// constructor predeterminado
Personal::Personal()
{
	this->id = 0;
	this->nombre = "";
	this->vehAsignado = NULL;
	this->ganancias = 0;
} // fin del constructor predeterminado


// constructor parametrico
Personal::Personal(int id, string nom )
{
	this->id = id;
	this->nombre = nom;
	this->vehAsignado = NULL;
	this->ganancias = 0;
} // fin del // constructor parametrico


// sobrecarga el operador relacional menor que
bool Personal::operator<( const Personal& datos )
{
	return ( this->id < datos.id );
} // fin del operador<


// sobrecarga el operador relacional mayor que
bool Personal::operator>( const Personal& datos )
{
	return ( this->id > datos.id );
} // fin del operador>


// sobrecarga el operador de igualdad
bool Personal::operator==( const Personal& datos )
{
	return ( this->id == datos.id); // retorna desición  
} // fin de operator==


// sobrecarga el operador de inserción de flujo 
ostream& operator<<( ostream& salida, const Personal& datos )
{
	char delim = ','; // separador 

	// imprime atribtos separados por delim
	salida << datos.id << delim << datos.nombre << "/" << "Vehiculo:" <<
	( datos.vehAsignado ? datos.vehAsignado->placa  : "Ninguno" );  
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<

