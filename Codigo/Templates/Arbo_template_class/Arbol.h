/**
 *	@Autor: Dilan Useche
 *	@Date: 10/4/2016
 *	@Release: 24/4/2016
 *	@Version: 1.0
 */


#ifndef ARBOL_H
#define ARBOL_H


#include <iostream>
#include <cstdlib>
#include "NodoA.h"


/**
 *	@brief representacion de una estructura de datos no lineal 
 *	tipo Arbol, que puede representar cualquiera de 
 *  estos dos tipos de Arbol: 1)Binario de busquerda; 2)AVL;
 *	El arbol además es compatible con cualquier tipo de dato.
 */
template<class T>
class Arbol
{
	private:
		NodoA<T>* raiz; // apuntador a la raiz del Arbol
		bool AVL; // determina si el Arbol es AVL
		int altura; // altura del Arbol 
		NodoA<T>* desequilibrado; // NodoA desequilibrado en el Arbol
		NodoA<T>* desequilibrado_padre; // NodoA padre del NodoA desequlibrado
		void actualizar( NodoA<T>*, int nivel = 0 ); // actualiza el Arbol y todos sus nodos
		void equilibrar(); // equilibra el Arbol para que sea un Arbol AVL
		NodoA<T>* rotacionSD( NodoA<T>* ); // realiza rotación simple a la derecha de un NodoA
		NodoA<T>* rotacionSI( NodoA<T>* ); // realiza rotación simple a la izquierda de un NodoA
		NodoA<T>* rotacionCD( NodoA<T>*, NodoA<T>* ); // realiza rotación compuesta a la derecha de un NodoA
		NodoA<T>* rotacionCI( NodoA<T>*, NodoA<T>* ); // realiza rotación compuesta a la izquierda de un NodoA
	public:
		Arbol( bool avl = false )
		{
			this->raiz = this->desequilibrado = this->desequilibrado_padre = NULL;
			this->AVL = avl; 
			this->altura = 0;
		}
		NodoA<T>* getRaiz() const; // retorna la raiz del Arbol
		int getAltura() const; // retorna la altura del Arbol
		bool isAVL() const; // retorna determinación acerca de si el Arbol es AVL
		bool isVacio() const; // determina si el Arbol esta vacio
		NodoA<T>* buscar( T*, NodoA<T>** antes = NULL ) const; // busca elemento en el Arbol 
		int agregar( T* ); // agrega un nuevo NodoA al Arbol
		int eliminar( T* ); // elimina un NodoA del Arbol
		void eliminarArbol( NodoA<T>* ); // elimina todos los elementos del Arbol
		void imprimir( NodoA<T>* ) const; // imprime la ListaD en el flujo std de salida
//		void imprimir( bool ) const; // imprime la ListaD en el flujo std de salida
}; // fin de Arbol


/**
 *	@brief retorna un apuntador a la raiz del Arbol
 *	@since: 1.0
 *	@return NodoA<T>* apuntador a la raiz del Arbol
 */
template<class T> NodoA<T>* Arbol<T>::getRaiz() const
{
	return this->raiz;
} // fin de getRaiz


/**
 *	@brief retorna altura del Arbol
 *	@since: 1.0
 *	@return int altura de la raiz del Arbol
 */
template<class T> int Arbol<T>::getAltura() const
{
	return this->altura;
} // fin de getAltura


/**
 *	@brief retorna el atributo de tipo de Arbol AVL
 *	@since: 1,0
 *	@return bool atributo AVL del ARbol
 */
template<class T> bool Arbol<T>::isAVL() const
{
	return this->AVL;
} // fin de isAVL


/**
 *	@brief determina si el Arbol esta vacio
 *	@since: 1.0
 *	@return bool true Arbol vacio, de lo contrario false
 */
template<class T> bool Arbol<T>::isVacio() const
{
	return !this->raiz; 
} // fin de isVacio


/**
 *	@brief busca el elemento de información especificado en el Arbol
 *	@param T* elemento de información a buscar
 * 	@param Nodo<T>** apuntador de puntero al antes(Solo util para cuando se quiere agregar)
 *	@since: 1.0
 *	@return Nodo<T>* apuntador al campo info buscado, Si el campo info a buscar no se encuentra o 
 *	el Arbol esta vacio, el apuntador sera NULL o será false
 */
