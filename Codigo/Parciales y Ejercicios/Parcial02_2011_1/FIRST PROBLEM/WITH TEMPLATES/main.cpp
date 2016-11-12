#include <iostream>
#include <string>
#include <cstdlib>
#include "ListaD.h"
#include "Nodo.h"
#include "Archivo.h"
#include "ProcessingLine.h"
#include "RawMaterial.h"
 using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// procesa y realiza operaciones con los datos
void procesarDatos()
{
	// crear el primer nivel de la estructura
	ListaD<ProcessingLine>* processingLines = new ListaD<ProcessingLine>(); // nivel 1 de la lista 
	string* campos; // buffer para campos del archivo
	Archivo* nivel = new Archivo( "nivel.txt" ); // archivo de texto nivel.txt
	cout << "Aperura: " << nivel->abrir() << endl; // apertura nivel.txt
	
	
	// mientras no llegue al final de nivel.txt
	while( !nivel->isFinal() ) 
	{
		campos = nivel->leerCampos( ',', 2 ); // leo linea y obtengo array de dos campos
		processingLines->agregar( new ProcessingLine( atoi(campos[0].c_str()), campos[1] ), // instancio y agrego 
			ListaD<ProcessingLine>::AGRE_FIN ); // nuevo objeto ProcessingLine con campos leidos de nivel.txt
	} // fin del while
	
	processingLines->imprimir(); // imprimo nivel 1 de la lista
	processingLines->imprimir(0); // imprimo nivel 1 de la lista
	cout << endl << endl;
	
	delete nivel; // libero recursos asociados al archivo nivel.txt
	
	
	// creando segundo nivel 
	Nodo<ProcessingLine>* nivel1; // Apuntador a Nodo del primer nivel
	RawMaterial* raw; // Apuntador a objetos a agregar en la sublistas
	Archivo* data = new Archivo( "data.txt" ); // archivo de etexto data.txt
	cout << "Apertura: " << data->abrir() << endl << endl; // aperturo data.txt
	
	
	// mientras no llegue al final de data.txt
	while( !data->isFinal() )
	{
		campos = data->leerCampos( ',', 4 ); // leo linea y obtengo array de 4 campos
		raw = new RawMaterial( atoi(campos[0].c_str()), campos[1], // instancio nuevo objeto RawMaterial
			atof(campos[2].c_str()), atoi(campos[3].c_str()) ); // con campos leidos de data.txt
		nivel1 = processingLines->getCab(); // apunto al inicio del nivel 1 de la lista
		
		// mientras apunte a un Nodo del nivel 1 de la lista
		while( nivel1 )
		{
			// si el nivel de pureza del material es igual al de la linea de procesamiento
			if( raw->purityLevel == nivel1->getInfo().purityLevel )
			{
				// agrego el material a esa linea de procesamiento
				nivel1->getInfo(true)->materials->agregar( raw, ListaD<RawMaterial>::AGRE_FIN );
				break; // salgo del ciclo
			}
				
			nivel1 = nivel1->getLink_suc(); // ahora apunto al siguiente Nodo del nivel1 de la lista
		} // fin del while
	} // fin del while
	
	
	// imprimo Los dos niveles
	nivel1 = processingLines->getCab();
	
	// mientras apunte a un Nodo del nivel 1 de la lista
	while( nivel1 )
	{
		cout << "*)" << nivel1->getInfo() << ": " << endl;
		nivel1->getInfo(true)->materials->imprimir();
		nivel1 = nivel1->getLink_suc();
	} // fin del while
} // 


int main(int argc, char** argv) 
{
	procesarDatos();	
	return 0;
}
