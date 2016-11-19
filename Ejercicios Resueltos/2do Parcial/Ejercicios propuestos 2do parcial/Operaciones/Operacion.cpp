#include "Operacion.h"


using namespace std;

Operacion::Operacion( int op1, int op2, char t)
{
	this->operando1 = op1;
	this->operando2 = op2,
	this->tipo = t;
}



int Operacion::getOperacion()
{
	if( this->tipo == '+')
		return this->operando1 + this->operando2;
	else if( this->tipo == '-' )
		return this->operando1 - this->operando2;
	else if( this->tipo == '*')
		return this->operando1 * this->operando2;
	else
		return this->operando1 / this->operando2;
}

/**
 *	@brief sobrecarga el operador de inserción de flujo 
 *	un objeto de tipo Datos, y lo representa como una cadena
 *	con todos sus atributos separados por una coma 
 *	@since 0.1
 *	@param ostream& objeto de flujo de salida
 *	@param Datos& objeto de la clase
 *	@return ostream& objeto del flujo de salida 
 */
ostream& operator<<( ostream& salida, const Operacion& datos )
{
	char delim = ','; // separador 
	
	// imprime atribtos separados por delim
	salida << datos.operando1 << datos.tipo << datos.operando2;
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<