template<class T> NodoA<T>* Arbol<T>::buscar( T* info, NodoA<T>** antes ) const
{
	NodoA<T>* recor = this->raiz; // recor empezara en la raiz
	
	
	// mientras recor tenga dirección
	while( recor )
	{
		// si antes apunta a una dirección valida( existe )
		if( antes )		
			*antes = recor; // antes sera ahora recor ( en agregar también cambiara antes)
			
		
		// si consigo el info especificado
		if( *info == *recor->getInfo() ) // retorno apuntador
			return recor; 
		else if( *info < *recor->getInfo() ) // si no, si es menor
			recor = recor->getLink_hi(); // recor sera ahora el hijo izquierdo
		else // si no, es mayor a recor
			recor = recor->getLink_hd(); // recor ahora sera el hijo derecho
			
			
		// si recor tiene dirección y consigo el info especificado
		if( recor && *info == *recor->getInfo() ) // retorno apuntador
			return recor; 
	} // fin del while
	
	return NULL; // retorna NULL 
} // fin de buscar


/**
 *	@brief agrega un nuevo elemento de datos o información al Arbol, 
 *	creando un nuevo NodoA y asignanando a su  campo info el elemento de 
 *	informacion especificado. Si el elemento es repetido, no se agregara al Arbol 
 *	@since: 1.0
 *	nota: para evitar la repetición la funcion depende completamente de la sobrecarga del 
 *	operador de igualdad en la clase que representa el campo info, la repetición se evitara 
 *	de acuerdo a el tipo o atributo de comparación en la sobrecarga de la clase   
 *	@return int 1 exito al agregar; 0 fallo al agregar por falta de memoria; -1 no se agrego
 * 	debido a que el elemento ya existia en el Arbol
 */
template<class T> int Arbol<T>::agregar( T* info )
{
	NodoA<T>* nuevo = new NodoA<T>( info ); // crea nuevo NodoA
	NodoA<T>* recor; // recorrido
	NodoA<T>* antes = NULL; // antes sera NULL
	 
	
	
	if( nuevo ) // si la asignacion de memoria tuvo exito
	{
		// si el arbol esta vacio
		if( this->isVacio() )
			raiz = nuevo; // raiz sera nuevo
		else
		{
			recor = buscar( info, &antes ); // busco info
			
			
			// si recor tiene dirección(ya existe el campo info)
			if( recor )
				return -1; // no se puede agregar repetido
			else
			{
				if( *info < *antes->getInfo() )
					antes->setLink_hi( nuevo );
				else
					antes->setLink_hd( nuevo );
			} // fin del if...else
			
			
			this->actualizar( this->raiz ); // actualizo Arbol
			this->altura = this->raiz->getAltura(); // actualizo altura del Arbol
			
			
			// mientras sea un Arbol AVL y exista un desequilibrio
			while( this->AVL && this->desequilibrado )
			{
				this->equilibrar();
				this->actualizar( this->raiz );
				this->altura = this->raiz->getAltura(); // actualizo altura del Arbol
			}
		} // fin del if...else
	} 
	else // de lo contrario, no habia memoria suficiente
		return 0; // fallo al agregar por falta de memoria
		
	return 1; // exito al agregar
} // fin de agregar


/**
 *	@brief elimina el NodoA con el campo info especificado
 *	@since: 1.0
 *	@param T* campo de información a eliminar
 *	@return int 0 si no se pudo eliminar, debido a que el Arbol esta vacía;
 *	1 exito al eliminar; 404 si no se pudo eliminar, debido a que no se encontro el 
 *	elemento especificado 
 */
