#include "Vertice.h"
using namespace std;


/**
 *	@brief inicializa el Vertice
 *	@since 1.0
 *	@param string identificador del Vertice
 *	@param longitud de la arista del Vertice
 */
Vertice::Vertice( string identificador, double longitud )
{
	// crea la lista de Vertices adyacentes
	this->vertices_adyacentes = new ListaD<Vertice>();
	this->identificador = identificador; // asigna identificador
	this->longitud_arista = longitud; // asigna longitud_arista
} // fin del contsructor


/**
 *	@brief devuelve la longitud de la arista del Vertice
 *	@since 1.0
 *	@return double longitud arista
 */
double Vertice::getLongitudArista() const 
{
	return this->longitud_arista; // retorna longitud
} // fin de getLongitudArista


/**
 *	@brief devuelve identificador del Vertice
 *	@since 1.0
 *	@return string identificador del Vertice
 */
string Vertice::getIdentificador() const 
{
	return this->identificador; // retorna campo info
} // fin de getIdentificador


/**
 *	@brief sobrecarga el operador de insercion de flujo para 
 *	imprimir una represetanción de un Vertice en el flujo std
 *	de salida
 *	@param ostream& flujo de salida a ser usado
 *	@param const Vertice& Vertice a ser impreso en el flujo de salida
 *	@since 1.0
 *	@return ostrem& flujo de salida usado(permite usar el operador en cascada)
 */
ostream& operator<<( ostream& salida, const Vertice& datos )
{
	// imprime identificador del vertice
	salida << datos.identificador;
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<


/**
 *	@brief sobrecarga el operador relacional de igualdad
 *	el cual compara el identificador en los Vertices
 *	@param Vertice& operando derecho del operador
 *	@since 1.0
 *	@return bool true si el Vertice(operando) izquierdo tiene
 *	el mismo identificador que el Vertice(operando) derecho
 */
bool Vertice::operator==( const Vertice& datos )
{
	return ( this->identificador == datos.identificador ); // retorna desición  
} // fin de operator==




