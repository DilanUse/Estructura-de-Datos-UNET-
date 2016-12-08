/**
 *	@Autor: Dilan Useche
 *	@Date: 24/4/2016
 *	@Release: 27/04/2016
 *	@Version: 1.0
 */

#ifndef CAMINO_H
#define CAMINO_H


#include "ListaD.h"
#include "Vertice.h"
#include <iostream>



/**
 *	@brief representacion de un Camino para un Grafo que contiene
 *	una ListaD en orden de los Vertices del Camino en el Grafo
 */
class Camino
{
	// función para sobrecargar operador de inserción de flujo
	friend std::ostream& operator<<( std::ostream&, const Camino& );
	private:
		static int id_static; // identificador compartido de Caminos 
		int id; // identificador de cada Camino
		int vertices; // cantidad de vertices en el camino
		double longitud; // longitud del camino ( peso de las aristas entre los vertices)
	public:
		ListaD<Vertice>* lista_vertices; // lista de vertices del camino
		Camino(); // constructor 
		~Camino(); // destructor
		double getLongitud() const; // retorna la longitud del Camino
		int getVertices() const; // retorna la cantidad de vertices en el Camino
		void actualizar(); // actualiza el Camino
		bool eliminarListaVerticesDesde( Vertice* ); // elimina en la lista de Vertices a partir del especificado
		bool iguales( Camino*, bool opuesto = false ) const; // determina si dos caminos son iguales
		bool operator==( const Camino& ); // sobrecarga el operador de igualdad
		bool operator<( const Camino& ); // sobrecarga el operador 
		bool operator>( const Camino& ); // sobrecarga el operador
}; // fin de Camino

#endif