template<class T> int Arbol<T>::eliminar(  T* info )
{
	NodoA<T>* eliminar = NULL; // NodoA a eliminar
	NodoA<T>* eliminar_padre = NULL; // padre del NodoA a eliminar / padre de eliminar_sust
	NodoA<T>* eliminar_hijo = NULL; // hijo del NodoA a eliminar 
	NodoA<T>* eliminar_sust = NULL; // NodoA descendiente mayor o menor del NodoA a eliminar
	
	
	// si el Arbol no esta vacio
	if( !this->isVacio() )
	{
		// busco el NodoA a eliminar y su padre 
		eliminar = this->buscar( info, &eliminar_padre );
		
		
		// si no existe el NodoA a eliminar en el Arbol
		if( !eliminar )
			return 404; // no existe NodoA a eliminar 
			
		
		// si el NodoA a eliminar es una hoja
		if( eliminar->isHoja() )
		{				
			// si el NodoA a eliminar es la raiz y es una hoja
			if( eliminar == this->raiz ) // entonces es el unico NodoA en el Arbol
				this->raiz = NULL; // raiz será NULL(Arbol vacio)
			else
			{
				// si eliminar es el hijo izquierdo de su padre
				if( eliminar_padre->getLink_hi() == eliminar )
					eliminar_padre->setLink_hi( NULL );
				else // si no, es el hijo derecho
					eliminar_padre->setLink_hd( NULL );	
			} // fin del if...else
			
			delete eliminar; // elimino NodoA 
		} // si no, si el Nodo a eliminar tiene dos subArboles
		else if( eliminar->getLink_hd() && eliminar->getLink_hi() )
		{
			// identifico el NodoA descendiente mayor del subArbol izquierdo
			// del NodoA a eliminar 
			eliminar_sust = eliminar->getLink_hi(); // mayor sera hijo izquierdo de eliminar
			
			// mientras el mayor tenga un hijo derecho 
			while( eliminar_sust->getLink_hd() )
				eliminar_sust = eliminar_sust->getLink_hd();
				
				
			// encuentro padre del NodoA sustituto( mayor de los menores)
			this->buscar( eliminar_sust->getInfo(), &eliminar_padre );
			
			// copio campo info de sustituto en el NodoA a eliminar
			eliminar->setInfo( *eliminar_sust->getInfo() );
			
			// actualizo enlace del NodoA padre del sustituto
			// si el padre del sustituto tiene hijo izquierdo y es el sustituto
			if( eliminar_padre->getLink_hi() && eliminar_padre->getLink_hi() == eliminar_sust )
			{
				// si el sustituto es una hoja
				if( eliminar_sust->isHoja() )
					eliminar_padre->setLink_hi( NULL );
				else
					eliminar_padre->setLink_hi( eliminar_sust->getLink_hi() );
			}
			else // si no, entonces el hijo derecho es el sustituto 
			{
				// si el sustituto es una hoja
				if( eliminar_sust->isHoja() )
					eliminar_padre->setLink_hd( NULL );
				else
					eliminar_padre->setLink_hd( eliminar_sust->getLink_hi() );
			} // fin del if...else
			
			
			delete eliminar_sust; // elimino NodoA sustituto 
		}
		else // si no, entonces solo tiene un subArbol
		{
			// identifo NodoA hijo de eliminar
			if( eliminar->getLink_hi() )
				eliminar_hijo = eliminar->getLink_hi();
			else
				eliminar_hijo = eliminar->getLink_hd();
				
			
			// si el NodoA a eliminar es la raiz
			if( eliminar == this->raiz )
				this->raiz = eliminar_hijo; //raiz ahora sera el hijo de eliminar
			else
			{
				// actualizo enlace de Padre de eliminar a su hijo
				if( eliminar_padre->getLink_hi() == eliminar )
					eliminar_padre->setLink_hi( eliminar_hijo );
				else // si no, es el hijo derecho
					eliminar_padre->setLink_hd( eliminar_hijo );	
			} // fin del if...else
					
			delete eliminar; // elimino NodoA que deja de ser raiz 
		} // fin de los if...else anidados 	
	} 
	else
		return 0; // Arbol vacio


	// si el arbol existe 
	if( this->raiz )
	{
		this->actualizar( this->raiz ); // actualizo Arbol
		this->altura = this->raiz->getAltura();
		
		
		// mientras sea un Arbol AVL y exista un desequilibrio
		while( this->AVL && this->desequilibrado )
		{
			this->equilibrar();
			this->actualizar( this->raiz );
			this->altura = this->raiz->getAltura(); // actualizo altura del Arbol
		}
	} // fin del if
	else
		this->altura = 0;
	
	
	return 1; // exito al eliminar 
} // fin de eliminar


/**
 *	@brief elimina todos los NodoA del Arbol
 *	@since: 1.0
 */
