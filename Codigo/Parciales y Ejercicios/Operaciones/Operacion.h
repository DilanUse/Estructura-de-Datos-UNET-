#ifndef OPERACION_H
#define OPERACION_H

#include <iostream>

class Operacion
{
	public:
		char tipo; 
		int operando1;
		int operando2;
		
		
				// funci�n para sobrecargar operador de inserci�n de flujo
		friend std::ostream& operator<<( std::ostream&, const Operacion& );
		Operacion( int op1, int op2, char t);
		int getOperacion();
	protected:
};

#endif
