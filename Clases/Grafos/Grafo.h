/**
 *	@Autor: Dilan Useche
 *	@Date: 24/4/2016
 *	@Release:
 *	@Version: 1.1
 */


#ifndef GRAFO_H
#define GRAFO_H

#include "ListaD.h"
#include "Vertice.h"
#include "Camino.h"
#include "Nodo.h"
#include "Archivo.h"
#include <iostream>
#include <string>
#include <cstdlib>


/**
 *	@brief representacion de una estructura de datos no lineal
 *	tipo Grafo, que puede ser, dirigido o no, y además, puede ser,
 *	ponderado o no, el Grafo siempre sera conexo, en caso de que sea
 *	dirigido, se garantiza que el Grafo es al menos debilmente conexo
 */
class Grafo {
	private:
		bool DIRIGIDO; // determina si el Grafo es dirigido
		bool PONDERADO; // determina si el Grafo es ponderado
		float longitud; // longitud de todas las aristas del grafo

		void inicializar( bool dirigido = true, bool ponderado = false ); // inicializa el Grafo
		bool agregar_camino( Nodo<Camino>*, Nodo<Vertice>* ); // agrega Vertices a la lista de Caminos del Grafo
		void actualizarCaminos(); // actualiza los Caminos de la lista de Caminos
		void buscarCaminos_MinMaxVertices( bool min = true ); // busca los Caminos con menor o mayor longitud de vertices
		void buscarCaminos_MinMaxLongitud( // busca los Caminos de mayor o
		    bool min = true ); // menor longitud en el Grafo
		void buscarCaminosSinVertice( Vertice* ); // busca los caminos sin un vertice dado 
	public:
		ListaD<Vertice>* lista_adyacencia; // lista de adyacencia que representa al Grafo
		ListaD<Camino>* lista_caminos; // lista de Caminos del Grafo

		Grafo(); // constructor predeterminado
		Grafo( bool, bool ); // constructor con dos argumentos
		Grafo( std::string, char, bool, bool ); // constructor con cuatro argumentos
		bool isDirigido() const; // devuelve determinación acerca de si el Grafo es dirigido o no
		bool isPonderado() const; // devuelve determinación acerca de si el Grafo es ponderado o no
		int getNumeroVertices() const; // retorna el numero de Vertices del Grafo
		float getLongitud() const; // retorna la longitud de todas las aristas del grafo
		bool agregar( Vertice*, Vertice* ); // agrega Vertices a la lista de adyacencia del Grafo
		void BuscarCaminos(); // Busca todos los Caminos en el Grafo
		void buscarCaminos_maxVertices(); // busca Caminos con la mayor cantidad de Vertices
		void buscarCaminos_MinMaxLongitud_Grafo( bool min ); // busca los caminos con mayor o menor longitud en todo el grafo
		bool buscarCaminos_MinMaxVertices_Vertices( // busca los Caminos con mayor o menor numero de vertices
		    Vertice*, Vertice*, bool min = true, Vertice* inter = NULL ); // entre dos Vertices Dados, obviando un vertice intermedio si lo hay
		bool buscarCaminos_MinMaxLongitud_Vertices( // busca los Caminos de mayor o menor longitud
		    Vertice*, Vertice*, bool min = true, Vertice* inter = NULL ); // entre dos Vertices Dados
		bool conectividad( Vertice*, Vertice* ); // determina si hay conectividad entre un par de Vertices dados
		void imprimirListaAdyacencia() const; // imprime la lista de adyacencia
		void imprimirListaCaminos() const; // imprime la lista de caminos
		//	void buscarCaminosLargos();
}; // fin de grafo


#endif
