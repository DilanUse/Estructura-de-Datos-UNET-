/**
 *	@Autor: Dilan Useche
 *	@Date: 1/3/2016
 *	@Release: 27/4/2016
 *	@Version: 1.2
 */

#ifndef LISTAD_H
#define LISTAD_H

#include <iostream>
#include "Nodo.h"


/**
 *	@brief representacion de una estructura de datos lineal 
 *	tipo lista dinamica, que puede representar cualquiera de 
 *  estos cuatro tipos de lista: 1)Enlazada; 2)Enlazada circular;
 *	3)Doblemenete enlzada; 4)Doblemente enlazada circular. La lista
 *	además es compatible con cualquier tipo de dato.
 */
template<class T>
class ListaD
{
	private:
		Nodo<T>* cab; // cabezera de la lista 
		Nodo<T>* fin; // fin de la lista
		
		// atributos de tipo de lista
		bool DOBLE; // define si la lista es doblemente enlazada
		bool CIRCU; // define si la lista es circular
		int size; // tamaño de la lista( numero de elementos)
		
		// funciones miembro utilitarias
		Nodo<T>* getElemento( int& ); // retorna apuntador al Nodo en la posicion especificado
	public:
		static const int AGRE_INICIO = 1; // agregar al inicio
		static const int AGRE_FIN = 2; // agregar al final
		static const int AGRE_CRE = 3; // agregar en orden creciente
		static const int AGRE_DECRE = 4; // agregar en orden decreciente
		static const int BUSCAR_POS_CRE = -1; // buscar posicion en orden creciente 
		static const int BUSCAR_POS_DECRE = 1; // buscar posicion en orden decreciente   
		static const int BUSCAR_ELEMENTO = 0; // buscar elemento 
		static const int ELIM_INICIO = -1; // eliminar al incio
		static const int ELIM_ELEMENTO = 0; // eliminar elemento(buscandolo) 
		static const int ELIM_FINAL = 1; // eliminar al final
		
		/**
		 *	@brief inicializa la ListaD con cero elementos,
		 *	asiganando a NULL la cabezera y el fin de la misma,
		 *	y crea una lista enlazada asignando a false sus 
		 *	atributos de tipo de lista DOBLE y CIRCU
		 *	@since 0.1
		 */
		ListaD()
		{	// inicia....
			this->cab = this->fin = NULL; // cab y fin a NULL
			this->DOBLE = this->CIRCU = false; // atributos de tipo de lista a false
			this->size = 0; // tamaño de la lista
		} // fin del constructor 
		
		
		/**
		 *	@brief inicializa la ListaD con cero elementos,
		 *	asiganando a NULL la cabezera y el fin de la misma,
		 *	y crea una lista que depende de sus atributos 
		 *	de tipo de lista DOBLE y CIRCU
		 *	@param bool especifica si la lista es doblemente 
		 *	enlazada(true) o no(false)
		 *	@param bool especifica si la lista es circular(true)
		 * 	o no lo es(false)
		 *	@since 0.1
		 */
		ListaD( bool doble, bool circu )
		{	//inicia
			this->cab = this->fin = NULL; // cab y fin a NULL
			this->DOBLE = doble; this->CIRCU = circu; // atributos tipo de lista
			this->size = 0; // tamaño de la lista
		} // fin del constructor 
		
		
		~ListaD(); // destructor de la listaD
		Nodo<T>* getCab() const; // retorna la cab de la ListaD
		Nodo<T>* getFin() const; // retorna el fin de la ListaD
		int getSize() const; // retorna el tamaño de la lista
		Nodo<T>* getElemento_nodo( int ); // retorna apuntador al Nodo en la posicion especificado
		T* getElemento_info( int ); // retorna apuntador al campo info en la posicion especificada
		bool isDoble() const; // retorna determinación acerca de si la ListaD es doble
		bool isCircu() const; // retorna determinación acerca de si la ListaD es circular
		bool isVacia() const; // determina si la ListaD esta vacia
		Nodo<T>* buscar( T*, int tipo = BUSCAR_ELEMENTO, Nodo<T>** antes = NULL ) const; // busca elemento en la ListaD 
		int agregar( T*, int pos = AGRE_CRE, bool repeticion = true ); // agrega un nuevo elemento a la ListaD
		int eliminar( int tipo = ELIM_FINAL, T* info = NULL ); // elimina un elemento de la ListaD
		bool eliminarLista(); // elimina todos los elementos de la ListaD
		void imprimir() const; // imprime la ListaD en el flujo std de salida
		void imprimir( bool ) const; // imprime la ListaD en el flujo std de salida
}; // fin de ListaD


