#include <iostream>
#include <string>
#include <cstdlib>
#include "Archivo.h"
#include "ColaD.h"
#include "Nodo.h"
#include "Customer.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// procesa los datos
void procesarDatos()
{
	ColaD<Customer>* cola_clientes = new ColaD<Customer>(); // instancio cola
	string* buffer; // almacena campos de archivos
	int cant_producto; // cantidad en existencia del producto
	
	
	cout << "Ingrese la cantidad en existencia del producto: ";
	cin >> cant_producto; 
	
	
	
	// crear la cola
	Archivo* cola_txt = new Archivo( "cola.txt" ); // asocio archivo cola.txt
	
	
	cout << "cantidad producto: " << cant_producto << endl; // muestro cantidad
	cout << cola_txt->abrir() << endl; // aperturo cola.txt
	
	
	// mientras no llegue al final de cola.txt
	while( !cola_txt->isFinal() )
	{
		buffer = cola_txt->leerCampos( ',', 2 ); // obtengo campos de cola.txt
		
		cola_clientes->agregar( new Customer( atoi(buffer[0].c_str()), atoi(buffer[1].c_str()) ));
	} // fin del while  
	
	
	cola_clientes->imprimir(); // imprimo la cola
	
	delete cola_txt; // libero recursos del archivo
	
	

	// eliminar de la cola(procesar cientes)
	Nodo<Customer>* cliente; // apunta al cliente que se procesa
	
	
	cout << endl << endl <<  "Procesamiento..." << endl;
	cout << "Unidades en existencia: " << cant_producto << endl << endl;
	// mientras se pueda seguir despachando un cliente 
	while( true )
	{
		cliente = cola_clientes->getFrente(); // proceso cliente por el frente de la cola
		
		
		// si quedan suficientes unidades para despachar al cliente
		if( cant_producto - cliente->getInfo(true)->buyAmount >= 0 )
		{
			cout << "Unidades en existencia: " << cant_producto << endl;
			cout << "*)cliente: " << cliente->getInfo() << endl << endl;
			
			cant_producto -= cliente->getInfo(true)->buyAmount; // resto unidades vendidas
			cola_clientes->eliminar(); // despacho cliente en el frente 
		} // fin de if
		else
			break; // termino proceso de despacho
	} // fin del while
	
	
	cout << endl << endl << "Unidades en existencia: " << cant_producto << endl;
	cout << "Clientes sin despachar: " << endl;
	cola_clientes->imprimir(); // imprimo clientes que qeudaron en la cola
} // fin de procesarDatos


int main(int argc, char** argv)
{
	procesarDatos();
	return 0;
}
