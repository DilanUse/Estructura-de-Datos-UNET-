#ifndef OPERACION_H
#define OPERACION_H

#include <iostream>

class Operacion
{
	public:
		char tipo; 
		int operando1;
		int operando2;
		
		
				// función para sobrecargar operador de inserción de flujo
		friend std::ostream& operator<<( std::ostream&, const Operacion& );
		Operacion( int op1, int op2, char t);
		int getOperacion();
	protected:
};

#endif
