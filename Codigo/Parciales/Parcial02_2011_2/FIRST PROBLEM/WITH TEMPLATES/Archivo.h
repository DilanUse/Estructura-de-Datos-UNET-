/**
 *	@Autor: Dilan Useche
 *	@Date: 2/19/2016
 *	@Release: 10/3/2016
 *	@Version: 1.1
 */


#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <string>
#include <fstream>
#include <iostream>


/**
 *	@brief manipula la lectura y escritura de un archivo de texto asociado.
 *	Además realiza operaciones con los datos leidos o a escribir
 *	en el archivo de texto.    
 */
class Archivo
{
	private:
		std::string nombre; // nombre del archivo asociado
		std::fstream flujo; // flujo de entrada/salida al archivo asociado	
		
		// determina si en la siguiente lectura hasta el caracter delimitador 
		// especificado se encuentra el caracter de fin de linea 
		bool isFinLinea( const char );		
	
	
	public:
		explicit Archivo( std::string ); // inicializa nombre del archivo asociado
		~Archivo(); // libera recursos del archivo asociado
		//std::fstream getFlujo() const; // retorna el flujo del archivo asociado
		std::string getNombre() const; // retorna el nombre del archivo asociado
		bool abrir(); // apertura el archivo, asociandolo con el flujo 
		bool crear(); // crea un nuevo archivo, con el nombre asociado
		std::string leerLinea(); // lee linea del archivo asociado y la retorna
		// lee una linea del archivo asociado y la retorna 
		std::string leerLinea( const char ); // sin el caracter especificado
		// lee un campo del archivo asociado hasta un caracter 
		std::string leerCampo( const char ); // delimitador especificado
		// lee los n campos en una linea del archivo asociado, separados por un caracter
		// delimitador especificado y los retorna por separado en un arreglo de cadenas
		std::string* leerCampos( const char, const unsigned int );
		template<class T> bool escribir( T&, bool finLinea = false ); // escribe en el archivo asociado  
		bool isFinal() const; // determina si se llego al final del archivo asociado
		
}; // fin de Archivo


/**
 *	@brief	escribe cualquier tipo de dato en el archivo asociado
 *	nota: para obligar al buffer a escribir se debe indicar true 
 *	al parámetro finLinea
 *	@since 1.1
 *	@param T& datos a escribie en el archivo asociado
 * 	@param bool true: añade fin de linea en el archivo asoaciado, 
 *	luego de escribir en el mismo, de lo contrario no lo añadirá
 *	@return bool true escritura exitosa, false error logico
*/
template<class T> bool Archivo::escribir( T& datos, bool finLinea )
{
	// si el archivo esta abierto
	if( this->flujo.is_open() )
	{
		this->flujo << datos; // escribo datos en el archivo asociado
		
		// si se quiere añadir salto de linea
		if( finLinea ) 
			this->flujo << std::endl; // escribo fin de linea en el archivo asociado
	}
	else // si no esta abierto el archivo
		return false; // no se puede escribir en archivo cerrado
		
	return true; // exito al escribir
} // fin de escribir


#endif
