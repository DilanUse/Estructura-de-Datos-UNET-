#include "Grafo.h"
using namespace std; // uso del espacio de nombres std
#include <windows.h> //////////////////////////////


/**
 *	@brief inicializa el Grafo asignando todos
 *	sus valores y instanciando su ListaD de Vertices y 
 *	de Caminos, asigna además sus atributos de tipo de 
 *	de Grafo DIRIGIDO y PONDERADO, el Grafo sera por 
 *	defecto dirigido y no ponderado
 *	@param bool valor atributo de tipo de Grafo DIRIGIDO
 *	@param bool valor atributo de tipo de Grafo PONDERADO
 *	@since 1.0
 */	
void Grafo::inicializar( bool dirigido, bool ponderado )
{ // incializa...
	this->DIRIGIDO = dirigido;
	this->PONDERADO = ponderado;
	this->longitud = 0;
	this->lista_adyacencia = new ListaD<Vertice>();
	this->lista_caminos = new ListaD<Camino>();
} // fin de inicializar


/**
 *	@brief inicializa el Grafo asignando todos
 *	sus valores y instanciando su ListaD de Vertices y 
 *	de Caminos, el Grafo sera por defecto dirigido y no 
 *	ponderado
 *	@since 1.0
 */	
Grafo::Grafo()
{ // inicializa
	this->inicializar(); // llama a inicializar
} // fin del constructor


/**
 *	@brief inicializa el Grafo asignando a cero todos
 *	sus valores y instanciando su ListaD de Vertices y 
 *	de Caminos, asigna además sus atributos de tipo de 
 *	de Grafo DIRIGIDO y PONDERADO
 *	@param bool valor atributo de tipo de Grafo DIRIGIDO
 *	@param bool valor atributo de tipo de Grafo PONDERADO
 *	@since 1.0
 */	
Grafo::Grafo( bool dirigido, bool ponderado )
{ // inicializa
	this->inicializar( dirigido, ponderado );
} // fin del constructor


/**
 *	@brief inicializa el Grafo asignando a cero todos
 *	sus valores y instanciando su ListaD de Vertices y 
 *	de Caminos, asigna además sus atributos de tipo de 
 *	de Grafo DIRIGIDO y PONDERADO, además se crea el 
 *	Grafo con el nombre del archivo suministrado
 *	@param string nombre del Archivo a leer valores del Grafo
 *	@param char delimitador o separador en el Archivo para 
 *	los campos en el Archivo
 *	@param bool valor atributo de tipo de Grafo DIRIGIDO
 *	@param bool valor atributo de tipo de Grafo PONDERADO
 *	nota: este constructor solo crea Grafos para Archivos con el 
 *	siguiente formato vertice delim vertice delim peso/longitud
 *	@since 1.0
 */	
Grafo::Grafo( string nom_archivo, char delimitador, bool dirigido, bool ponderado )
{ // inicializa
	this->inicializar( dirigido, ponderado );


	Archivo* archivo = new Archivo( nom_archivo ); // creo Archivo
	string* buffer; // buffer para almacenar campos
	
	
	archivo->abrir(); // abro el archivo
	
	
	// mientras no llegue al final del Archivo
	while( !archivo->isFinal() )
	{
		buffer = archivo->leerCampos( delimitador, 3 ); // leo campos del Archivo
		
		// agrego Vertices de partida y llegada a la ListaD de adyacencia
		this->agregar( new Vertice( buffer[0] ), new Vertice( buffer[1], 
			( this->PONDERADO ? atof( buffer[2].c_str()) : 0 ) ));
		
		
		// si el Grafo no es dirigido 
		if( !this->DIRIGIDO ) // agrego Vertices en sentido contrario a la ListaD de adyacencia
			this->agregar(  new Vertice( buffer[1] ), new Vertice( buffer[0], 
				( this->PONDERADO ? atof( buffer[2].c_str()) : 0 ) ));
	} // fin del while
} // fin del constructor


/**
 *	@brief retorna determinación acerca de si el
 *	Grafo es dirigido
 *	@since 1.0
 *	@return bool valor del atributo de Grafo DIRIGIDO
 */	
bool Grafo::isDirigido() const
{
	return this->DIRIGIDO;
} // fin de isDirigido


/**
 *	@brief retorna determinación acerca de si el
 *	Grafo es ponderado
 *	@since 1.0
 *	@return bool valor del atributo de Grafo PONDERADO	
 */	
bool Grafo::isPonderado() const
{
	return this->PONDERADO;
} // fin de isPonderado


/**
 *	@brief retorna numero de Vertices en el Grafo
 *	@since 1.0
 *	@return int numero de Vertices 	
 */	
