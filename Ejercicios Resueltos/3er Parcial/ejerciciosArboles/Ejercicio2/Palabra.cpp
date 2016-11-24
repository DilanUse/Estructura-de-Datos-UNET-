#include "Palabra.h"

Palabra::Palabra( string pal )
{
	this->palabra = pal; 
	this->ocurrencia = 1;
}


ostream& operator<<( ostream& salida, const Palabra& datos )
{

	// imprime atribtos separados por delim
	salida << datos.palabra << ": " << datos.ocurrencia;
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<



bool Palabra::operator<( const Palabra& datos )
{
	return ( this->palabra < datos.palabra );
} // fin del operador<

bool Palabra::operator>( const Palabra& datos )
{
	return ( this->palabra > datos.palabra );
} // fin del operador<


bool Palabra::operator==( const Palabra& datos )
{
	return ( this->palabra == datos.palabra); // retorna desición  
} // fin de operator==

