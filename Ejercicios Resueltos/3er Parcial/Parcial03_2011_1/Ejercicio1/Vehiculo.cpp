#include "Vehiculo.h"

Vehiculo::Vehiculo( string pla, string des )
{
	this->placa = pla; 
	this->descripcion = des;
}


ostream& operator<<( ostream& salida, const Vehiculo& datos )
{

	// imprime atribtos separados por delim
	salida << datos.placa;
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<


bool Vehiculo::operator<( const Vehiculo& datos )
{
	return ( this->placa < datos.placa );
} // fin del operador<


bool Vehiculo::operator>( const Vehiculo& datos )
{
	return ( this->placa > datos.placa );
} // fin del operador<


bool Vehiculo::operator==( const Vehiculo& datos )
{
	return ( this->placa == datos.placa ); // retorna desición  
} // fin de operator==