int Grafo::getNumeroVertices() const
{
	// si el Grafo no es dirigido
	if( !this->DIRIGIDO ) // Vertices será igual al tamaño de la LAP
		return this->lista_adyacencia->getSize();
	else
	{
		// el numero de Vertices inicial sera el tamaño de la LAP
		int vertices = this->lista_adyacencia->getSize();
		Nodo<Vertice>* recor = this->lista_adyacencia->getCab(); // recor será cab de LAP
		Nodo<Vertice>* travel = NULL; // travel será NULL 
		ListaD<Vertice>* ausentes = new ListaD<Vertice>(); // lista de Vertices ausentes en la LAP
		
		
		// mientras recor tenga direccion valida
		while( recor )
		{
			// travel sera la cab de la sublista de recor
			travel = recor->getInfo()->vertices_adyacentes->getCab();
			
			
			// mientras travel tenga direccion valida
			while( travel )
			{
				// si el Vertice de travel no se encuentra ena la LAP
				if( !this->lista_adyacencia->buscar( travel->getInfo() ) && 
					!ausentes->buscar( travel->getInfo() ))
				{
					vertices++; // incremento vertices
					ausentes->agregar( travel->getInfo(), ListaD<Vertice>::AGRE_FIN ); // agrego a ausentes
				} // fin del if
					
					
				travel = travel->getLink_suc(); // travel será su sucesor
			} // fin del while
			
			
			recor = recor->getLink_suc(); // recor sera su sucesor
		} // fin del while
		
		
		return vertices; // retorna numero de Vertices
	} // fin del if...else
} // fin de getNUmeroVertices



/**
 *	@brief retorna la longitud de todas las aristas del grafo
 *	@since 1.1
 *	@return float longitud de las aristas del grafo 	
 */	
float Grafo::getLongitud() const
{
	return this->longitud;
} // fin de getLongitud


/**
 *	@brief agrega dos Vertices, uno de partida y uno de 
 *	llegada a la lista principal de adyacencia y a su sublista 
 *	respectivamente 
 *	@param Vertice* apuntador al Vertice de partida
 *	@param Vertice* apuntador al Vertice destino
 *	@since 1.0
 *	@return bool true exito al agregar, de lo contrario false 	
 */	
bool Grafo::agregar( Vertice* vertice_partida, Vertice* vertice_destino )
{
	// Vertice auxiliar para acceder a las sublistas de la 
	Nodo<Vertice>* vertice_aux; // Lista de adyacencia
	int estado = 1; // estado de la operación de agregar
	
	
	
	// si la lista de adyacencia esta vacia
	if( this->lista_adyacencia->isVacia() )
	{
		 estado = this->lista_adyacencia->agregar( vertice_partida, // agrego vertice_partida a la lista 
			ListaD<Vertice>::AGRE_FIN ); // de adyacencia principal(LAP)
		vertice_aux = this->lista_adyacencia->getCab(); // obtengo la cab de la LAP
		estado = vertice_aux->getInfo()->vertices_adyacentes->agregar( // agrego vertice_destino a la lista 
			vertice_destino, ListaD<Vertice>::AGRE_FIN ); // de adyacencia secundaria(LAS)
	}
	else // si no, la lista no esta vacia
	{
		// busco al vertice de partida en el Grafo y apunto con vertice_aux
		vertice_aux = this->lista_adyacencia->buscar( vertice_partida );
		
		
		// si se encontro el vertice_partida en la LAP
		if( vertice_aux )
			estado = vertice_aux->getInfo()->vertices_adyacentes->agregar( // agrego vertice destino a 
				vertice_destino, ListaD<Vertice>::AGRE_FIN ); // vertice_aux
		else // si no, entonces no se encontra en la LAP
		{
			estado = this->lista_adyacencia->agregar( // agrego vertice_partida a la lista 
				vertice_partida, ListaD<Vertice>::AGRE_FIN ); // de adyacencia principal(LAP)
			vertice_aux = this->lista_adyacencia->getFin(); // obtenga el final de la LAP
			estado = vertice_aux->getInfo()->vertices_adyacentes->agregar( // agrego vertice_destino a la  
				vertice_destino, ListaD<Vertice>::AGRE_FIN ); // lista de adyacencia secundaria(LAS)
		} // fin del if...else
	} // fin del if...else
	
	
	this->longitud += vertice_destino->getLongitudArista(); // acumulo la longitud de la arista
	return ( estado == 1 ); // retorna estado de agregar
} // fin de agregar



void Grafo::BuscarCaminos()
{
	// recor empieza en la cab de la lAP
	Nodo<Vertice>* recor = this->lista_adyacencia->getCab();
	Nodo<Camino>* camino = NULL; // apuntador a lista de caminos
	
	
	// mientras recor tenga direccion valida
	while( recor )
	{
		// agrego a la sublista de camino a recor 
		this->agregar_camino( camino, recor );
		recor = recor->getLink_suc(); // recor ahora sera su sucesor
		
		
		// si recor aun tiene dirección valida
		if( recor )
		{
			// agrego a la lista de caminos un nuevo Camino
			this->lista_caminos->agregar( new Camino(), ListaD<Camino>::AGRE_FIN );
			camino = this->lista_caminos->getFin(); // camino ahora sera el fin de lista_caminos
//			cout << endl << "EMPIEZO CON CAMINOS DE OTRO VERTICE" << endl;////////////////////////////////
		} // fin del if
	} // fin de while 
}  // fin de crearCaminos


