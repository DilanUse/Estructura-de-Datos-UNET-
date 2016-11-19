#include "TipoOperacion.h"

using namespace std;

TipoOperacion::TipoOperacion( char t )
{
	this->tipo = t;
	this->colaOperacion = new ColaD<Operacion>();
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
ostream& operator<<( ostream& salida, const TipoOperacion& datos )
{
	char delim = ','; // separador 
	
	// imprime atribtos separados por delim
	salida << "(" << datos.tipo << ")";
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<


/**
 *	@brief sobrecarga el operador relacional menor que,
 *	 comparandn dos objetos Datos por su nombre
 *	@since 0.4.1
 *	@param Datos& datos a comparar 
 *	@return bool true si el nombre del objeto que hizo la llamada
 *	es menor al objeto del parámetro
 */
bool TipoOperacion::operator<( const TipoOperacion& datos )
{
	return false;
} // fin del operador<

/**
 *	@brief sobrecarga el operador de igualdad, comparando 
 *	dos objetos Datos por su nombre
 *	@since 0.4.1
 *	@param Datos& datos a comparar 
 *	@return bool true si el nombre de ambos Datos es igual, de 
 *	lo contrario false
 */
bool TipoOperacion::operator==( const TipoOperacion& datos )
{
	return (this->tipo == datos.tipo); // retorna desición  
} // fin de operator==


bool TipoOperacion::operator>( const TipoOperacion& datos )
{
	return false;
} // fin del operador<
