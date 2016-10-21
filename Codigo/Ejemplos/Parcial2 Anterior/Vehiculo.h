#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
#include <iostream>

class Vehiculo
{
		// funci�n para sobrecargar operador de inserci�n de flujo
	friend std::ostream& operator<<( std::ostream&, const Vehiculo& );
	
	
	public:
		std::string placa; // placa del vehiculo
		std::string marca; // marca del vehiculo
		
		Vehiculo(); // constructor por defecto
		Vehiculo( std::string, std::string ); // constructor parametrico	
}; // fin de la clase Vehiculo

#endif