/**
 *	@brief agrega un Vertice a la lista de caminos
 *	del Camino especificado 
 *	@param Nodo<Camino>* Nodo del Camino actual para 
 *	agregar nuevos Vertices
 *	@param Nodo<Vertice>* Nodo a agregar a la lista de
 *	Vertices del Camino especificado
 *	@since 1.0
 *	@return bool true si se llego al final de un Camino, de lo contrario false 	
 */	
bool Grafo::agregar_camino( Nodo<Camino>* nodo_lista_camino, Nodo<Vertice>* nodo_agregar )
{
	Nodo<Vertice>* nodo_sublista_adyacencia; // posición en la sublista de adyacencia de nodo_agregar
	bool finCamino = false; // determina si se llego al final del camino
	Nodo<Vertice>* nodo_aux_vertice = NULL; // nodo para operaciones auxiliares
	Nodo<Camino>* nodo_aux_camino = NULL; // nodo para oporeaciones auxiliares
	
	
	
	// si la lista de caminos esta vacia
	if( this->lista_caminos->isVacia() )
	{
		// agrego a la lista de caminos un nuevo Camino
		this->lista_caminos->agregar( new Camino(), ListaD<Vertice>::AGRE_FIN );
		nodo_lista_camino = this->lista_caminos->getFin(); // nodo_lista_caminos sera el ultimo Camino creado 
	} // fin del if
	
	
	// si la lista de Vertices de nodo_lista_camino esta vacia
	if( nodo_lista_camino->getInfo()->lista_vertices->isVacia() )
	{
		// agrego a la lista de Vertices de nodo_lista_camino un nuevo 
		nodo_lista_camino->getInfo()->lista_vertices // Nodo con el Vertice 
			->agregar( nodo_agregar->getInfo(), ListaD<Vertice>::AGRE_FIN ); // de nodo_agregar
	} 
	else // si no, busco en la lista de nodo_lista_camino
	{
		// si esta el Vertice de nodo_agregar en la lista de Vertices de nodo_lista_camino
		if( nodo_lista_camino->getInfo()->lista_vertices->buscar( nodo_agregar->getInfo() ) )
			return false; // no se agrega y retorno false(no he llegado al fin del Camino)
		else // si no esta, entonces lo agrego
			nodo_lista_camino->getInfo()->lista_vertices->agregar( 
				nodo_agregar->getInfo(), ListaD<Vertice>::AGRE_FIN );
	} // fin del if...else
	
	
	// si nodo_agregar no tiene una sublista de Vertices( no es un Nodo de la LPA)
	if( nodo_agregar->getInfo()->vertices_adyacentes->isVacia() )
		nodo_agregar = this->lista_adyacencia-> // buscp al Vertice en la 
			buscar( nodo_agregar->getInfo() ); // lista principal de adyacencia
		
	
		
	// si el nodo_agregar no esta en la lista de adyacencia
	if( !nodo_agregar )
		return true; // entonces llegue al final del camino
		
		
	// nodo_sublista_adyacencia ahora sera la cab de la sublista de adyacencia de nodo_agregar
	if( !nodo_agregar->getInfo()->vertices_adyacentes->isVacia() )	/////////////////////////////
		nodo_sublista_adyacencia = nodo_agregar->getInfo()->vertices_adyacentes->getCab(); 
	else
	nodo_sublista_adyacencia = NULL; /////////////////////////////////////////////////////////////
	
	
	// llamada recursiva con argumentos de Nodo de Camino, y Nodo a agregar respectivamente 
	finCamino = this->agregar_camino( nodo_lista_camino, nodo_sublista_adyacencia ); 
	

	// hacer mientras nodo_sublista_adyacencia tenga un sucesor
	do
	{
		// si ya se llego al final de camino
		if( finCamino )
		{
			// si nodo_sublista_adyacencia no tiene sucesor
			if( !nodo_sublista_adyacencia->getLink_suc() )
				return true; // se llego al final del camino
			else // si no, entonces si tiene sucesor, debo crear nuevo Camino
			{
				// nodo_aux_vertice será el Vertice en la cab de  
				nodo_aux_vertice = this->lista_caminos->getFin() // la lista de vertices del ultimo Camino
					->getInfo()->lista_vertices->getCab(); // en la lista de caminos
					
				// agrego a la lista de caminos un nuevo Camino
				this->lista_caminos->agregar( new Camino(), ListaD<Camino>::AGRE_FIN );
				nodo_aux_camino = this->lista_caminos->getFin(); // nodo_aux_camino será el ultimo Camino 
				
				
				// copio camino de nodo_lista_camino desde su cab hasta nodo_agregar al nuevo Camino
				while( true )
				{
					// agrego a nodo_aux_vertice a la lista de Vertices de nodo_aux_camino
					nodo_aux_camino->getInfo()->lista_vertices->agregar( 
						nodo_aux_vertice->getInfo(), ListaD<Vertice>::AGRE_FIN );


					// si nodo_aux_vertice es el mismo Vertice de nodo_agregar
					if (  *nodo_aux_vertice->getInfo() == *nodo_agregar->getInfo() )
						break; // dejo de copiar el camino 
					
					
					// nodo_aux_vertice ahora será su sucesor 	
					nodo_aux_vertice = nodo_aux_vertice->getLink_suc();
				} // fin del while
			} // fin del if...else
		} // fin del if
		
		
		// si nodo_sublista_adyacencia tiene sucesor
		if( nodo_sublista_adyacencia->getLink_suc() )
		{
			nodo_sublista_adyacencia = nodo_sublista_adyacencia->getLink_suc();
			
			
			// si ya se llego al final del camino
			if( finCamino )
			{
				// llamada recursiva con argumentos de Nodo de Camino, y Nodo a agregar respectivamente 
			/*	finCamino =*/ agregar_camino( nodo_aux_camino, nodo_sublista_adyacencia );
			}
			else // si no, no se ha llegado al final del camino
			{
				// llamada recursiva con argumentos de Nodo de Camino, y Nodo a agregar respectivamente
				finCamino = agregar_camino( nodo_lista_camino, nodo_sublista_adyacencia );
			} // fin del if...else
		} // fin del if
	}while( nodo_sublista_adyacencia->getLink_suc() ); // fin del while
	
	
	return true; // se llego al final del camino
} // fin de agregar_camino


