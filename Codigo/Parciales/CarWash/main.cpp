#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include "Archivo.h"
#include "Nodo.h"
#include "ColaD.h"
#include "ListaD.h"
#include "Personal.h"
#include "Vehiculo.h"


using namespace std; // uso del espacio de nombres std

int main(int argc, char** argv) 
{
	// creo objetos para leer de los archivos 
	Archivo* personal_txt = new Archivo("Personal.txt");
	Archivo* vehiculo_txt = new Archivo("Vehiculo.txt");
	string* buffer; // buffer para leer campos de los archivos	
	
	
	// creo estructuras de datos
	ListaD<Personal>* personal_lista = new ListaD<Personal>(); // lista de perosnal
	ColaD<Vehiculo>* vehiculos_cola = new ColaD<Vehiculo>(); // cola de espera de vehiculos
	
	
	// abro los archivos de texto
	personal_txt->abrir();
	vehiculo_txt->abrir();
	
	
	// creo la lista de personal	
	while( !personal_txt->isFinal() )
	{
		buffer = personal_txt->leerCampos( ' ', 2 ); // leo campos de cada linea
		personal_lista->agregar( new Personal( atoi( buffer[0].c_str()), buffer[1] ),
									ListaD<Personal>::AGRE_FIN ); // agrego nuevo personal
	} // fin del while
	
	
	// creo la cola de espera de vehiculos	
	while( !vehiculo_txt->isFinal() )
	{
		buffer = vehiculo_txt->leerCampos( ' ', 2 ); // leo campos de cada linea
		vehiculos_cola->agregar( new Vehiculo( buffer[0], buffer[1]) ); // agrego nuevo vehiculo a la cola
	} // fin del while
	
	
	
	char respuesta; // almacena la respuesta del usuario
	bool salir = false; // determina si se debe salir del menu
	int idSeleccionado; // id del personal seleccionado por el usuario
	Nodo<Personal>* personalAux_nodo; // nodo auxuliar de tipo personal
	Personal* personalAux = new Personal(); // personal auxliar 
	int montoTotalRecaudado = 0; 
	int GananciaTotal = 0;
	  	
		
	// while para el menu
	while( !salir )
	{
		system("cls"); // limpia el menu
		cout << "**AUTOLAVADO CARWASH**" << endl << endl;
		cout << "a) Iniciar servicio de lavado de un vehiculo" << endl;
		cout << "b) Finalizar servicio de lavado de un vehiculo" << endl;
		cout << "c) Consultar datos administrativos" << endl;
		cout << "d) Visulaizar cola de espera y lista de personal" << endl;
		cout << "e) Salir" << endl;
		cout << "-Su opcion: ";
		cin >> respuesta;
		
		
		// Muestra el menu de la aplicación
		switch( respuesta )
		{
			// iniciar servicio de lavado de un vehiculo
			case 'A':
			case 'a':
				cout << endl << "*Personal desocupado: " << endl;
							
				// muestro el personal desocupado en la lista de personal
				for( int x = 0; x < personal_lista->getSize(); x++ )
				{
					// si el personal en la pos x esta desocupado
					if( personal_lista->getElemento_info(x)->vehAsignado == NULL )
						cout << *personal_lista->getElemento_info(x) << endl;
				} // fin del for			
				
				cout << "Seleccione el id de un personal: ";
				cin >> idSeleccionado;
				
				personalAux->id = idSeleccionado; // asigno id seleccionado al personal auxiliar
				personalAux_nodo = personal_lista->buscar( personalAux ); // busco personal con id seleccionado
				
				// si no hay vehiculos en espera
				if( vehiculos_cola->getFrente() == NULL )
				{
					cout << "No hay mas vehiculos en la cola de espera..." << endl;
					system("PAUSE");
					break;
				} // fin del if
					
				// si se encontro el personal con el id seleccionado y esta desocupado
				if( personalAux_nodo != NULL && personalAux_nodo->getInfo()->vehAsignado == NULL )
				{
					// asigno al personal seleccionado el primer vehiculo en la cola
					personalAux_nodo->getInfo()->vehAsignado = vehiculos_cola->getFrente()->getInfo();
					vehiculos_cola->eliminar(); // elimino el vehiculo de la cola de espera 
					
					cout << "Vehiculo asignado al personal seleccionado..." << endl;
				} 
				else // si no, entonces no se encontro
					cout << "El id seleccionado no corresponde al personal..." << endl;
									
				system("PAUSE");
				break; // fin del case 1(iniciar servicio de lavado de un vehiculo)
				
			
			// finalizar servicio de lavado de un vehiculo 
			case 'B':
			case 'b':
				cout << endl << "*Vehiculos en proceso de lavado: " << endl;
							
				// muestro el personal ocupado en la lista de personal
				for( int x = 0; x < personal_lista->getSize(); x++ )
				{
					// si el personal en la pos x esta ocupado
					if( personal_lista->getElemento_info(x)->vehAsignado != NULL )
					{
						cout << *personal_lista->getElemento_info(x) << endl;
					}
				} // fin del for			
				
				cout << "Seleccione el id del personal para finalizar el lavado: ";
				cin >> idSeleccionado;
				
				personalAux->id = idSeleccionado; // asigno id seleccionado al personal auxiliar
				personalAux_nodo = personal_lista->buscar( personalAux ); // busco personal con id seleccionado
					
				// si se encontro el personal con el id seleccionado y esta ocupado
				if( personalAux_nodo != NULL && personalAux_nodo->getInfo()->vehAsignado != NULL )
				{
					// asigno al vehiculo del personal seleccionado NULL para desocuparlo
					personalAux_nodo->getInfo()->vehAsignado = NULL;
					
					// acumulo ganancias por lavado
					personalAux_nodo->getInfo()->ganancias += 150; // asigno 10% del pago al lavador
					montoTotalRecaudado += 1500; // acumulo el total recaudado
					GananciaTotal += 1350; // acumulo las ganancias
					cout << "Lavado finalizado y facturado..." << endl;
				} 
				else // si no, entonces no se encontro
					cout << "El id seleccionado no corresponde al personal..." << endl;
									
				system("PAUSE");
				break; // fin del case 2(iniciar servicio de lavado de un vehiculo)
			
			
			// consultar datos administrativos 	
			case 'C':
			case 'c':
				cout << endl << "*Datos administrativos:" << endl;
				
				cout << "Monto total recaudado: " << montoTotalRecaudado << endl;
				cout << "Ganancias totales: " << GananciaTotal << endl;
				cout << "Recaudado por vendedor: " << endl;
				
				// muestro el personal y sus ganancias
				for( int x = 0; x < personal_lista->getSize(); x++ )
					cout << personal_lista->getElemento_info(x)->nombre << " : " <<
						personal_lista->getElemento_info(x)->ganancias << "$" << endl;
						
				system("PAUSE");
				break; // fin del case 3( consultar datos administrativos )
				
				
			// visualizar cola de espera y lista de personal
			case 'D':	
			case 'd':
				cout << endl << "*Lista de personal: " << endl;
				personal_lista->imprimir();
				cout << endl << endl;
				cout << "*Cola de vehiculos en espera: " << endl;
				vehiculos_cola->imprimir();
				system("PAUSE");
				break; // fin del case 4(visualizar cola de espera y lista de personal)
			
			
			// salir
			case 'E':	
			case 'e':
				salir = true;
				break; // fin del case 5(Salir)
			
			
			// todas las demas opciones
			default:
				cout << "Opcion no valida, ingrese de nuevo..." << endl;
				system("PAUSE");
				break; // fin de default(todas las demas opciones)		
		} // fin del switch del menu
	} // fin del while del menu
	return 0;
} // fin del main
