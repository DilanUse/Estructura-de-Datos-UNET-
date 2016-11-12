#include <iostream>
#include <string>
#include <windows.h>
#include "ListaD.h"
#include "ColaD.h"
#include "Operacion.h"
#include "TipoOperacion.h"
#include "Nodo.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) 
{
	string operaciones, operacion;
	ListaD<TipoOperacion>* operaciones_list = new ListaD<TipoOperacion>();
	bool continuar = true;
	int num1;
	int num2;
	TipoOperacion* suma = new TipoOperacion('+');
	TipoOperacion* resta = new TipoOperacion('-');
	TipoOperacion* producto = new TipoOperacion('*');
	TipoOperacion* cociente = new TipoOperacion('/');
	Nodo<TipoOperacion>* aux_nodo;
	
	
	cout << "Ingrese las operaciones a realizar: " << endl;
	cin >> operaciones;
	
	
	
	while( continuar )
	{
		if ( operaciones.find(',') == string::npos )
			continuar = false;
			
			
		operacion = operaciones.substr(0,operaciones.find(','));
		operaciones = operaciones.substr(operaciones.find(',') + 1);
		
		
		
		if(operacion.find('+') != string::npos)
		{
			num1 = atoi( operacion.substr( 0, operacion.find('+')).c_str() );
			num2 = atoi( operacion.substr( operacion.find('+') + 1 ).c_str() );
			
			aux_nodo = operaciones_list->buscar(suma);
			
			if( !aux_nodo )
			{
				operaciones_list->agregar(suma);
				aux_nodo = operaciones_list->buscar(suma);
			}
			
			aux_nodo->getInfo()->colaOperacion->agregar( new Operacion( num1, num2, '+' ) );
			
		}			
		else if( operacion.find('-') != string::npos )
		{
			num1 = atoi( operacion.substr( 0, operacion.find('-')).c_str() );
			num2 = atoi( operacion.substr( operacion.find('-') + 1 ).c_str() );
			
			aux_nodo = operaciones_list->buscar(resta);
			
			if( !aux_nodo )
			{
				operaciones_list->agregar(resta);
				aux_nodo = operaciones_list->buscar(resta);
			}
			
			aux_nodo->getInfo()->colaOperacion->agregar( new Operacion( num1, num2, '-' ) );
			
		}
		else if( operacion.find('*') != string::npos )
		{
			num1 = atoi( operacion.substr( 0, operacion.find('*')).c_str() );
			num2 = atoi( operacion.substr( operacion.find('*') + 1 ).c_str() );
			
						
			aux_nodo = operaciones_list->buscar(producto);
			
			if( !aux_nodo )
			{
				operaciones_list->agregar(producto);
				aux_nodo = operaciones_list->buscar(producto);
			}
			
			aux_nodo->getInfo()->colaOperacion->agregar( new Operacion( num1, num2, '*' ) );
		}
		else
		{
			num1 = atoi( operacion.substr( 0, operacion.find('/')).c_str() );
			num2 = atoi( operacion.substr( operacion.find('/') + 1 ).c_str() );
			
			
			aux_nodo = operaciones_list->buscar(cociente);
			
			if( !aux_nodo )
			{
				operaciones_list->agregar(cociente);
				aux_nodo = operaciones_list->buscar(cociente);
			}
			
			aux_nodo->getInfo()->colaOperacion->agregar( new Operacion( num1, num2, '/' ) );
		} // fin del if...else		
	} // fin del while}
	
	
	operaciones_list->imprimir();
	
	
	for( int x = 0; x < operaciones_list->getSize(); x++)
	{
		operaciones_list->getElemento_info(x)->colaOperacion->imprimir();
	}
	
	
	
	for( int x = 0; x < 4; x++ )
	{
	
		if( x == 0)
			aux_nodo = operaciones_list->buscar(producto);
		else if( x == 1)
			aux_nodo = operaciones_list->buscar(cociente);
		else if( x == 2)
			aux_nodo = operaciones_list->buscar(suma);
		else
			aux_nodo = operaciones_list->buscar(resta);
		
		
	 	// si hay multiplicaciones
		if( aux_nodo )
		{
			while( !aux_nodo->getInfo()->colaOperacion->isVacia() )
			{
				cout << *aux_nodo->getInfo()->colaOperacion->getFrente()->getInfo();
				cout <<  ": " << aux_nodo->getInfo()->colaOperacion->getFrente()->getInfo()->getOperacion() << endl;
				aux_nodo->getInfo()->colaOperacion->eliminar();
			}
		}
	}
	
	 system("PAUSE");
	 return 0;
	
}
