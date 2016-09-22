#pragma once

#include <string>
#include <cstring>


// representación de datos comunes
class Datos
{
public:
	char nombre[12];
	int cedula;


	Datos() {}


	Datos( std::string nombre, int cedula )
	{
		strcpy_s( this->nombre, 12, nombre.c_str );
		this->cedula = cedula;
	} // fin del constructor 
}; // fin de Datos