/**
 *	@brief busca los Caminos con mayor cantidad de Vertices
 *	en el Grafo, sin repetir Vertices ni aristas, es decir
 *	sin formar ciclos, los Caminos resultantes seran guardados 
 *	en la lista de Caminos del Grafo 
 *	nota: en caso de que el Grafo sea no dirigido, buscara los
 *	Caminos que tengan el numero de Vertices del Grafo
 *	nota: en caso de que el Grafo sea dirigido, buscara los
 *	Caminos con mayor cantidad de Vertices  
 *	@since 1.0
 */	
void Grafo::buscarCaminos_maxVertices()
{
	// recor_vertice empieza en la cab de la lAP
	Nodo<Vertice>* recor_vertice = this->lista_adyacencia->getCab();
	Nodo<Camino>* camino = NULL; // apuntador a lista de caminos
	Nodo<Camino>* recor_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* travel_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* eliminar_camino; // apuntador para eliminar Caminos
	int numeroVertices = this->getNumeroVertices(); // numero de Vertices en el Grafo
	this->lista_caminos->eliminarLista(); // elimino lista de Caminos si es que la habia  
	
	
	// mientras recor tenga direccion valida
	while( recor_vertice )
	{
		// agrego a la sublista de camino a recor 
		this->agregar_camino( camino, recor_vertice );
		recor_vertice = recor_vertice->getLink_suc(); // recor ahora sera su sucesor
		this->actualizarCaminos(); // actualizo Caminos creados 

		
		// si el Grafo no es dirigido 
		if( !this->DIRIGIDO )
		{
			// recor_camino empieza en la cab de la lista de Caminos
			recor_camino = this->lista_caminos->getCab();
			
			
			// mientras recor_camino tenga dirección valida 
			while( recor_camino )
			{
				// si recor_camino tiene menos Vertices que la cantidad de Vertices en el Grafo
				if( recor_camino->getInfo()->getVertices() < numeroVertices )
				{
					eliminar_camino = recor_camino; // recor_camino se eliminara 
					recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
					this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
						ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos
				}
				else // si no, entonces el camino de recor_camino tiene tantos Vertices como el Grafo
					recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
			} // fin del while
		}
		else // si no es dirigido
		{
			// recor_camino empieza en la cab de la lista de Caminos
			recor_camino = this->lista_caminos->getCab();
	
	
			// mientras recor_camino tenga dirección valida 
			while( recor_camino )
			{
				// travel_camino empieza en la cab de la lista de Caminos
				travel_camino = this->lista_caminos->getCab();
				
				
				// mientras travel_camino tenga dirección valida
				while( travel_camino )
				{
					// si travel_camino tiene menos Vertices que recor_camino 
					if( *travel_camino->getInfo() < *recor_camino->getInfo() )
					{
						eliminar_camino = travel_camino; // se eliminara a travel_camino
						travel_camino = travel_camino->getLink_suc(); // travel_camino será sus sucesor
						this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
							ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos 
					}
					else // si no, entonces travel_camino no tiene menos Vertices que recor_camino
						travel_camino = travel_camino->getLink_suc();  // travel_camino será sus sucesor
				} // fin del while
				
				
				recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
			} // fin del while	
		} // fin del if...else
		
		
		// si recor aun tiene dirección valida
		if( recor_vertice )
		{
			// agrego a la lista de caminos un nuevo Camino
			this->lista_caminos->agregar( new Camino(), ListaD<Camino>::AGRE_FIN );
			camino = this->lista_caminos->getFin(); // camino ahora sera el fin de lista_caminos
//			cout << endl << "EMPIEZO CON CAMINOS DE OTRO VERTICE" << endl;////////////////////////////////
		} // fin del if
	} // fin de while
	
	
	// si el Grafo no es dirigido 
	if( !this->DIRIGIDO )
	{
		// recor_camino empieza en la cab de la lista de Caminos
		recor_camino = this->lista_caminos->getCab();
	
	
		// mientras recor_camino tenga dirección valida 
		while( recor_camino )
		{
			// travel_camino empieza en la cab de la lista de Caminos
			travel_camino = this->lista_caminos->getCab();
				
				
			// mientras travel_camino tenga dirección valida
			while( travel_camino )
			{
				// si recor_camino y travel_camino no son el mismo Caminos pero son
				//  Caminos exactamente iguales(mismos vertices) 
				if( !( *recor_camino->getInfo() == *travel_camino->getInfo() ) &&
					 recor_camino->getInfo()->iguales( travel_camino->getInfo(), true ) )
				{
					eliminar_camino = travel_camino; // se eliminara a travel_camino
					travel_camino = travel_camino->getLink_suc(); // travel_camino será sus sucesor
					this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
						ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos 
				}
				else // si no, entonces travel_camino no tiene menos Vertices que recor_camino
					travel_camino = travel_camino->getLink_suc();  // travel_camino será sus sucesor
			} // fin del while
			
				
			recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
		} // fin del while 
	} // fin del if
} // fin de buscarCaminos_maxVertices


