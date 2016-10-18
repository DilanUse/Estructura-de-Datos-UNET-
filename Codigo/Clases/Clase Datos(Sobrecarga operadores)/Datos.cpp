#include "Datos.h"

using namespace std;

/**
 *	@brief inicializa el objeto Datos
 *	@since 0.1
 *	@param string nombre
 *	@param int edad
 *	@param char sexo
 *	@param double promedio
 */
Datos::Datos( std::string n, int e, char s, double p )
{
	this->nombre = n;
	this->edad = e;
	this->sexo = s;
	this->promedio = p;
} // fin del constructor 


/**
 *	@brief sobrecarga el operador de inserción de flujo 
 *	un objeto de tipo Datos, y lo representa como una cadena
 *	con todos sus atributos separados por una coma 
 *	@since 0.1
 *	@param ostream& objeto de flujo de salida
 *	@param Datos& objeto de la clase
 *	@return ostream& objeto del flujo de salida 
 */
ostream& operator<<( ostream& salida, const Datos& datos )
{
	char delim = ','; // separador 
	
	// imprime atribtos separados por delim
	salida << datos.nombre << delim << datos.edad << delim << 
	datos.sexo << delim << datos.promedio;
		
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
bool Datos::operator<( const Datos& datos )
{
	return ( this->nombre < datos.nombre );
} // fin del operador<

/**
 *	@brief sobrecarga el operador de igualdad, comparando 
 *	dos objetos Datos por su nombre
 *	@since 0.4.1
 *	@param Datos& datos a comparar 
 *	@return bool true si el nombre de ambos Datos es igual, de 
 *	lo contrario false
 */
bool Datos::operator==( const Datos& datos )
{
	return ( this->nombre == datos.nombre); // retorna desición  
} // fin de operator==

 
