#include <iostream>
#include "Archivo.h"
#include "Arbol.h"
#include "Palabra.h"
#include "windows.h"
#include "ListaD.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



void llenarLista( NodoA<Palabra>* recor, ListaD<Palabra>* palabras )
{
	// si recor es NULL
	if( !recor )
	{
		return;
	} // fin del if
	
	
	palabras->agregar( new Palabra( *recor->getInfo() )  );
		
		
	// si el NodoA recor tiene hijo por la izquierda 
	if ( recor->getLink_hi() ) // paso recursivo para actualizar al hijo por la izquierda
		llenarLista( recor->getLink_hi(), palabras );
	
	
	// si el NodoA recor tiene hijo por la derecha
	if ( recor->getLink_hd() ) // paso recursivo para actualizar al hijo por la derecha
		llenarLista( recor->getLink_hd(), palabras );
		
		
} // fin de imprimir



int main(int argc, char** argv) 
{
	ListaD<Palabra>* lista = new ListaD<Palabra>();
	Arbol<Palabra>* arbol = new Arbol<Palabra>();
	Archivo* enunciado_txt = new Archivo("Enunciado.txt");	
	string buffer;
 
  	 
	
	enunciado_txt->abrir();
	
	
	while( !enunciado_txt->isFinal() )
	{
		buffer = enunciado_txt->leerCampo( ' ' );
		buffer = buffer.substr( 0, buffer.find( ',' ) );
		buffer = buffer.substr( 0, buffer.find( '.' ) );
		
		
		//cout << buffer << endl;
		Palabra* pal = new Palabra( buffer );
		//arbol->agregar( new Palabra( buffer )); 
		
		
		if ( arbol->agregar( pal )  == -1 )
		{
			arbol->buscar( pal )->getInfo()->ocurrencia++;
		}
	}
	
	
	//arbol->imprimir( arbol->getRaiz() );
	//arbol->llenarLista( arbol->getRaiz(), lista );
	llenarLista( arbol->getRaiz(), lista );
//	lista->imprimir();
	
	
	
	
	
	cout << "Lista de ocurrencia: " << endl;
	for( int x = 0; x < lista->getSize(); x++ )
	{
		cout << *lista->getElemento_info(x) << endl;
	}
	
	
	
	cout << endl << endl << "ingrese una palabra para eliminarla: ";
	getline( cin, buffer, '\n' );
	
	
	
	Palabra* palAux = new Palabra( buffer );
	
	
	
	if( arbol->eliminar( palAux ) == 1 )
	{
		cout << "palabra eliminada..." << endl;
		
		lista->eliminar( ListaD<Palabra>::ELIM_ELEMENTO, palAux );
	}
	else
		cout << "Palabra no encontrada..." << endl;
		
		
	lista->imprimir();
	
	
	
	
		
	return 0;
}