/**
 *	@brief busca los Caminos con menor o mayor numero de vertices
 *	en el Grafo, segun sea especificado, lo hace
 *	sin repetir Vertices ni aristas, es decir
 *	sin formar ciclos, los Caminos resultantes seran guardados 
 *	en la lista de Caminos del Grafo 
 *	@param bool determina si se buscan Caminos de longitud
 *	minima o de longitud maxima, en el caso de que sea true
 *	o se omita el parámetro se buscaran Caminos de longitud minima,
 *	en caso contrario se buscaran Caminos de longitud maxima  
 *	@since 1.0
 */	
void Grafo::buscarCaminos_MinMaxVertices( bool min )
{
	Nodo<Camino>* recor_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* travel_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* eliminar_camino; // apuntador para eliminar Caminos
		
	
	// recor_camino empieza en la cab de la lista de Caminos
	recor_camino = this->lista_caminos->getCab();
	
	
	// mientras recor_camino tenga dirección valida 
	while( recor_camino )
	{
		// travel_camino empieza en la cab de la lista de Caminos
		travel_camino = this->lista_caminos->getCab();
				
				
		// mientras travel_camino tenga dirección valida
		while( travel_camino )
		{
			// si estoy buscando Caminos maximos y el Camino de recor_camino
			// tiene mayor longitud que el Camino de travel_camino
			if( ( !min && *travel_camino->getInfo() < *recor_camino->getInfo() ) ||
				( min && *recor_camino->getInfo() < *travel_camino->getInfo() ) )
			{
				eliminar_camino = travel_camino; // se eliminara a travel_camino
				travel_camino = travel_camino->getLink_suc(); // travel_camino será sus sucesor
				this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
					ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos 
			} // si no, entonces estoy buscando minimos
			else // si no, entonces travel_camino no tiene menos Vertices que recor_camino
				travel_camino = travel_camino->getLink_suc();  // travel_camino será sus sucesor
		} // fin del while
				
				
		recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
	} // fin del while	
} // fin de buscarCaminos_minMaxLongitud


/**
 *	@brief busca los Caminos con menor o mayor longitud
 *	en el Grafo, segun sea especificado, lo hace
 *	sin repetir Vertices ni aristas, es decir
 *	sin formar ciclos, los Caminos resultantes seran guardados 
 *	en la lista de Caminos del Grafo 
 *	nota: en caso de que el Grafo sea no dirigido, buscara los
 *	Caminos que tengan el numero de Vertices del Grafo
 *	nota: en caso de que el Grafo sea dirigido, buscara los
 *	Caminos con mayor cantidad de Vertices 
 *	nota: en caso de que el Grafo no sea ponderado solo
 *	se buscaran los Caminos con mayor cantidad de Vertices
 *	@param bool determina si se buscan Caminos de longitud
 *	minima o de longitud maxima, en el caso de que sea true
 *	o se omita el parámetro se buscaran Caminos de longitud minima,
 *	en caso contrario se buscaran Caminos de longitud maxima  
 *	@since 1.0
 */	
