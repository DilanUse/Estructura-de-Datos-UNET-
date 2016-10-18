/**
 *	@Autor: Dilan Useche
 *	@Date: 2/27/2016
 *	@Release: 10/3/2016
 *	@Version: 1.1
 */

#ifndef PILAD_H
#define PILAD_H

#include <cstdlib>
#include <iostream>
#include "Nodo.h"

/**
 *	@brief representacion de una estructura de datos lineal
 *	dinamica tipo pila, compatible con cualquier tipo de dato
 */
template<class T>
class PilaD
{
	private:
		Nodo<T>* tope; // enlance al tope de la PilaD
		
	public:
		/**
 		 *	@brief inicializa tope de la PilaD a NULL
		 *	@since: 0.1
		 */
		PilaD(){ tope = NULL; }
		bool isVacia() const; // determina si la PilaD esta vacia
		Nodo<T>* getTope() const; // retorna apuntador al Nodo tope
		bool agregar( T* ); // agrega un nuevo Nodo a la PilaD
		bool eliminar(); // elimina el Nodo en el tope de la PilaD
		bool eliminarPila(); // elimina la PilaD
		void imprimir() const; // imprime la PilaD en el flujo std de salida	
}; // fin del encabezado de la PilaD


/**
 *	@brief retorna apuntador al Nodo en el tope de la Pila
 *	@since: 1.1
 *	@return Nodo<T>* apuntador al Nodo tope
 */
template<class T> Nodo<T>* PilaD<T>::getTope() const
{
	return this->tope;
} // fin de getTope

/**
 *	@brief determina si la PilaD esta vacia
 *	@since: 0.1
 *	@return bool true PilaD vacia, de lo contrario false
 */
template<class T> bool PilaD<T>::isVacia() const
{
	return !this->tope; // retorna desicion 
} // din de isVacia


/**
 *	@brief agrega un nuevo elementos de datos o informacion 
 *	a la PilaD, creando un nuevo Nodo y asignanando a su 
 *	campo info el elemento de informacion especificado
 *	@since: 0.1
 *	@param T* campo de informacion del nuevo Nodo
 *	@return bool true exito al agregar, de lo contrario false,
 *	debido a falta de memoria
 */
template<class T> bool PilaD<T>::agregar( T* info )
{
	Nodo<T>* nuevo = new Nodo<T>( info ); // crea nuevo Nodo
	
	
	if( nuevo ) // si la asignacion de memoria tuvo exito
	{
		nuevo->setLink_pre( tope ); // predecesor de nuevo sera el tope
		tope = nuevo; // tope ahora sera el nuevo Nodo
	}
	else // de lo contrario, no habia memoria suficiente
		return false; // fallo al agregar por falta de memoria
		
	return true; // exito al agregar
} // fin de agregar


/**
 *	@brief elimina el Nodo actual en el tope de la PilaD 
 *	@since: 0.1
 *	@return bool true exito al eliminar, false si la PilaD 
 *	esta vacia
 */
template<class T> bool PilaD<T>::eliminar()
{
	Nodo<T>* eliminar; // Nodo a eliminar de la PilaD
	
	
	if( !this->isVacia() ) // si la PilaD no esta vacia
	{
		eliminar = tope; // eliminar sera el tope
		tope = tope->getLink_pre(); // tope ahora sera el predecesor de el mismo 
		delete eliminar; // elimina Nodo en el tope, liberando memoria
	}
	else // de lo contrario, esta vacia
		return false; // lista vacia
		
	return true; // exito al eliminar
} // fin de eliminar


/**
 *	@brief elimina todos los Nodos de la PilaD, vaciandola
 *	@since: 1.0
 *	@return bool true exito al eliminar, false si la PilaD 
 *	esta vacia
 */
template<class T> bool PilaD<T>::eliminarPila()
{
	Nodo<T>* eliminar; // Nodo a eliminar
	
	
	// si la PilaD no esta vacia
	if( !this->isVacia() ) // si la PilaD no esta vacia
	{
		// mientras el tope no sea NULL
		while( tope )
		{
			eliminar = tope;
			tope = tope->getLink_pre(); // tope ahora sera el predecesor de el mismo 
			delete eliminar; // elimina Nodo en el tope, liberando memoria
		} // fin del while
	}
	else // de lo contrario, esta vacia
		return false; // lista vacia
		
	return true; // exito al eliminar
} // fin de eliminar


/**
 *	@brief imprime la PilaD en el flujo std de salida,
 *	si la PilaD esta vacia, se imprime "NULL"
 *	@since: 0.1
 */
template<class T> void PilaD<T>::imprimir() const
{
	Nodo<T>* recor = tope; // El recorrido empezara en el tope de la PilaD
	
	
	while( recor ) // mientras no se salga de la pila
	{
		std::cout << recor->getInfo() << "-->"; // imprime Nodo
		recor = recor->getLink_pre(); // recor pasa a su predecesor
	} // end while
	
	
	std::cout << "NULL" << std::endl; // imprime enlace del ultimo Nodo
} // fin de imprimir

#endif
