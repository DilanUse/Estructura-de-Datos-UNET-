/**
 *	@Autor: Dilan Useche
 *	@Date: 2/27/2016
 *	@Release: 23/4/2016
 *	@Version: 1.2
 */

#ifndef NODO_H
#define NODO_H


/**
 *	@brief representacion de un Nodo de información 
 *	para cualquier estructura de datos, con capacidad
 *	de simple o doble enlace. La interpretación de los
 *	enlaces solo es una convención de La plantilla Nodo;
 * 	ya que pueden interpretarse de la manera que más convenga 
 */
template<class T> 
class Nodo
{
	private: 
		// enlace a otro Nodo, interpretado como el Nodo
		Nodo<T>* link_pre; // predecesor del Nodo actual
		// enlace a otro Nodo, interpretado como el Nodo
		Nodo<T>* link_suc; // sucesor del Nodo actual
		T* info; // campo de informacon asociada al Nodo
	public:
		/**
		 *	@brief inicializa el Nodo
		 *	@since 0.1
		 *	@param T* campo de informacion del Nodo
		 */
		explicit Nodo( T* inf ) : info( inf ) 
		{ this->link_pre = this->link_suc = NULL; } 
		~Nodo(); // destructor de Nodo
		Nodo<T>* getLink_pre() const; // retorna enlace predecesor
		Nodo<T>* getLink_suc() const; // retorna enlance sucesor
		T* getInfo() const; // retorna apuntador a campo de información del Nodo
		void setLink_pre( Nodo<T>* const ); // establece predecesor
		void setLink_suc( Nodo<T>* const ); // establece sucesor
		void setInfo( T* const ); // establece campo info 
}; // fin de la template class Nodo


/**
 *	@brief libera memoria del campo info del Nodo 
 *	y asigna a NULL todos sus apuntadores
 *	nota: si la memeoria del campo info del Nodo
 *	no fue asiganada con el operador new el comportamiento 
 *	del destructor no esta definido y puede traer 
 *	incovenientes inesperados, por lo tanto, se recomienda 
 *	solo enviar al contructor de Nodo objetos instaciados con
 *	el operador new 
 *	@since 1.2
 */
template<class T> Nodo<T>::~Nodo()
{
	//delete this->info; // libera memoria campo info
	
	// asigana a NULL apuntadores
	this->link_pre = this->link_suc = NULL;
	this->info = NULL;
} // fin del destructor


/**
 *	@brief devuelve referencia al Nodo interpretdo como predecesor
 *	@since 0.1
 *	@return Nodo<T>* referencia al Nodo predecesor
 */
 template<class T> Nodo<T>* Nodo<T>::getLink_pre() const
 {
	return this->link_pre; // retorna referencia
 } // fin de getLink_pre
 
 
/**
 *	@brief devuelve referencia al Nodo interpretdo como sucesor
 *	@since 0.1
 *	@return Nodo<T>* referencia al Nodo sucesor
 */
template<class T> Nodo<T>* Nodo<T>::getLink_suc() const
{
	return this->link_suc; // retorna referencia
} // fin de getLink_suc


/**
 *	@brief devuelve apuntador al campo de informacion del nodo
 *	@since 1.1
 *	@param bool solo por cuestiones de sobrecarga
 *	@return T* apuntador campo de informacion del Nodo
 */
template<class T> T* Nodo<T>::getInfo() const 
{
	return this->info; // retorna campo info
} // fin de getInfo


 /**
 *	@brief establece el Nodo predecesor del Nodo actual
 *	@since 0.1
 *	@param Nodo<T>* const Nodo predecesor
 */
template<class T> void Nodo<T>::setLink_pre( Nodo<T>* const pre ) 
{
	this->link_pre = pre;
} // fin de de setLink_pre


 /**
 *	@brief establece el Nodo sucesor del Nodo actual
 *	@since 0.1
 *	@param Nodo<T>* const Nodo sucesor
 */
template<class T> void Nodo<T>::setLink_suc( Nodo<T>* const suc ) 
{
	this->link_suc = suc;
} // fin de de setLink_suc


 /**
 *	@brief establece el campo info del Nodo actual
 *	@since 0.3
 *	@param const T* const campo info 
 */
template<class T> void Nodo<T>::setInfo( T* const inf ) 
{
	delete this->info; // libero campo info actual
	this->info = inf; // referencio al nuevo campo info
} // fin de de setLink_ext

#endif