template<class T> void Arbol<T>::eliminarArbol( NodoA<T>* recor )
{
	// si el NodoA recor tiene hijo por la izquierda 
	if ( recor->getLink_hi() ) // paso recursivo para actualizar al hijo por la izquierda
		actualizar( recor->getLink_hi() );
	
	// si el NodoA recor tiene hijo por la derecha
	if ( recor->getLink_hd() ) // paso recursivo para actualizar al hijo por la derecha
		actualizar( recor->getLink_hd() );
		
	
	// si recor es la raiz
	if( recor == this->raiz )
	{
		this->raiz = NULL;
		this->altura = 0;
		this->desequilibrado = this->desequilibrado_padre = NULL;
	} // fin del fi
	
	
	delete recor; // libero memoria del NodoA
} // fin de eliminarArbol


/**
 *	@brief actualiza el Arbol y todos sus nodos
 *	@since: 1.0
 *	@param NodoA<T>* NodoA a actualizar
 *	@param int nivel de profundidad en el arbol
 */
template<class T> void Arbol<T>::actualizar( NodoA<T>* recor, int nivel )
{
	// si el NodoA recor tiene hijo por la izquierda 
	if ( recor->getLink_hi() ) // paso recursivo para actualizar al hijo por la izquierda
		actualizar( recor->getLink_hi(), nivel + 1 );
	
	// si el NodoA recor tiene hijo por la derecha
	if ( recor->getLink_hd() ) // paso recursivo para actualizar al hijo por la derecha
		actualizar( recor->getLink_hd(), nivel + 1 );
	
		
	// actualizo los NodosA una vez que ya no tenga mas hijos por actualizar
	// si recor tiene hijo por la izquierda
	if ( recor->getLink_hi() ) // actulializo la altura de su subarbol izquierdo
		recor->setAltura_izq( recor->getLink_hi()->getAltura() + 1 );
	else // si no tiene
		recor->setAltura_izq( 0 ); // la altura del subArbol izquierdo es cero
	
	// si recor tiene hijo por la derecha 
	if ( recor->getLink_hd() ) // actualizo la altura de su subarbol derecho
		recor->setAltura_der( recor->getLink_hd()->getAltura() + 1 );
	else // si no tiene 
		recor->setAltura_der( 0 ); // la altura del subArbol derecho es cero
			 
	
	// actualizo altura del NodoA, factor de equilibrio y su nivel 
	recor->actualizar();
	recor->setNivel( nivel );
	
	
	// si no se ha detectado desequilibrio y  el Arbol es AVL y el NodoA esta desequilibrado
	if( !this->desequilibrado && this->AVL && ( recor->getFactorE() == 2 || recor->getFactorE() == -2 ) )
		this->desequilibrado = recor;
		
	// si hay desequilibrio y el NodoA desequilibrado es un hijo de recor 
	if( this->desequilibrado && ( recor->getLink_hi() == this->desequilibrado || 
		recor->getLink_hd() == this->desequilibrado ) )
		this->desequilibrado_padre = recor; 
} // fin de actualizar


/**
 *	@brief eqilibra el Arbol para que sea un Arbol AVL
 *	@since: 1.0
 */
template<class T> void Arbol<T>::equilibrar()
{
	NodoA<T>* raiz_subArbol; // nueva raiz del subArbol a equilibrar

	 
	// si el desequilibrio es hacia la derecha
	if( this->desequilibrado->getFactorE() == 2 )
	{
		// si el desequilibrio es simple
		if( this->desequilibrado->getLink_hd()->getFactorE() > 0 )
			raiz_subArbol = 
				this->rotacionSI( this->desequilibrado->getLink_hd() );
		else // si no entonces es compuesta 
			raiz_subArbol = this->rotacionCI( this->desequilibrado->getLink_hd(), 
				this->desequilibrado->getLink_hd()->getLink_hi() );
	}
	else // si no es a la izquierda
	{
		// si el desequilibrio es simple
		if( this->desequilibrado->getLink_hi()->getFactorE() < 0 )
			raiz_subArbol = 
				this->rotacionSD( this->desequilibrado->getLink_hi() );
		else // si no entonces es compuesta 
			raiz_subArbol = this->rotacionCD( this->desequilibrado->getLink_hi(), 
				this->desequilibrado->getLink_hi()->getLink_hd() );
	} // fin del if...else
	
	
	
	// si el NodoA desequilibrado tiene un padre
	if( this->desequilibrado_padre )
	{
		// si el NodoA desequilibrado es hijo derecho
		if( this->desequilibrado_padre->getLink_hd() == this->desequilibrado )
			this->desequilibrado_padre->setLink_hd( raiz_subArbol );
		else // si no, enotnces es el hijo izquierdo 
			this->desequilibrado_padre->setLink_hi( raiz_subArbol );
	} // fin del if
	
	
	// si el NodoA desequilibrado es la raiz 
	if( this->desequilibrado == this->raiz ) 
		this->raiz = raiz_subArbol; // raiz sera ahora la nueva raiz del subArbol
	
	
	this->desequilibrado = this->desequilibrado_padre = NULL; 
} // fin de equilibrar