void Grafo::buscarCaminos_MinMaxLongitud( bool min )
{
	Nodo<Camino>* recor_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* travel_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* eliminar_camino; // apuntador para eliminar Caminos
	
	
	// si el Grafo es no ponderado
	if( !this->PONDERADO )
		return; // no hago busqueda de Caminos largos o cortos
		
	
	// recor_camino empieza en la cab de la lista de Caminos
	recor_camino = this->lista_caminos->getCab();
	
	
	// mientras recor_camino tenga dirección valida 
	while( recor_camino )
	{
		// travel_camino empieza en la cab de la lista de Caminos
		travel_camino = this->lista_caminos->getCab();
				
				
		// mientras travel_camino tenga dirección valida
		while( travel_camino )
		{
			// si estoy buscando Caminos maximos y el Camino de recor_camino
			// tiene mayor longitud que el Camino de travel_camino
			if( ( !min && *recor_camino->getInfo() > *travel_camino->getInfo() ) ||
				( min && *travel_camino->getInfo() > *recor_camino->getInfo() ) )
			{
				eliminar_camino = travel_camino; // se eliminara a travel_camino
				travel_camino = travel_camino->getLink_suc(); // travel_camino será sus sucesor
				this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
					ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos 
			} // si no, entonces estoy buscando minimos
			else // si no, entonces travel_camino no tiene menos Vertices que recor_camino
				travel_camino = travel_camino->getLink_suc();  // travel_camino será sus sucesor
		} // fin del while
				
				
		recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
	} // fin del while	
} // fin de buscarCaminos_minMaxLongitud


/**
 *	@brief buscas los caminos sin un vertice intermedio dado,
 *	los caminos resultantes son guardados en la lista de caminos 
 *	del grafo
 *	@param Vertice* vertice por el cual se van a filtrar los caminos
 *	@since 1.0
 */	
void Grafo::buscarCaminosSinVertice( Vertice* inter )
{

	Nodo<Camino>* travel_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* eliminar_camino; // apuntador para eliminar Caminos
		
		
	// travel_camino empieza en la cab de la lista de Caminos
	travel_camino = this->lista_caminos->getCab();
			
			
	// mientras travel_camino tenga dirección valida
	while( travel_camino )
	{
		// si estoy buscando Caminos maximos y el Camino de recor_camino
		// tiene mayor longitud que el Camino de travel_camino
		if( travel_camino->getInfo()->lista_vertices->buscar( inter ) )
		{
			eliminar_camino = travel_camino; // se eliminara a travel_camino
			travel_camino = travel_camino->getLink_suc(); // travel_camino será sus sucesor
			this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
				ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos 
		} // si no, entonces estoy buscando minimos
		else // si no, entonces travel_camino no tiene menos Vertices que recor_camino
			travel_camino = travel_camino->getLink_suc();  // travel_camino será sus sucesor
	} // fin del while
} // buscarCaminosSinVertice


/**
 *	@brief busca los Caminos con menor o mayor longitud
 *	en el Grafo, segun sea especificado, lo hace
 *	sin repetir Vertices ni aristas, es decir
 *	sin formar ciclos, los Caminos resultantes seran guardados 
 *	en la lista de Caminos del Grafo 
 *	nota: en caso de que el Grafo sea no dirigido, buscara los
 *	Caminos que tengan el numero de Vertices del Grafo
 *	nota: en caso de que el Grafo sea dirigido, buscara los
 *	Caminos con mayor cantidad de Vertices 
 *	nota: en cadp de que el Grafo no sea ponderado solo
 *	se buscaran los Caminos con mayor cantidad de Vertices
 *	@param bool determina si se buscan Caminos de longitud
 *	minima o de longitud maxima, en el caso de que sea true
 *	o se omita el parámetro se buscaran Caminos de longitud minima,
 *	en caso contrario se buscaran Caminos de longitud maxima  
 *	@since 1.0
 */	
void Grafo::buscarCaminos_MinMaxLongitud_Grafo( bool min )
{
	this->buscarCaminos_maxVertices(); // busca los Caminos con más Vertices 
	this->buscarCaminos_MinMaxLongitud( min ); // busca Caminos largos o cortos
} // fin de buscarCaminos_MinMaxLongitud_Grafo


/**
 *	@brief comprueba conectividad entre dos Vertices A y B 
 *	especificados, es decir, verifica si existe o no un Camino
 *	entre los Vertices A y B 
 *	nota: en caso de que el Grafo sea no dirigido, encontrara
 *	los Caminos si es que los hay entre A y B en todos los sentidos
 *	y los alamacenara en la lista de Caminos del Grafo
 *	nota: en caso de que el Grafo sea dirigido, comprobara
 *	si existe un Camino a partir de A que llegue a B y no al
 *	contrario, igualmente los Caminos se almacenaran en la lista 
 *	de Caminos del Grafo 
 *	@param Vertice* Vertice de partida para comprobar conectividad 
 *	@param Vertice* Vertice de llegada para comprobar conectividad   
 *	@since 1.0
 *	@return bool true si existe conectividad entre A y B, de 
 *	lo contrario false
 *	nota: en caso de que no exista el Vertices A especificado
 *	en el Grafo, la funcion retornara false, al igual que si 
 *	existiera pero el Grafo fuerá dirigido y este fuera un pozo
 */