/**
 *	@brief elimina la lista y asigna a NULL sus aputadores
 *	@since: 1.1
 */
template<class T> ListaD<T>::~ListaD()
{
	this->eliminarLista(); // elimina la lista
} // fin del destructor


/**
 *	@brief retorna un apuntador a la cabezera de la ListaD
 *	@since: 0.1
 *	@return Nodo<T>* apuntador a la cabezera de la ListaD
 */
template<class T> Nodo<T>* ListaD<T>::getCab() const
{
	return this->cab; // cab de la lista
} // fin de getCab


/**
 *	@brief retorna un apuntador al fin de la listaD
 *	@since: 0.1
 *	@return Nodo<T>* apuntador al fin de la ListaD
 */
template<class T> Nodo<T>* ListaD<T>::getFin() const
{
	return this->fin; // fin de la lista
} // fin de getFin


/**
 *	@brief retorna el tamaño de la listaD
 *	@since: 1.1
 *	@return int atributo size de la listaD
 */
template<class T> int ListaD<T>::getSize() const
{
	return this->size; // tamaño de la lista
} // fin de size


/**
 *	@brief retorna un apuntador al Nodo en el 
 *	indice especificado 
 *	@since: 1.1
 *	@param int& indice del elemento a buscar en la listaD,
 *	es decir, posición del elemento en la lista en orden creciente
 *	@return Nodo<T>* apuntador al Nodo<T> en el indice
 *	especificado, en caso de que el indice indicado sea
 *	negativo o desborde el tamaño de la lista se retornara NULL
 */
template<class T> Nodo<T>* ListaD<T>::getElemento( int& indice )
{
	Nodo<T>* recor = this->cab; // recor empieza en cab 
	
	
	// si el indice es negativo o es igual o mayor al tamaño de la lista
	if( indice < 0 || indice >= this->size )
		return NULL; // se retorna NULL
	
	
	// recorre la lista hasta el indice especificado
	for( int i = 0; i < indice; i++ )
		recor = recor->getLink_suc(); // recor sera su sucesor
	
	
	return recor; // retorna Nodo
} // fin de getElemento


/**
 *	@brief retorna un apuntador al Nodo en el 
 *	indice especificado 
 *	@since: 1.1
 *	@param int& indice del elemento a buscar en la listaD,
 *	es decir, posición del elemento en la lista en orden creciente
 *	@return Nodo<T>* apuntador al Nodo<T> en el indice
 *	especificado, en caso de que el indice indicado sea
 *	negativo o desborde el tamaño de la lista se retornara NULL
 */
template<class T> Nodo<T>* ListaD<T>::getElemento_nodo( int indice )
{
	// obtengo el Nodo<T> en el indice especificado
	Nodo<T>* elemento = this->getElemento( indice );
	return elemento; // retorna Nodo<T>*
} // fin de getElemento_nodo


/**
 *	@brief retorna  el campo info del Nodo en el 
 *	indice especificado 
 *	@since: 1.1
 *	@param int& indice del elemento a buscar en la listaD,
 *	es decir, posición del elemento en la lista en orden creciente
 *	@return T* apuntador añ campo de información del Nodo<T> en el indice
 *	especificado, en caso de que el indice indicado sea
 *	negativo o desborde el tamaño de la lista se retornara NULL
 */
