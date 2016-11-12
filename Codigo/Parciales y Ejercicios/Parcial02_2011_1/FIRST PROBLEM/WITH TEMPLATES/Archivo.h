/**
 *	@Autor: Dilan Useche
 *	@Date: 2/19/2016
 *	@Release: 2/25/2016
 *	@Version: 1.0
 */


#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <string>
#include <fstream>


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
		std::string leerLinea(); // lee linea del archivo asociado y la retorna
		// lee una linea del archivo asociado y la retorna 
		std::string leerLinea( const char ); // sin el caracter especificado
		// lee un campo del archivo asociado hasta un caracter 
		std::string leerCampo( const char ); // delimitador especificado
		// lee los n campos en una linea del archivo asociado, separados por un caracter
		// delimitador especificado y los retorna por separado en un arreglo de cadenas
		std::string* leerCampos( const char, const unsigned int );  
		bool isFinal() const; // determina si se llego al final del archivo asociado 
};

#endif