bool Grafo::conectividad( Vertice* A, Vertice* B )
{
	// busco el Vertice A en el grafo y este sera mi Vertice de partida
	Nodo<Vertice>* partida = this->lista_adyacencia->buscar( A );
	Nodo<Camino>* recor; // Nodo para recorrer la lista de Caminos resultante
	Nodo<Camino>* travel; // Nodo para recorrer la lista de Caminos resultante
	Nodo<Camino>* eliminar; // apuntador para eliminar Caminos
	this->lista_caminos->eliminarLista(); // elimino lista de Caminos si es que la habia  


	// si el Vertice de partida se encuentra en la lista de adyacencia 
	if( partida )
	{	
		// agrego a la sublista de camino a partida 
		this->agregar_camino( NULL, partida );
		
		// recor empezara en la cab de la lista de Caminos
		recor = this->lista_caminos->getCab(); 
	

		// mientras recor tenga una direccion valida
		while( recor )
		{
			// si no se encontro a B en el Camino de recor
			if( !recor->getInfo()->eliminarListaVerticesDesde( B ) ) 
			{
				eliminar = recor; // eliminar sera recor
				recor = recor->getLink_suc(); // recor será su sucesor 
				this->lista_caminos->eliminar( // elimino a recor de la lista de Caminos 
					ListaD<Camino>::ELIM_ELEMENTO, eliminar->getInfo() ); // del Grafo 
			} // fin del if 
			else
				recor = recor->getLink_suc(); // recor será su sucesor 
		} // fin del while
	} // fin del if
	else
		return false; // no se encuentra Vertice A o es un pozo( con Grafo dirigido)
		
	
	// si la lista de Caminos esta vacia
	// ( no se encontro a B en ningun Camino partiendo de A ) 	
	if( this->lista_caminos->isVacia() )
		return false; // no hay conectividad
	else
	{
		this->actualizarCaminos(); // actualizo Caminos	
		
		// recor empieza en la cab de la lista de Caminos
		recor = this->lista_caminos->getCab();
	
	
		// mientras recor tenga dirección valida 
		while( recor )
			{
				// travel empieza en la cab de la lista de Caminos
				travel = this->lista_caminos->getCab();
				
				
				// mientras travel tenga dirección valida
				while( travel )
				{
					// si recor y travel no son el mismo Caminos pero son
					//  Caminos exactamente iguales(mismos vertices)
					if(  !( *recor->getInfo() == *travel->getInfo() ) &&
						 recor->getInfo()->iguales( travel->getInfo() ) )
					{
						eliminar = travel; // se eliminara a travel
						travel = travel->getLink_suc(); // travel será sus sucesor
						this->lista_caminos->eliminar( // elimino a eliminar de la lista de 
							ListaD<Camino>::ELIM_ELEMENTO, eliminar->getInfo() ); // Caminos 
					}
					else // si no, entonces travel y recor no son Caminso iguales
						travel = travel->getLink_suc();  // travel será sus sucesor
				} // fin del while
				
				
				recor = recor->getLink_suc(); // recor será su sucesor 
			} // fin del while
		
		
		return true; // si hay conectividad 
	} // fin del if...else
} // fin de conectividad


 /**
 *	@brief busca los Caminos con menor o mayor cantidad de vertices
 *	entre un par de Vertices dados segun se especifique, y obviando
 *  un vertice intermedio si se especifica. Lo hace
 *	sin repetir Vertices ni aristas, es decir
 *	sin formar ciclos, los Caminos resultantes seran guardados 
 *	en la lista de Caminos del Grafo 
 *	nota: en caso de que el Grafo no sea ponderado entonces
 *	se buscan todos los Caminos desde A hasta B
 *	@param Vertice* Vertice de partida 
 *	@param Vertice* Vertice de llegada  
 *	@param bool determina si se buscan Caminos con mayor numero de vertices o
 *	menor numero de vertices, en el caso de que sea true
 *	o se omita el parámetro se buscaran Caminos con la menor cantidad de vertices,
 *	en caso contrario se buscaran Caminos con la mayor cantidad de vertices  
 *	@since 1.1
 *	@return bool true si existe conectividad entre A y B, de 
 *	lo contrario false
 *	nota: en caso de que no exista el Vertices A especificado
 *	en el Grafo, la funcion retornara false, al igual que si 
 *	existiera pero el Grafo fuerá dirigido y este fuera un pozo
 */	