template<class T> T* ListaD<T>::getElemento_info( int indice )
{
	// obtengo el Nodo<T> en el indice especificado
	Nodo<T>* elemento = this->getElemento( indice );
	
	if( elemento )
		return elemento->getInfo();
	else
		return NULL;
} // fin de getElemento_nodo


/**
 *	@brief retorna el atributo de tipo de Lista CIRCU
 *	@since: 0.1
 *	@return bool atributo CIRCU de la ListaD
 */
template<class T> bool ListaD<T>::isCircu() const
{
	return this->CIRCU; // aributo de tipo de lista
} // fin de isCircu


/**
 *	@brief retorna el atributo de tipo de lista DOBLE
 *	@since: 0.1
 *	@return bool atributo DOBLE de la ListaD
 */
template<class T> bool ListaD<T>::isDoble() const
{
	return this->DOBLE; // aributo de tipo de lista
} // fin de isDoble


/**
 *	@brief determina si la ListaD esta vacia
 *	@since: 0.1
 *	@return bool true ListaD vacia, de lo contrario false
 */
template<class T> bool ListaD<T>::isVacia() const
{
	return !this->cab; // determinación
} // fin de isVacia


/**
 *	@brief busca el elemento de información especificado o el lugar en la ListaD del mismo,
 *	según sea el tipo de comparación especificada
 *	@param T* elemento de información a buscar
 *	@param int tipo de comparación a realizar en la busqueda. Para el valor BUSCAR_POS_CRE,
 *	la comparación sera menor que, es decir, se buscara la posición en la ListaD del 
 *	elemento de información especificado en orden creciente. Para el valor BUSCAR_POS_DECRE, la 
 *	comparación sera mayor que, es decir, se buscara la posición en la ListaD del elemento de 
 *	información especificado en orden decreciente. Para el valor BUSCAR_ELEMENTO, la comparación sera de 
 *	igualdad, es decir, se buscar al elemento especificado en la ListaD. En caso de omitir el
 *	parámetro, la comparación sera por defecto de igualdad(BUSCAR_ELEMENTO).
 * 	@param Nodo<T>** apuntador de puntero al antes(Solo util para cuando se quiere agregar)
 *	@since: 0.1
 *	@return Nodo<T>* apuntador al campo info buscado, Si el campo info a buscar no se encuentra o 
 *	la ListaD esta vacía, el apuntador sera NULL 
 */
template<class T> Nodo<T>* ListaD<T>::buscar( T* info, int tipo, Nodo<T>** antes ) const
{
	Nodo<T>* recor = this->cab; // recor empezara en cab
	bool empezo = false; // determinar si se empezo ya la busqueda
	
	
	// mientras recor tenga dirección y recor sea diferente de cab
	while( recor && ( recor != this->cab || !empezo ) ) // a excepción de la primera vez
	{
		if( !empezo ) // si no se ha empezado la busqueda
			empezo = true; // busqueda empezada
			
		
		if( ( tipo == BUSCAR_ELEMENTO && *info == *recor->getInfo() ) || // si busco a un elmento y lo consigo o....
			 ( tipo == BUSCAR_POS_CRE && *info < *recor->getInfo() )  || // busco pos en orden crec y al consigo o..
			 	( tipo == BUSCAR_POS_DECRE && *info > *recor->getInfo() ) ) // busco pos en orden decre y la consigo
			return recor;			
			
		
		// si antes apunta a una dirección valida( existe )
		if( antes )		
			*antes = recor; // antes sera ahora recor ( en agregar también cambiara antes)
			
			
		recor = recor->getLink_suc(); // recor ahora sera su sucesor 
	} // fin del while
	
	return NULL; // retorna NULL 
} // fin de buscar


