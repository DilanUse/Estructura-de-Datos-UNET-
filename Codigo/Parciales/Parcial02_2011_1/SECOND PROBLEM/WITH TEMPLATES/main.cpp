#include <iostream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Archivo.h"
#include "ListaD.h"
#include "Nodo.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// procesa los datos
void procesarDatos()
{
	ListaD<char>* lista_claves = new ListaD<char>( true, true ); // instancio lista doble
	string buffer; // almacena datos
	
	
	
	// crea la lista doblemente enlazada de letras
	Archivo* claves = new Archivo( "claves.txt" ); // asocio archivo claves.txt
	cout << claves->abrir() << endl << endl; // abro claves.txt
	
	
	// mientras no llegue al final de claves.txt
	while( !claves->isFinal() )
	{
		buffer = claves->leerCampo( ' ' ); // leo clave
		lista_claves->agregar( (char*)buffer.c_str(), ListaD<char>::AGRE_CRE, true ); // agrego clave a la lista
	} // fin del while
	
	lista_claves->imprimir();
	lista_claves->imprimir(true);
	
	delete claves; // libero recursos
	cout << endl << endl;
	
	
	// descifrar el mensaje
	Nodo<char>* clave = lista_claves->getCab(); // apunto a la cab de la lista
	Archivo* mensa = new Archivo( "mensa.txt" ); // asocio archivo mensa.txt
	Archivo* salida = new Archivo( "salida.txt" ); // asocio archivo salida.txt(no existe)
	int sentido; // sentido del recorrido
	int recorrido; // distancia(Nodos) a recorrer
	char clave_escribir; // clave a escribir en el archivo salida.txt
	
	
	cout << mensa->abrir() << endl; // aperturo mensa.txt
	cout << salida->crear() << endl; // creo salida.txt para escritura 
	
	
	// mientras no llegue al fin de mensa.txt
	while( !mensa->isFinal() )
	{
		buffer = mensa->leerCampo( ' ' ); // leo los tres digitos
		sentido = atoi( buffer.c_str() ) / 100; // obtengo sentido del recorrido
		recorrido = ( atoi( buffer.c_str() ) % 100 ) - 1; // obtengo la distancia
		
		
		// recorrido hasta la clave especificada por recorrido
		for( ; recorrido > 0; recorrido-- )
		{
			// si el sentido es a la dereche, clave sera su sucesor, de lo contrario, clave sera
			clave = ( sentido == 1 ? clave->getLink_suc() : clave->getLink_pre() ); // su predecesor
		} // fin del for 
		
		clave_escribir = clave->getInfo(); // obtengo clave del Nodo
		salida->escribir( clave_escribir ); // escribo clave en salida.txt
	} // fin del while
	
	
	salida->escribir( "", true ); // obligo al flujo a escribir
	
	
	delete mensa, salida; // libero recursos de archivos
} // fin de procesarDatos

int main(int argc, char** argv) 
{
	procesarDatos();
	return 0;
}
