#include <iostream>
#include "Archivo.h"
#include "Arbol.h"
#include <string>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) 
{
	string buffer; 
	Arbol<int>* claves_arbol = new Arbol<int>();
	Archivo* claves_txt = new Archivo("claves2.txt");
	claves_txt->abrir();
	
	
	while( !claves_txt->isFinal() )
	{
		
		buffer = claves_txt->leerCampo( ' ' );
		claves_arbol->agregar( new int( atoi( buffer.c_str()) ) );
//		claves_arbol->agregar( new Persona( atoi( buffer[0] ), buffer[1])  );
	}
	
	
	claves_arbol->imprimir( claves_arbol->getRaiz() );
	cout << endl << endl << claves_arbol->getAltura() << endl;
	cout << claves_arbol->isCompleto( claves_arbol->getRaiz() ) << endl;
	
	
	
	return 0;
}
