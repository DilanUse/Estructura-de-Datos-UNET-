#include "ProcessingLine.h"

ProcessingLine::ProcessingLine( int purityLevel, std::string description )
{
	this->purityLevel = purityLevel;
	this->description = description;
	this->materials = new ListaD<RawMaterial>();
}


std::ostream& operator<<( std::ostream& salida, const ProcessingLine& datos )
{
	char delim = ','; // separador 
	
	// imprime atribtos separados por delim
	salida << datos.description;
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<