/**
 *	@brief realiza rotación simple a la izquierda de un NodoA
 *	@since: 1.0
 *	@return NodoA<T>* apuntador a la nueva raiz del subArbol balanceado
 */
template<class T> NodoA<T>* Arbol<T>::rotacionSI( NodoA<T>* desequilibrado_hijo )
{
	this->desequilibrado->setLink_hd( desequilibrado_hijo->getLink_hi() );
	desequilibrado_hijo->setLink_hi( this->desequilibrado );
	return desequilibrado_hijo;
} // fin de rotacionSI
 
 
 /**
 *	@brief realiza rotación simple a la derecha de un NodoA
 *	@since: 1.0
 *	@return NodoA<T>* apuntador a la nueva raiz del subArbol balanceado
 */
template<class T> NodoA<T>* Arbol<T>::rotacionSD( NodoA<T>* desequilibrado_hijo )
{
	this->desequilibrado->setLink_hi( desequilibrado_hijo->getLink_hd() );
	desequilibrado_hijo->setLink_hd( this->desequilibrado );
	return desequilibrado_hijo;
} // fin de rotacionSD


 /**
 *	@brief realiza rotación compuesta a la izquierda de un NodoA
 *	@since: 1.0
 *	@return NodoA<T>* apuntador a la nueva raiz del subArbol balanceado
 */
template<class T> 
NodoA<T>* Arbol<T>::rotacionCI( NodoA<T>* desequilibrado_hijo, NodoA<T>* desequilibrado_nieto )
{
	this->desequilibrado->setLink_hd( desequilibrado_nieto->getLink_hi() );
	desequilibrado_nieto->setLink_hi( this->desequilibrado );
	desequilibrado_hijo->setLink_hi( desequilibrado_nieto->getLink_hd() );
	desequilibrado_nieto->setLink_hd( desequilibrado_hijo );
	
	return desequilibrado_nieto;
} // fin de rotacionCI


 /**
 *	@brief realiza rotación compuesta a la derecha de un NodoA
 *	@since: 1.0
 *	@return NodoA<T>* apuntador a la nueva raiz del subArbol balanceado
 */
template<class T> 
NodoA<T>* Arbol<T>::rotacionCD( NodoA<T>* desequilibrado_hijo, NodoA<T>* desequilibrado_nieto )
{
	desequilibrado_hijo->setLink_hd( desequilibrado_nieto->getLink_hi() );
	desequilibrado_nieto->setLink_hi( desequilibrado_hijo );
	this->desequilibrado->setLink_hi( desequilibrado_nieto->getLink_hd() );
	desequilibrado_nieto->setLink_hd( this->desequilibrado );
	
	return desequilibrado_nieto;
} // fin de rotacionCI


/**
 *	@brief imprime el Arbol en el flujo std de salida,
 *	 Si el Arbol esta vacio, se imprime "NULL"
 *	@since: 1.0
 *	@param NodoA<T>* NodoA a imoprimir
 */
template<class T> void Arbol<T>::imprimir( NodoA<T>* recor ) const
{
	// si recor es NULL
	if( !recor )
	{
		std::cout << "NULL" << std::endl;
		return;
	} // fin del if
		
		
	// si el NodoA recor tiene hijo por la izquierda 
	if ( recor->getLink_hi() ) // paso recursivo para actualizar al hijo por la izquierda
		imprimir( recor->getLink_hi() );
		
		
	for( int i = 0; i < recor->getNivel(); i++ )
		std::cout << "       ";
		
	
	std::cout << *recor->getInfo() << " ( " << recor->getFactorE() << " ) " << std::endl;
	
	
	// si el NodoA recor tiene hijo por la derecha
	if ( recor->getLink_hd() ) // paso recursivo para actualizar al hijo por la derecha
		imprimir( recor->getLink_hd() );
} // fin de imprimir


#endif
