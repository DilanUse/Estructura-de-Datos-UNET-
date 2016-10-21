#ifndef PERSONAL_H
#define PERSONAL_H

#include <string>
#include <iostream>
#include "Vehiculo.h"


// clase que representa al personal de lavado
class Personal
{
	// función para sobrecargar operador de inserción de flujo
	friend std::ostream& operator<<( std::ostream&, const Personal& );
	
	
	public:
		int id; // identificador
		int ganancias; // ganancias del personal 
		std::string nombre; // nombre del personal
		Vehiculo* vehAsignado; // vehiculo asignado al lavador
		
		
		Personal(); // constructor predeterminado
		Personal(int, std::string ); // constructor parametrico
		bool operator==( const Personal& ); // sobrecarga el operador de igualdad
		bool operator<( const Personal& ); // sobrecarga el operador relacional menor que
		bool operator>( const Personal& ); // sobrecarga el operador relacional mayor que
}; // fin del la clase personal

#endif