/**
 *	@brief agrega un nuevo elemento de datos o información a la ListaD, 
 *	creando un nuevo Nodo y asignanando a su  campo info el elemento de 
 *	informacion especificado. Si el elemento es repetido, se agregará o no 
 *	dependiendo del argumento especificado o no para el parámetro repeticion. 
 *	@since: 0.1
 *	@param T* campo de informacion del nuevo Nodo
 *	@param int posición u orden en el que se va agregar el 
 *	nuevo elemento; AGRE_INICIO agrega al inicio; AGRE_FIN agrega al final;
 *	AGRE_CRE agrega en oreden creciente; AGRE_DECRE agrega en orden decresiente.
 *	En caso de omitirse este parámetro, se agregara en orden 
 *	creciente de manera predeterminada.
 *	@param bool determina o no si se puede agregar un elemento que ya esta en la ListaD,
 *	si el parámetro es true se permitira la repetición, de lo contrario se evitara la 
 *	repetición. En caso de omitirse el parámetro, este por defecto sera true, es decir, la 
 *	repetición estara permitida. 
 *	nota: si se omite el parámetro int debe tambien omitirse el parámetro bool, de lo contrario
 *	al llamar a la funcion con ( T*, bool ) se convertira implicitamente el valor bool a int 
 *	y el comportamineto de la funcion será el mismo del caso al agregar al inicio sin tomar en
 *	cuenta la repetición, es decir, la repetición estara permitida y se agregara al inicio el 
 *	nuevo elemento.
 *	nota: para evitar la repetición la funcion depende completamente de la sobrecarga del 
 *	operador de igualdad en la clase que representa el campo info, la repetición se evitara 
 *	de acuerdo a el tipo o atributo de comparación en la sobrecarga de la clase   
 *	@return int 1 exito al agregar; 0 fallo al agregar por falta de memoria; -1 no se agrego
 * 	debido a que el elemento ya existia en la ListaD y se especifico a repeticion como false
 */
template<class T> int ListaD<T>::agregar( T* info, int pos, bool repeticion )
{
	Nodo<T>* nuevo = new Nodo<T>( info ); // crea nuevo Nodo
	Nodo<T>* recor = this->cab; // recorrido empezara en cab
	Nodo<T>* antes = NULL; // antes sera NULL
	 
	
	
	if( nuevo ) // si la asignacion de memoria tuvo exito
	{
		// si se quiere evitar la repeticion
		if( !repeticion )
		{
			// busco si existe el elemento a agregar
			recor = this->buscar( info, BUSCAR_ELEMENTO, &antes );
			
			
			if( recor ) // si se encontro el elemento a agregar
				return -1; // el elemento a agregar ya existe
				
			recor = this->cab; // recor de nuevo sera cab
			antes = NULL; // antes de nuevo sera NULL
		} // fin del if
		
		
		// Caso en los que se debe llamar a buscar 
		// si se quiere agregar al inicio evitando la repetición
		// si se quiere agregar al final, evitando la repetición 
		// se se quiere agregar en un orden especifico, evitando o no la repetición
		if( pos == AGRE_CRE || pos == AGRE_DECRE ) 
		{ 
			// obtengo las posiciones recor y antes  del nuevo Nodo
			recor = this->buscar( info, ( pos == AGRE_CRE ? 
				BUSCAR_POS_CRE : BUSCAR_POS_DECRE ), &antes );
		} 
		else if( pos == AGRE_FIN ) // si no, si se quiere agregar al final 
		{
			recor = NULL; // recor sera NULL
			antes = this->fin; // antes sera el fin
		} // si no entonces se quiere agregar al inicio
		  // recor y antes no se modifican
	

		// si la lista esta vacia
		if( !antes && !recor ) // antes y recor son NULL
			this->cab = this->fin = nuevo; // cab y fin serán nuevo
		
		
		// si se agregara de primero o en medio
		if( recor ) // recor tiene dirección 
		{	// si la lista es doble, pre de recor será nuevo 
			recor->setLink_pre( ( this->DOBLE ? nuevo: NULL ) );
			nuevo->setLink_suc( recor ); // suc de nuevo sera recor
			
			// si agrege de primero, cab ahora será nuevo
			this->cab = ( recor == this->cab ? nuevo : this->cab );
		} // fin del if
		
		
		// si se agregara en medio o al fina
		if( antes ) // antes tiene dirección
		{	// si la lista es doble, pre de nuevo será antes 
			nuevo->setLink_pre( ( this->DOBLE ? antes: NULL ) );
			antes->setLink_suc( nuevo );
			
			// si agregue de ultimo, fin ahora sera nuevo
			this->fin = ( antes == this->fin ? nuevo : this->fin );
		} // fin del if
		
		
		// si la lista es circular
		if( this->CIRCU )
		{	// suc de fin sera cab
			this->fin->setLink_suc( cab );
			
			// si la lista ademas es doble 
			if( this->DOBLE )
				this->cab->setLink_pre( fin ); // pre de cab sera fin
		} // fin del if
	} 
	else // de lo contrario, no habia memoria suficiente
		return 0; // fallo al agregar por falta de memoria
		
		
	this->size++; // aumneta tamaño de la lista
	return 1; // exito al agregar
} // fin de agregar


