/**
 *	@Autor: Dilan Useche
 *	@Date: 24/4/2016
 *	@Release: 27/04/2016
 *	@Version: 1.0
 */
 

#ifndef VERTICE_H
#define VERTICE_H

#include <string>
#include <iostream>
#include "ListaD.h"


/**
 *	@brief representacion de un Vertice de un Grafo
 *	que contiene la longitud de su arista con el Vertice 
 *	anterior adyacente y el nombre o identificador del Vertice
 */
class Vertice
{
	// función para sobrecargar operador de inserción de flujo
	friend std::ostream& operator<<( std::ostream&, const Vertice& );
	private:
		// longitud de la arista entre este Vertice y 
		// su Vertice anterior adyacente
		double longitud_arista; 
		std::string identificador; // identificador asociado al Vertice
		
	public:
		ListaD<Vertice>* vertices_adyacentes; // ListaD de vertices adyacentes
		
		Vertice( std::string, double longitud = 0 ); // construtor de Vertice
		double getLongitudArista() const; // devuelve la longitud de la aritsa
		std::string getIdentificador() const; // retorna identificador del Vertice
		bool operator==( const Vertice& ); // sobrecarga el operador de igualdad
		bool operator<( const Vertice& ){} // sobrecarga el operador 
		bool operator>( const Vertice& ){} // sobrecarga el operador
}; // fin de Vertice


#endif
