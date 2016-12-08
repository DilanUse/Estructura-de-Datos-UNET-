#include "Camino.h"

//using namespace std; ////////////////////////////////////////

// identificador compartido de Caminos
int Camino::id_static = 0; // inicia en cero 


/**
 *	@brief inicializa el Camino asignando a cero todos
 *	sus valores y instanciando su ListaD de Vertices
 *	@since 1.0
 */	
Camino::Camino()
{ // inicializa...
	this->id = Camino::id_static; // id será id_static actual
	Camino::id_static++; // incremento id_static en uno
	this->longitud = this->vertices = 0;
	this->lista_vertices = new ListaD<Vertice>( true, false );
} // fin del contructor


/**
 *	@brief libera memoria del Camino
 *	@since 1.0
 */	
Camino::~Camino()
{ // elimina la lista de vertices
	delete this->lista_vertices;
} // fin del destructor


/**
 *	@brief retorna la longitud del Camino
 *	@since 1.0
 *	@return double Longitud del Camino
 */
double Camino::getLongitud() const
{
	return this->longitud; // longitud del camino
} // fin de getLongitud


/**
 *	@brief retorna la cantidad de Vertices en el Camino
 *	@since 1.0
 *	@return int cantidad de Vertices del Camino
 */
int Camino::getVertices() const
{
	return this->vertices; // cantidad de vertices del camino
} // fin de getVertices


/**
 *	@brief actualiza la cantidad de Vertices en el Camino
 *	y la Longitud del mismo
 *	@since 1.0
 */
void Camino::actualizar()
{
	// cantidad de vertices sera la cantidad de elementos en la lista
	this->vertices = this->lista_vertices->getSize();
	this->longitud = 0; // antes de actualizarce debe ser cero
	
	
	// acumulo las Longitudes de todos los Vertices en el Camino
	for( int i = 0; i < this->lista_vertices->getSize(); i++ )
		this->longitud += 
			this->lista_vertices->getElemento_info( i )->getLongitudArista();
} // fin de actualizar


/**
 *	@brief elimina en la lista de Vertices en forma sucesiva
 *	a partir del Vertice de partida especificado pero sin incluirlo
 *	@param Vertice* Vertice a partir del cual se debe 
 *	eliminar la lista de Vertices en forma sucesiva
 *	@since 1.0
 *	@return bool true si se pudo eliminar, de lo contrario false
 *	debido a que no se encuentra el Vertice especificado en 
 *	la lista de Vertices del Camino
 *	nota: al retornar true la funcion garantiza que se ha 
 *	encontrado el Vertice de partida en la lista de Vertices
 *	del camino, pero la elimnación depende de si el Vertice
 *	es o no el ultimo elemento de la lista, ya que el Vertice de 
 *	partida no es tomado en cuenta en la eliminación
 */
bool Camino::eliminarListaVerticesDesde( Vertice* partida )
{
	// busco en la lista de Vertices el Vertice de partida
	// y lo almaceno en recor
	Nodo<Vertice>* recor = this->lista_vertices->buscar( partida );
	Nodo<Vertice>* eliminar; // auxiliar para eliminar Vertices
	
	
	// si se encontro Vertice de partida y se alamaceno en recor
	if( recor )
	{
		recor = recor->getLink_suc(); // recor inicia siendo su sucesor 
		
		
		// mientras recor tenga direccion valida
		while( recor )
		{
			eliminar = recor; // eliminar ser recor
			recor = recor->getLink_suc(); // recor será su sucesor
			this->lista_vertices->eliminar( ListaD<Vertice>::ELIM_ELEMENTO, eliminar->getInfo() ); // elimino 
		} // fin del while 
	}
	else // si no, entonces no se pudo eliminar 
		return false;  // no se encontro el Vertice de partida
		
		
	return true; // se encontro el Vertice de partida y elimino despues de el la lista de Caminos 
} // fin de eliminarListaVerticesDesde