bool Grafo::buscarCaminos_MinMaxVertices_Vertices( Vertice* A, Vertice* B, bool min, Vertice* inter ) 
{
	// si existe conectividad entre A y B
	if( this->conectividad( A, B ) )
	{
		// si se especifico un vertice intermedio a obviar
		if( inter )
		{
			this->buscarCaminosSinVertice( inter );
		} // fin del if
		
		
		// busca los Caminos mas largos o cortos segun se especifico 
		this->buscarCaminos_MinMaxVertices( min );
		return true; 
	}
	else // si no, entonces no existe conectividad
		return false; // no existen Caminos entre A y B
} // fin de buscarCaminos_MinMaxVertices_Vertices

 
 /**
 *	@brief busca los Caminos con menor o mayor longitud
 *	entre un par de Vertices dados segun se especifique, lo hace
 *	sin repetir Vertices ni aristas, es decir
 *	sin formar ciclos, los Caminos resultantes seran guardados 
 *	en la lista de Caminos del Grafo 
 *	nota: en caso de que el Grafo no sea ponderado entonces
 *	se buscan todos los Caminos desde A hasta B
 *	@param Vertice* Vertice de partida 
 *	@param Vertice* Vertice de llegada  
 *	@param bool determina si se buscan Caminos de longitud
 *	minima o de longitud maxima, en el caso de que sea true
 *	o se omita el parámetro se buscaran Caminos de longitud minima,
 *	en caso contrario se buscaran Caminos de longitud maxima  
 *	@since 1.0
 *	@return bool true si existe conectividad entre A y B, de 
 *	lo contrario false
 *	nota: en caso de que no exista el Vertices A especificado
 *	en el Grafo, la funcion retornara false, al igual que si 
 *	existiera pero el Grafo fuerá dirigido y este fuera un pozo
 */	
bool Grafo::buscarCaminos_MinMaxLongitud_Vertices( Vertice* A, Vertice* B, bool min, Vertice* inter )
{
	// si existe conectividad entre A y B
	if( this->conectividad( A, B ) )
	{
		// si se especifico un vertice intermedio a obviar
		if( inter )
		{
			this->buscarCaminosSinVertice( inter );
		} // fin del if
		
		
		// busca los Caminos mas largos o cortos segun se especifico 
		this->buscarCaminos_MinMaxLongitud( min );
		return true; 
	}
	else // si no, entonces no existe conectividad 
		return false; // no existen Caminos entre A y B
} // fin de buscarCaminos_MinMaxLongitud_Vertices

/**
 *	@brief actualiza todos los Caminos
 *	en la lista de Caminos actual del Grafo 
 *	@since 1.0
 */	
void Grafo::actualizarCaminos()
{
	// recor empezara en la cab de la lista de Caminos
	Nodo<Camino>* recor = this->lista_caminos->getCab(); 
	
	
	// mientras recor tenga una direccion valida
	while( recor )
	{
		recor->getInfo()->actualizar(); // actualizo Camino
		recor = recor->getLink_suc(); // recor será su sucesor 
	} // fin del while
} // fin de actualizarCaminos


/**
 *	@brief imprime la lista de adyacencia en el flujo 
 *	std de salida
 *	@since 1.0	
 */	
void Grafo::imprimirListaAdyacencia() const
{
	// recor será la cab de la lista de adyacencia principal
	Nodo<Vertice>* recor = this->lista_adyacencia->getCab(); 
	
	
	// si la lista de adyacencia esta vacia
	if( this->lista_adyacencia->isVacia() )
	{
		cout << "NULL" << endl; // grafo vacio
		return; // retorno
	} // fin del if
	
	
	// mientras recor tenga direccion 
	while( recor )
	{
		cout << *recor->getInfo() << ": " << endl; // imprimo vertice
		recor->getInfo()->vertices_adyacentes->imprimir(); // imprimo sublista 
		recor = recor->getLink_suc(); // recor será su sucesor
	} // fin del while
} // fin de imprimirListaAdyacencia


/**
 *	@brief imprime la lista de Caminos en el flujo 
 *	std de salida
 *	@since 1.0	
 */	
void Grafo::imprimirListaCaminos() const
{
	// recor empezara en la cab de la lista de Caminos
	Nodo<Camino>* recor = this->lista_caminos->getCab(); 
	
	
	// si la lista de Caminos esta vacia 
	if( this->lista_caminos->isVacia() )
	{
		cout << "NULL" << endl; // lista vacia
		return; // retorno a quien hizo la llamada
	} // fin del if
	
	
	// mientras recor tenga una direccion valida
	while( recor )
	{
		// actualizo e impirmo Camino y su lista de Vertices
		recor->getInfo()->actualizar(); // actualizo camino ////////////////////////
		cout << *recor->getInfo() << ": " << endl;
		recor->getInfo()->lista_vertices->imprimir(); // lista de Vertices
		recor = recor->getLink_suc(); // recor será su sucesor 
	} // fin del while
} // fin de imprimirListaCaminos














