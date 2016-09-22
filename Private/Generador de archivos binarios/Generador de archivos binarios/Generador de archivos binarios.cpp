// Generador de archivos binarios.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <vector>
#include "Datos.h"
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;


int main()
{
	ifstream in("NombresSimplesDesordenados.txt", ios::in);
	ofstream out( "datos.dat", ios::out | ios::binary );
	ifstream in_binary;
	vector<Datos>* datos = new vector<Datos>();
	string buffer;
	int cedulas[25];
	int cedula = 20000000;
	int cedula_aux;
	int count = 0;
	srand(time(NULL));



	for ( int i = 0; i < 25; i++)
	{
		cedula += 100000 + rand() % 1000000;
		cedulas[i] = cedula;
	}


	for ( int num,  i = 0; i < 25; i++)
	{
		num = rand() % 25;
		cedula_aux = cedulas[i];
		cedulas[i] = cedulas[num];
		cedulas[num] = cedula_aux;
	}


	if (in.fail() || out.fail() )
	{
		cout << "Fallo la apertura" << endl;
	}
	else
	{
		while (!in.eof())
		{
			getline(in, buffer, '\n');
			cout << buffer << ", " << cedulas[count] << endl;


			out.write((char*)(new Datos(buffer, cedulas[count])), sizeof(Datos));
			count++;

		}


		in.close();
		out.close();
		cout << "Salida exitosa" << endl;
		system("PAUSE");
//		system("cls");


		in_binary.open("datos.dat", ios::in | ios::binary);
		Datos dat;


		while (!in_binary.eof() )
		{
			
			in_binary.read((char*)&dat, sizeof(Datos));

			if (in_binary.eof())
				break;

			cout << dat.nombre << "," << dat.cedula << endl;

		}


		in_binary.close();



	} // fin del else



	cout << count << endl;
	system("PAUSE");


	



    return 0;
} // fin del main

