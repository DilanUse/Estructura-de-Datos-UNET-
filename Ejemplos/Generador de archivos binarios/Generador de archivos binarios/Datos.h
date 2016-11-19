#pragma once

/**
*	@Autor: Dilan Useche
*/

#include <string>
#include <cstring>


// representación de Datos comunes
class Datos
{
public:
	char nombre[12];
	int cedula;


	Datos() {} // constructor por defecto


	// constructor que incia el nombre y la cedula 
	Datos( std::string nom, int ced )
	{
		strcpy_s( this->nombre, 12, nom.c_str() );
		this->cedula = ced;
	} // fin del constructor 
}; // fin de Datos

