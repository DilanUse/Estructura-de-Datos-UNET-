#pragma once

#include <string>


// representaci�n de datos comunes
class Datos
{
public:
	std::string nombre;
	int cedula;


	Datos() {}


	Datos( std::string nombre, int cedula )
	{
		this->nombre = nombre;
		this->cedula = cedula;
	} // fin del constructor 
}; // fin de Datos

