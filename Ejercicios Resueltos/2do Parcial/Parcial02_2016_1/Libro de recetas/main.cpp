#include <iostream>
#include <string>
#include <windows.h>
#include "ListaD.h"
#include "Archivo.h"
#include "Receta.h"
#include "Ingrediente.h"
#include "Nodo.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv)
{
	ListaD<Receta>* recetas = new ListaD<Receta>();
	Archivo* libro_txt = new Archivo("Libro.txt");
	libro_txt->abrir(); 
	string* buffer;
	
	
	while( !libro_txt->isFinal() )
	{
		 buffer = libro_txt->leerCampos( ',', 3 );
		 recetas->agregar( new Receta( atoi( buffer[0].c_str() ), buffer[1] , atoi( buffer[2].c_str() )) );
	}
	
	
	delete libro_txt;
	
	
	Archivo* ingrediente_txt = new Archivo("Ingrediente.txt");
	ingrediente_txt->abrir();
	bool continuar;
	Ingrediente* ingredAux; 
	string linea;
	string nom;
	int cal;
	int codigo;
	
	
	
	while( !ingrediente_txt->isFinal() )
	{ 
		linea = ingrediente_txt->leerLinea();
		
		nom = linea.substr(0, linea.find(','));
		linea = linea.substr( linea.find(',') + 1 );
		cal = atoi( linea.substr(0, linea.find(',')).c_str() );
		linea = linea.substr( linea.find(',') + 1 );
		
		ingredAux = new Ingrediente( nom, cal );
		
		continuar = true;
		
		
		while( continuar )
		{
			if ( linea.find(',') == string::npos )  
				continuar = false;
			
			
			
			codigo = atoi( linea.substr(0, linea.find(',')).c_str() );
			linea = linea.substr( linea.find(',') + 1);
			
			
			
			for( int x = 0; x < recetas->getSize(); x++ )
			{
				if( recetas->getElemento_info(x)->codigo == codigo )
				{
		//			recetas->getElemento_info(x)->ingredientes->agregar(ingredAux); 
					recetas->getElemento_info(x)->ingredientes->agregar( new Ingrediente(*ingredAux) ); 
				}
			}
				
		} // fin del while
	} // fin del while 	
	
	recetas->imprimir();
	cout << endl;
	
	
	for( int x = 0; x < recetas->getSize(); x++ )
	{
		recetas->getElemento_info(x)->ingredientes->imprimir();
	}
	
	
	
	ingredAux = new Ingrediente();
	Nodo<Ingrediente>* nodoIngAux;
	Nodo<Receta>* nodoRecAux;
	Receta*  recAux = new Receta(); 
	cout << endl << endl;
	cout << "Ingrese el codigo de una receta... ";
	recetas->imprimir();
	cout << "Codigo: ";
	cin >> codigo;
	
	
	recAux->codigo = codigo;
	nodoRecAux = recetas->buscar(recAux);
	
	
	if( nodoRecAux )
	{
		cout << "Lo ingredientes de la receta son: " << endl;
		nodoRecAux->getInfo()->ingredientes->imprimir();
		
		
		cout << "Desea modificar las calorias totales(Ingrese 1)" << endl;
		cout <<  "Dese modificar las calorias de un ingrediente(Ingrese 2)" << endl;
		cin >> codigo;
		
		
		if( codigo == 1 )
		{
			cout << "Ingrese las calorias de la receta: ";
			cin >> cal;
			
			nodoRecAux->getInfo()->calorias = cal;
		}else if( codigo == 2 )
		{
			cout << "Ingrese el nombre del ingrediente: ";
			cin >> nom;
			
			ingredAux->nombre = nom;
			nodoIngAux = nodoRecAux->getInfo()->ingredientes->buscar( ingredAux );
			
			
			if( nodoIngAux )
			{
				cout << "Ingrese las calorias del ingrediente: ";
				cin >> cal;
			
				nodoIngAux->getInfo()->calorias = cal;
			}
			else
			{
				cout << "El ingrediente seleccionado no existe..." << endl;
			}
			
			
		}
		else
			cout << "No modifico nada..." << endl;
		
		
	}
	else
		cout << "No existe la receta seleccionada..." << endl;
				
		
		
	recetas->imprimir();
	cout << endl;
	
	
	for( int x = 0; x < recetas->getSize(); x++ )
	{
		recetas->getElemento_info(x)->ingredientes->imprimir();
	}
	
	
	
	
	
	return 0;
}
