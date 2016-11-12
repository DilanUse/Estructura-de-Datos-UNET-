#ifndef TIPOOPERACION_H
#define TIPOOPERACION_H

#include "ColaD.h"
#include "Operacion.h"
#include <iostream>

class TipoOperacion
{

	
		// funci�n para sobrecargar operador de inserci�n de flujo
	friend std::ostream& operator<<( std::ostream&, const TipoOperacion& );
	
	public:
		char tipo; 
		ColaD<Operacion>* colaOperacion;
		bool operator==( const TipoOperacion& ); // sobrecarga el operador de igualdad
		bool operator<( const TipoOperacion& ); // sobrecarga el operador relacional menor que
		bool operator>( const TipoOperacion& ); // sobrecarga el operador relacional menor que
		TipoOperacion(char);
	protected:
};

#endif