/**
 *	@brief elimina el Nodo con el campo info especificado, o 
 *	el Nodo inicial o final, según se especifiquen los parámetros o no 
 *	@since: 0.1
 *	@param int tipo de eliminación en la ListaD; ELIM_INICIO se
 *	elimina el inicio de la ListaD; ELIM_FINAL se elimina el fin de 
 *	la ListaD; ELIM_ELEMENTO se elimina el elemento con el campo info
 *	especificado. En caso de omitirse, por defecto se eliminará
 *	el final de la ListaD
 *	@param T* elemento de información a eliminar. En caso de omitirse
 *	este sera NULL y no se tomara en cuenta para la eliminación, esta 
 *	dependera del tipo de eliminación.
 *	nota: Si se omite el parámetro int, debe omitirse también el 
 *	parámetro T*; Si se omite T* el tipo de eliminación no debe ser
 * 	ELIM_ELEMENTO; Si no se omite ningun parámetro, el tipo del eliminación
 *	debe ser ELIM_ELEMENTO
 *	@return int 0 si no se pudo eliminar, debido a que la ListaD esta vacía;
 *	1 exito al eliminar; -1  no se pudo eliminar debido a combinación invalida
 *	de parámetros; 404 si no se pudo eliminar, debido a que no se encontro el 
 *	elemento especificado 
 */
