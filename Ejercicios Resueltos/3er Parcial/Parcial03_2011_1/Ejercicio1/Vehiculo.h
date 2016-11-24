#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
#include <iostream>
using namespace std;


class Vehiculo
{
		friend std::ostream& operator<<( std::ostream&, const Vehiculo& );
	public:
		string placa;
		string descripcion;
		Vehiculo( string, string );
		
		bool operator==( const Vehiculo& ); // sobrecarga el operador de igualdad
		bool operator<( const Vehiculo& ); // sobrecarga el operador relacional menor que
		bool operator>( const Vehiculo& ); // sobrecarga el operador relacional menor que
		
		
};

#endif