/**
 *	@brief determina si dos Caminos son exactamente iguales 
 *	ya sea en el mismo sentido o en sentidos opuestos segun 
 *	sea especificado, es decir, si tiene la misma sucesion de 
 *	Vertices en igual sentido o contrario
 *	@param Camino* Camino a compara con el Camino que hizo la 
 *	llamada
 *	@param bool determina si la comparación es en el mismo sentido 
 *	o en sentido opuesto segun se especifique false o true respectivamente,
 *	en caso de no especificar el parámetro este por defecto sera false
 *	@since 1.0
 *	@return bool true si lo Caminos son exactamente iguales en el orden 
 *	especificado, de lo contrario false 
 *	nota: para que la comprobacion sea efectiva los Caminos
 *	deben ser de igual numero de Vertices, si no lo son la función 
 *	retornara false 
 */
bool Camino::iguales( Camino* contrario, bool opuesto ) const
{
	// recor empieza en la cab de la lista de Vertices del
	// Camino que hizo la llamada, y travel sera su contraparte
	// y empezara en la cab o final de la lista de contrario
	// dependiendo del parámetro opuesto 
	Nodo<Vertice>* recor = this->lista_vertices->getCab();
	Nodo<Vertice>* travel = ( opuesto ? 
		contrario->lista_vertices->getFin() : 
			contrario->lista_vertices->getCab() );
			
			
	// si los caminos tienen igual numero de Vertices
	if( this->vertices == contrario->vertices )
	{ //cout << "Igual vertices" << endl; ////////////////
		// mientras recor y travel tengan direccion valida 
		while( recor && travel )
		{ //cout << *recor->getInfo() << " == " << *travel->getInfo() << endl; ///////////////////////// 
			// si recor y travel no son iguales
			if( !( *recor->getInfo() == *travel->getInfo() ) )
				return false; // Caminos diferentes
				
			
			// recor será su sucesor y travel sera sus sucesor o 	
			recor = recor->getLink_suc(); // su predecesor dependiendo de opuesto
			travel = ( opuesto ? travel->getLink_pre() : travel->getLink_suc() ); 
		} // fin del while
	}
	else
		return false; // los Caminos no son iguales 
			
			
	return true; // Caminos iguales
} // fin de iguales


/**
 *	@brief sobrecarga el operador de insercion de flujo para 
 *	imprimir una represetanción de un Camino en el flujo std
 *	de salida
 *	@param ostream& flujo de salida a ser usado
 *	@param const Camino& Camino a ser impreso en el flujo de salida
 *	@since 1.0
 *	@return ostrem& flujo de salida usado(permite usar el operador en cascada)
 */
std::ostream& operator<<( std::ostream& salida, const Camino& datos )
{
	char delim = '/'; // separador 
	
	// imprime atribtos separados por delim
	salida << "(id: " << datos.id << delim << "Vertices: " << datos.vertices
		<< delim << "Longitud: " << datos.longitud << ")";
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<


/**
 *	@brief sobrecarga el operador relacional menor que,
 *	el cual compara la cantidad de vertices en los Caminos
 *	@param Camino& operando derecho del operador
 *	@since 1.0
 *	@return bool true si el Camino(operando) izquierdo tiene
 *	menos vertices que el Camino(operando) derecho
 */
bool Camino::operator<( const Camino& datos )
{
	return ( this->vertices < datos.vertices );
} // fin del operador<


/**
 *	@brief sobrecarga el operador relacional mayor que,
 *	el cual compara la longitud en los Caminos
 *	@param Camino& operando derecho del operador
 *	@since 1.0
 *	@return bool true si el Camino(operando) izquierdo tiene
 *	mayor longitud que el Camino(operando) derecho
 */
bool Camino::operator>( const Camino& datos )
{
	return ( this->longitud > datos.longitud );
} // fin del operador>


/**
 *	@brief sobrecarga el operador relacional de igualdad
 *	el cual compara el id en los Caminos
 *	@param Camino& operando derecho del operador
 *	@since 1.0
 *	@return bool true si el Camino(operando) izquierdo tiene
 *	el mismo id que el Camino(operando) derecho
 */
bool Camino::operator==( const Camino& datos )
{
	return ( this->id == datos.id ); // retorna desición  
} // fin de operator== 


