template<class T> int ListaD<T>::eliminar( int tipo, T* info )
{
	Nodo<T>* eliminar = this->cab; // Nodo a eliminar de la lista
	Nodo<T>* antes = NULL; // Nodo anterior a eliminar 
	
	if( !this->isVacia() ) // si la ListaD no esta vacia
	{	
		// si se viola la nomenclatura de los parámteros de la función
		// si se enivo elemento, y el tipo de eliminacion no es ELIM_ELEMENTO
		// o si no se envio elemento y el tipo de eliminación es ELIM_ELEMENTO
		if( ( info && tipo != ELIM_ELEMENTO ) || ( !info && tipo == ELIM_ELEMENTO ) )
			return -1; // combinación de parámetros invalida 
			
		
		// si se quiere eliminar un elemento especifico 
		if( tipo == ELIM_ELEMENTO )
		{
			// obtengo las posiciones antes y eliminar 
			eliminar = this->buscar( info, BUSCAR_ELEMENTO, &antes );
						
			// si no se encuentra el elemento a eliminar
			if( !eliminar ) 
				return 404; // no existe elemento a eliminar
		} 
		else if( tipo == ELIM_FINAL ) // si no, si se quiere eliminar al final
		{
			// obtengo copia del campo info del ultimo Nodo
			T* nodoFin = this->fin->getInfo();
			
			//obtengo las posiciones antes y eliminar del ultimo elemento
			eliminar = this->buscar(  nodoFin, BUSCAR_ELEMENTO, &antes );
		} // si no, entonces se quiere eliminar al inicio 
		  // por lo tanto no se modifican eliminar y antes
	
	
		// si eliminar es el unico en la lista
		if( this->cab == this->fin )
		{
			this->cab = this->fin = NULL; // cab y fin a NULL
			delete eliminar; // elimino Nodo
			this->size = 0; // tamaño de la ListaD será cero
			return 1; // exito al eliminar
		}  // fin del fi
		
		
		// si se eliminar en el inicio, fin o intermedio de la ListaD
		if( eliminar == this->cab ) // eliminar es cab
			this->cab = this->cab->getLink_suc(); // cab será su sucesor
		else if( eliminar == this->fin ) // si eliminar es fin
			this->fin = antes; // fin será antes
		else // si no, eliminar estara en una posición intermedia en la ListaD
		{
			// suc de antes ahora sera el suc de eliminar
			antes->setLink_suc( eliminar->getLink_suc() );
			
			// si la lista es doble, pre del suc de eliminar sera antes
			eliminar->getLink_suc()->setLink_pre( this->DOBLE ? antes : NULL ); 
		} // fin de los if...else
		
		// probando a reemplazar codigo de abajo
		this->fin->setLink_suc( ( this->CIRCU ? cab : NULL ) );
		this->cab->setLink_pre( ( this->DOBLE && this->CIRCU ? fin : NULL) );
		// termino prueba
					
		delete eliminar; // elimina Nodo	
	}
	else // de lo contrario, esta vacia la lista
		return 0; // No hay nada que eliminar
	
	
	this->size--; // decremento el tamaño de la ListaD en uno	
	return 1; // exito al eliminar
} // fin de eliminar


/**
 *	@brief elimina todos los Nodos de la ListaD, vaciando
 *	la ListaD.
 *	@since: 0.1
 *	@return bool true eliminación completada, false no se pudo 
 *	eliminar la ListaD debido a que ya esta vacía
 */
template<class T> bool ListaD<T>::eliminarLista()
{
	Nodo<T>* recor = this->cab; // recor empieza en cab cab
	Nodo<T>* eliminar = NULL; // eliminar será NULL
	
	
	// si la ListaD no esta vacia 
	if( !this->isVacia() ) 
	{
		// si eliminar es el unico en la lista
		if( this->cab == this->fin )
		{
			this->cab = this->fin = NULL; // cab y fin a NULL
			delete recor; // elimino Nodo
			return true; // exito al eliminar ListaD
		}  // fin del if
		
		
		// mientras la lista no este vacia 
		while(  recor ) 
		{	
			eliminar = recor; // eliminar ahora sera recor
			recor = recor->getLink_suc(); // recor pasa a su sucesor
		
			delete eliminar; // elimino Nodo
			
			
			// si se llego al final de la ListaD
			if( recor == this->fin )
			{
				delete recor; // elimino ultimo Nodo
				this->cab = this->fin = recor = NULL; // cab, fin y recor serán NULL
				this->size = 0; // el tamaño de la ListaD será cero
			} // fin del if
		} // end while
	}
	else
		return false; // ListaD vacia
		
		
	return true; // exito al eliminar
} // fin de eliminarLista


/**
 *	@brief imprime la lista en el flujo std de salida,
 *	la lista imprime la perspectiva solo de los enlaces
 *	utilizados para el tipo de lista inicializado. Si la 
 *	ListaD esta vacia, se imprime "NULL"
 *	@since: 0.1
 */
