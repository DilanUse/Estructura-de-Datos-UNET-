/**
 *	@Autor: Dilan Useche
 *	@Date: 2/27/2016
 *	@Release: 10/3/2016
 *	@Version: 1.1
 */

#ifndef COLAD_H
#define COLAD_H

#include <cstdlib>
#include "Nodo.h"


/**
 *	@brief representacion de una estructura de datos lineal
 *	dinamica tipo cola, compatible con cualquier tipo de dato
 */
template<class T>
class ColaD
{
	private:
		Nodo<T>* frente; // frente de la ColaD
		Nodo<T>* fin; // fin de la ColaD
		
	public:
		/**
		 *	@brief inicializa la ColaD, asiganando a NULL
		 * 	el frente y el fin de la misma
		 *	@since 0.1
		 */
		ColaD(){ this->frente = this->fin = NULL; }
		Nodo<T>* getFrente() const; // retorna frente de la ColaD
		Nodo<T>* getFin() const; // retorna el fin de la ColaD
		bool isVacia() const; // determina si la ColaD esta vacia
		bool agregar( T* ); // agrega un nuevo Nodo a la ColaD
		bool eliminar(); // elimina el Nodo en el frente de la ColaD
		bool eliminarCola(); // elimina la ColaD
		void imprimir() const; // imprime la ColaD en el flujo std de salida	
		
		
}; // fin de ColaD


/**
 *	@brief retorna apuntador al Nodo en el frente de la ColaD
 *	@since: 1.1
 *	@return Nodo<T>* apuntador al frente de la ColaD
 */
 template<class T> Nodo<T>* ColaD<T>::getFrente() const
 {
	return this->frente; 
 } // fin de getFrente
 
 
/**
 *	@brief retorna apuntador al Nodo en el fin de la ColaD
 *	@since: 1.1
 *	@return Nodo<T>* apuntador al fin de la ColaD
 */
 template<class T> Nodo<T>* ColaD<T>::getFin() const
 {
	return this->fin; 
 } // fin de getFin

/**
 *	@brief determina si la ColaD esta vacia
 *	@since: 0.1
 *	@return bool true ColaD vacia, de lo contrario false
 */
template<class T> bool ColaD<T>::isVacia() const
{
	return !this->frente; // retorna desicion 
} // fin de isVacia


/**
 *	@brief agrega un nuevo elementos de datos o informacion 
 *	a la ColaD, creando un nuevo Nodo y asignanando a su 
 *	campo info el elemento de informacion especificado
 *	@since: 0.1
 *	@param T* campo de informacion del nuevo Nodo
 *	@return bool true exito al agregar, de lo contrario false,
 *	debido a falta de memoria
 */
template<class T> bool ColaD<T>::agregar( T* info )
{
	Nodo<T>* nuevo = new Nodo<T>( info ); // crea nuevo Nodo
	
	
	if( nuevo ) // si la asignacion de memoria tuvo exito
	{
		if( this->isVacia() ) // si la ColaD esta vacia
			this->frente = this->fin = nuevo; // frente y fin a nuevo
		else // si la ColaD no esta vacía
		{
			this->fin->setLink_pre( nuevo ); // pre de fin a nuevo
			this->fin = nuevo; // fin ahora sera nuevo
		} // fin del if...else
	}
	else // de lo contrario, no habia memoria suficiente
		return false; // fallo al agregar por falta de memoria
		
	return true; // exito al agregar
} // fin de agregar


/**
 *	@brief elimina el Nodo actual en el frente de ColaD
 *	@since: 0.1
 *	@return bool true exito al eliminar, false si la ColaD
 *	esta vacia
 */
template<class T> bool ColaD<T>::eliminar()
{
	Nodo<T>* eliminar; // Nodo a eliminar de la ColaD
	
	
	if( !this->isVacia() ) // si la colaD no esta vacia
	{
		eliminar = this->frente; // eliminar sera el frente
		
		
		if( this->frente == this->fin ) // si frente y fin son el mismo Nodo
			this->frente = this->fin = NULL; // frente y fin seran NULL
		else // si no son el mimos Nodo( mas de un Nodo en la ColaD)
			this->frente = this->frente->getLink_pre(); // frente ahora sera el predecesor del mismo 
			
			
		delete eliminar; // elimina Nodo en el tope, liberando memoria
	}
	else // de lo contrario, esta vacia la ColaD
		return false; // ColaD vacia
		
	return true; // exito al eliminar
} // fin de eliminar


 /**
 *	@brief elimina todos los Nodos de la ColaD, vaciandola
 *	@since: 1.0
 *	@return bool true exito al eliminar, false si la ColaD
 *	esta vacia
 */
template<class T> bool ColaD<T>::eliminarCola()
{
	Nodo<T>* eliminar; // Nodo a eliminar de la ColaD
	
	
	if( !this->isVacia() ) // si la colaD no esta vacia
	{
		// mientras frente no sea NULL
		while( frente )
		{
			eliminar = this->frente; // eliminar sera el frente
			this->frente = this->frente->getLink_pre(); // frente ahora sera el predecesor del mismo 	
			delete eliminar; // elimina Nodo en el tope, liberando memoria
		} // fin del while
		
		this->fin = this->frente; // fin sera el frente(NULL)
	}
	else // de lo contrario, esta vacia la ColaD
		return false; // ColaD vacia
		
	return true; // exito al eliminar
} // fin de eliminar


/**
 *	@brief imprime la ColaD en el flujo std de salida,
 *	si la ColaD esta vacia, se imprime "NULL"
 *	@since: 0.1
 */
template<class T> void ColaD<T>::imprimir() const
{
	Nodo<T>* recor = this->frente; // El recorrido empezara en el frente de la ColaD
	
	
	while( recor ) // mientras no se salga de la ColaD
	{
		std::cout << recor->getInfo() << "-->"; // imprime Nodo
		recor = recor->getLink_pre(); // recor pasa a su predecesor
	} // end while
	
	
	std::cout << "NULL" << std::endl; // imprime enlace del ultimo Nodo
} // fin de imprimir

#endif
