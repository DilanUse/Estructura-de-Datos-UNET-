// Generador de archivos binarios.cpp : Defines the entry point for the console application.
//

/**
*	@Autor: Dilan Useche
*/

#include "stdafx.h"
#include <fstream>
#include <vector>
#include "Datos.h"
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std; // uso del espacio de nombres std


// funcion main que inicia la ejecución
int main()
{
	ifstream in("NombresSimplesDesordenados.txt", ios::in); // abre archivo de texto para lectura
	ofstream out( "datos.dat", ios::out | ios::binary ); // crea archivo binario para escritura
	ifstream in_binary; // flujo para leer archivo bonario
	vector<Datos>* datos = new vector<Datos>(); // lista de datos
	string buffer; // buffer auxiliar
	int cedulas[25]; // cedulas para los nombres
	int cedula = 20000000; // cedula actual
	int cedula_aux; // cedula para operaciones auxiliares
	int registro = 0; // cuenta los registros creados 
	srand(time(NULL)); // inicia semilla de rand con el tiempo actual
	cout << "Tamaño de la clase Datos: " << sizeof(Datos) << " Bytes" << endl << endl;


	// asigna 25 cedulas aleatorias sin repeticiones
	for ( int i = 0; i < 25; i++)
	{
		cedula += 100000 + rand() % 1000000;
		cedulas[i] = cedula; 
	} // fin del for


	// Mezcla la cedulas de forma aleatoria
	// nota: en el encabezado del for declaro a num y i
	// y inicia a i 
	for ( int num,  i = 0; i < 25; i++)
	{
		num = rand() % 25;
		cedula_aux = cedulas[i];
		cedulas[i] = cedulas[num];
		cedulas[num] = cedula_aux;
	} // fin del for


	// si no fallo la apertura o creacioón de ningun archivo
	if (in.fail() || out.fail() )
	{
		cout << "Fallo la apertura" << endl;
	} 
	else
	{
		cout << "*Antes de escribir en el archivo Binario:" << endl;
		// mientras no llegue al final del archivo
		while (!in.eof())
		{
			// leo del archivo de texto
			getline(in, buffer, '\n');
			cout << buffer << ", " << cedulas[registro] << endl;


			// escribo en el archivo binario
			out.write((char*)(new Datos(buffer, cedulas[registro])), sizeof(Datos));
			registro++;
		} // fin del while 


		// cierro los flujos de E/S
		in.close();
		out.close();
		cout << "Salida exitosa..." << endl;
		system("PAUSE");


		cout << endl << "*Despues de escribir en el archivo Binario(leyendo contenido escrito):" << endl;
		in_binary.open("datos.dat", ios::in | ios::binary); // abro archivo binario para lectura
		Datos dat; // buffer para los Datos(registros)


		// lee y muestra el contenido del archivo del binario
		while ( true )
		{
			in_binary.read((char*)&dat, sizeof(Datos));


			// si llego al final del archivo me salgo
			if (in_binary.eof())
				break;


			cout << dat.nombre << "," << dat.cedula << endl;
		} // fin del while


		in_binary.close(); // cierro flujo de entrada
	} // fin del else


	cout << endl << "Registros creado:" << registro << endl; // muetra los registros creados
	system("PAUSE");


    return 0;
} // fin del main