template<class T> void ListaD<T>::imprimir() const
{
	// El recorrido empezara en la cabezera de la lista
	Nodo<T>* recor = this->cab; 
	
	
	// si al ListaD esta vacia
	if( !recor )
	{
		std::cout << "NULL" << std::endl;
		return; // retorna a la funcion que hizo la llamada
	} // fin del if
	
	
	// si solo hay un elemento en la ListaD
	if( recor && this->cab == this->fin )
	{
		// si la ListaD es doble repito el preocesos
		for( int i = 0; i < ( this->DOBLE ? 2 : 1 ); i++ )
		{
			std::cout << *recor->getInfo();
		
			// si la ListaD es circular
			if( this->CIRCU ) // imprimo enlace circular
				std::cout << "|-->" << *recor->getLink_suc()->getInfo() << std::endl; 
			else
				std::cout << "-->NULL" << std::endl; // enlace utimo Nodo
		} // fin del for
	} // fin del if 
	
	
	// mientras la lista no este vacia y no se llegue al final 
	while(  recor && recor != this->fin ) 
	{		
		std::cout << *recor->getInfo() << "-->"; // imprime Nodo
		recor = recor->getLink_suc(); // recor pasa a su sucesor
		
		
		// si se llego al final de la ListaD
		if( recor == this->fin )
		{
			std::cout << *recor->getInfo(); // ultimo Nodo
			
			// si la ListaD es circular
			if( this->CIRCU ) // imprimo enlace circular
				std::cout << "|-->" << *recor->getLink_suc()->getInfo() << std::endl; 
			else
				std::cout << "-->NULL" << std::endl; // enlace utimo Nodo
		}
	} // end while
	
	
	recor = this->fin; // recor empezara en fin ahora
	
	
	// mientras la lista no este vacia, sea doble y recor no llegue a cab
	while( recor && this->DOBLE && recor != this->cab ) 
	{	
		std::cout << *recor->getInfo() << "-->"; // imprime Nodo
		recor = recor->getLink_pre(); // recor pasa a su predecesor
		
		
		// si se llego a la cab de la ListaD 
		if( recor == this->cab )
		{
			std::cout << *recor->getInfo(); // ultimo Nodo
			
			// si la ListaD es circular
			if( this->CIRCU ) // imprimo enlace circular
				std::cout << "|-->" << *recor->getLink_pre()->getInfo() << std::endl; 
			else
				std::cout << "-->NULL" << std::endl; // enlace utimo Nodo
		}
	} // end while
} // fin de imprimir


/**
 *	@brief imprime la ListaD en el flujo std de salida,
 *	imprimiendo todos los enlaces de la lista, independientemente 
 *	del tipo de ListaD especificado. Si la lista esta vacia, se imprime "NULL"
 *	*param bool solo para cuestiones de sobrecarga, la función no toma 
 *	 en cuenta este parámetro
 *	@since: 0.1
 */
template<class T> void ListaD<T>::imprimir( bool sobrecarga ) const
{
	// El recorrido empezara en la cabezera de la lista
	Nodo<T>* recor = this->cab; 
	
	
	// si al ListaD esta vacia
	if( !recor )
	{
		std::cout << "NULL" << std::endl; // imprime enlace del ultimo Nodo
		return; // retorna a la funcion que hizo la llamada
	} // fin del if
	
	
	// si solo hay un elemento en la ListaD
	if( recor && this->cab == this->fin )
		std::cout << recor->getLink_pre() << "<--" << *recor->getInfo() << 
			"-->" << recor->getLink_suc() << std::endl; // imprime Nodo y sus dos enlaces

	
	
	// mientras la lista no este vacia y no se llegue al final o..
	while(  recor && recor != this->fin ) // no se haya empezado el recorrido
	{	
		std::cout << recor->getLink_pre() << "<--" << *recor->getInfo() << 
			"-->" << recor->getLink_suc(); // imprime Nodo y sus dos enlaces
		recor = recor->getLink_suc(); // recor pasa a su sucesor
		
		
		// si se llego al final de la ListaD
		if( recor == this->fin )
			std::cout << std::endl << recor->getLink_pre() << "<--" << *recor->getInfo() << 
			"-->" << recor->getLink_suc() ; // imprime ultimo Nodo y sus dos enlaces
			
		
		std::cout << std::endl; // deja linea en blanco
	} // end while
} // fin de imprimir

#endif
