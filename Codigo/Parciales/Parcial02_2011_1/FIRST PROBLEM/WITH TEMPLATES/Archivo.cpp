#include "Archivo.h"
#include <iostream>

using namespace std; // uso del espacio de nombres std 


 /**
 *	@brief	inicializa el nombre del archivo asociado
 *	@since 1.0
 *	@param	string nombre del archivo asociado	
 */ 
Archivo::Archivo( string n ) : nombre( n ) {}


/**
 *	@brief	libera recursos del archivo asociado
 *	@since 1.0
 */
Archivo::~Archivo()
{
	if( this->flujo.is_open() ) // si el archivo asociado esta abieto
		this->flujo.close();    // cierra el archivo asociado, liberando el recurso
} // fin destructor Archivo 


/**
 *	@brief	retorna el nombre del archivo asociado
 *	@since 1.0
 *	@return	string nombre del archivo asociado
*/
string Archivo::getNombre() const
{
	return this->nombre;  // returna el nombre del archivo asociado
} // fin de getNombre

	
/**
 *	@brief	apertura el archivo, asociandolo con el flujo 
 *	@since 1.0
 *	@return	true apertura correcta, false error lógico
 */ 
bool Archivo::abrir() 
{
	// apertura el archivo con el nombre asociado
	this->flujo.open( this->nombre.c_str(), fstream::in ); 
		
	return !this->flujo.fail(); // retorna el exito de la apertura 
} // fin de abrir


/**
 *	@brief lee una linea del archivo asociado y la retorna en una cadena
 *	@since 1.0
 *	@return	string linea del archivo asociado leida
 */
string Archivo::leerLinea()
{
	string* linea = new string();  // linea a retornar 
	
	getline( this->flujo, *linea, '\n' );  // lee linea en el archivo asociado
	
	return *linea;  // retorna la linea leida del archivo asociado
} // fin de leerLinea


/**
 *	@brief	lee una linea del archivo asociado y la retorna sin
 *	el caracter delimitador especificado, eliminando todas las 
 *	apariciones del caracter en la cadena retornada
 *	@since 1.0
 *	@param	const char caracter a eliminar en la cadena
 *	@return	string contenido de la linea del archivo leida, 
 *	si se esta en el final del archivo retorna una cadena vacia
 */
 string Archivo::leerLinea( const char elim )
 {
	string* linea = new string();   // linea a retornar
	string* buffer = new string();  // subcadena temporal sin caracter especificado
	
    
    // mientras no este en el final del archivo y no este en el fin de linea 
	while( !this->flujo.eof() && !this->isFinLinea( elim ) )  
	{
		// lee subcadena sin caracter especificado
		getline( this->flujo, *buffer, elim );  
		*linea += *buffer; // concatena subcadenas sin el caracter especificado
	} // fin del while
	
	
	// si no se llegó al fin del archivo(se llego al fin de linea)
	if( !this->flujo.eof() )  
	{
		getline( this->flujo, *buffer, '\n' );  // lee hasta el fin de linea
		*linea += *buffer; // concatena ultima subcadena a la cadena a retornar
	} // fin del if 
	
	
	delete buffer; // libera memoria del buffer temporal
	return *linea; // retorna la cadena sin el caracter especificado
 } // fin de leerLinea
 
 
/**
 *	@brief lee un campo del archivo asociado hasta un caracter 
 *	delimitador especificado
 *	@since 1.0
 *	@param	const char delimitador para la lectura del campo
 *	@return	string campo leido en el archivo asociado,
 *	si se esta en el final del archivo retorna una cadena vacia
 */
 string Archivo::leerCampo( const char delim )
 {
	string* campo = new string();   // campo a retornar
	
	
	if( !this->flujo.eof() ) // si no estoy en el final del archivo asociado
		if( this->isFinLinea( delim ) ) // si el siguiente campo llega al fin de linea
			getline( this->flujo, *campo, '\n' ); // leo el campo hasta el fin de linea
		else // si el siguiente campo no llega al fin de linea
			getline( this->flujo, *campo, delim ); // leo campo hasta delimitador especificado
			
			
	return *campo;  // retorno campo leido del arhcivo asociado
 } // fin de leerCampo
 
 
 /**
 *	@brief lee los n campos en una linea del archivo asociado, 
 *	separados por un caracter delimitador especificado y los
 *	retorna por separado en un arreglo de cadenas
 *	@since 1.0
 *	@param	const char delimitador para la lectura de los campos
 *	@param	const unsigned int numero de campos a leer en la linea
 *	@return	string* campos leidos de la linea en el archivo asociado
 */
 string* Archivo::leerCampos( const char delim, const unsigned int num_campos )
 {
	string* campos = new string[num_campos]; // campos a retornar
	
	
	// para num_campos campos leo y almaceno por separado
	for( int campo = 0; campo < num_campos; campo++ )
		getline( this->flujo, campos[campo], // lee campo por campo hasta el final de linea
			( campo == num_campos - 1 ? '\n' : delim ) ); // deparando por delim
		
		
	return campos; // retorna arreglo con campos leidos 
 } // fin de leerCampos
 
 
 /**
 *	@brief	determina si en la siguiente lectura hasta el
 *	caracter delimitador especificaod se encuentra el caracter 
 *	de fin de linea 
 *	@since 1.0
 *	@param	const char delimitador para la siguiente lectura
 *	@return	true si se alcanza el fin de linea al leer, de lo contrario false
 */
bool Archivo::isFinLinea( const char delim )
{
	fstream flujoAux; // flujo de entrada auxiliar para hacer la siguiente lectura
	
	
	flujoAux.open( this->nombre.c_str(), fstream::in ); // apertura archivo asociando a flujo auxiliar
	flujoAux.seekg( this->flujo.tellg() ); // igualo la posición del flujo auxiliar al flujo principal
	
	string* lectura = new string(); // buffer para guardar lectura
 	
	getline( flujoAux, *lectura, delim ); // leo hasta delim
	flujoAux.close(); // cierro flujo auxiliar


	// evalua si en el campo leido se encuentra el caracter de fin de linea
	return ( lectura->find( '\n' ) == string::npos ? false : true );
} // fin de isFinLinea
 

/**
 *	@brief	determina si se llego al final del archivo asociado 
 *	@since 1.0
 *	@return	true si se alcanzo el final del archivo, de lo contrario false
 */
bool Archivo::isFinal() const
{
	// evalua si se llego al final del archivo asociado
	return this->flujo.eof();
} // fin de isFinal
 
 
 
 
 
 
 
 
 
 
 
 
 
