#include <iostream>
#include "Arbol.h"
#include "Archivo.h"
#include "ListaD.h"
#include "Vehiculo.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) 
{
	Archivo clave_txt( "clave.txt" );
	Arbol<Vehiculo> vehiculos_arb( true );
	string* buffer;
	
	
	clave_txt.abrir();
	
	
	while( !clave_txt.isFinal() )
	{
		buffer = clave_txt.leerCampos( ',', 2 );
		vehiculos_arb.agregar( new Vehiculo( buffer[0], buffer[1] ));
	}
	
	
	vehiculos_arb.imprimir( vehiculos_arb.getRaiz() );
	
	
	
	int nivel = 0;
	cout << "ingrese un numero de nivel: ";
	cin >> nivel;
	
	
	
	// si el nivel esta dentro de la altura del arbol
	if( nivel <= vehiculos_arb.getAltura() )
	{
		vehiculos_arb.imprimir( vehiculos_arb.getRaiz(), nivel );
	}
	else
		cout << "El nivel ingresado esta fuera del arbol..." << endl;
	
	
	
	
	int nodosIzq;
	int nodosDer;
	string placa; 
	NodoA<Vehiculo>* nodoAux;
	
	
	cout << endl << endl << "Ingrese una placa por teclado: ";
	cin >> placa;
	Vehiculo* vehAux = new Vehiculo( placa, "" );
	
	
	nodoAux = vehiculos_arb.buscar( vehAux );
	
	
	// si se encontro el vehiculo con la placa especificada
	if( nodoAux )
	{
		nodosIzq = vehiculos_arb.getCantDesc( nodoAux->getLink_hi() );
		nodosDer = vehiculos_arb.getCantDesc( nodoAux->getLink_hd() );
		
		cout << "SubArbolIzq: " << nodosIzq << endl;
		cout << "SubArbolDer: " << nodosDer << endl;
		
		
		if( nodosIzq > nodosDer )
		{
			cout << "se imprime el subArbol izquierdo..." << endl;
			vehiculos_arb.imprimir( nodoAux->getLink_hi() );
		}
		else
		{
			cout << "se imprime el subArbol derecho..." << endl;
			vehiculos_arb.imprimir( nodoAux->getLink_hd() );
		}
	
	}
	else
		cout << "La placa ingresada no existe en el arbol..." << endl;
	
	
	return 0;
}
