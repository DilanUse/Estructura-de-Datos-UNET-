// MinMax(4 capas con hilos).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// algoritmo heuristico

#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include <thread>
using namespace std;


int matriz[6][7]; // matriz del juego


// imprime la matriz del juego
void imprimir( int matriz[6][7] )

{

	for (int j = 0; j< 7; j++)
		cout << j << "|  ";

	cout << endl;

	for (int j = 0; j< 7; j++)
		cout << "----";

	cout << endl;

	for (int i = 0; i< 6; i++) {
		for (int j = 0; j< 7; j++) 
		{
			if (matriz[i][j] == 0)
				cout << "*   ";
			else
				
				cout << matriz[i][j] << "   ";
		}
		cout << endl << endl;
	} // fin del for
} // fin de imprimir


// verifica si la columna dada esta llena
int llena( int x, int matriz[6][7])
{
	if (matriz[0][x] != 0) 
	{
		return -1;
	}
} // fin de llena


  // borra una jugada
void borrar(int colu, int matriz[6][7] )
{
	for (int i = 0; i<6; i++)
		if (matriz[i][colu] == 1 || matriz[i][colu] == 2) 
		{
			matriz[i][colu] = 0;
			break;
		}

} // fin de borrar


// realiza una jugada en la matriz del juego
void jugar(int col, int jugador, int matriz[6][7] )
{
	for (int i = 5; i >= 0; i--) 
	{
		if (matriz[i][col] == 0) 
		{
			matriz[i][col] = jugador;
			break;
		} // fin del if
	} // fin del for
} // fin de jugar


int FuncionEvaluadora( int matriz[6][7] )
{
	int adyacentesJ1 = 0; // cuenta las adyacentes para el jugador1(Humano)
	int adyacentesJ2 = 0; // cuenta las adyacentes para el jugador1(Humano)
	int puntosJ1 = 0;
	int puntosJ2 = 0;

	//comprobacion de filas
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			// para J1
			if (matriz[i][j] == 1)
			{
				adyacentesJ1++;
			}
			else
			{
				if (adyacentesJ1 > 1)
					puntosJ1 += adyacentesJ1;

				adyacentesJ1 = 0;
			} // fin del if...else


			  // para J2
			if (matriz[i][j] == 2)
			{
				adyacentesJ2++;
			}
			else
			{
				if (adyacentesJ2 > 1)
					puntosJ2 += adyacentesJ2;

				adyacentesJ2 = 0;
			}
		} // fin del for


		if (adyacentesJ1 > 1)
			puntosJ1 += adyacentesJ1;

		if (adyacentesJ2 > 1)
			puntosJ2 += adyacentesJ2;

		adyacentesJ1 = 0;
		adyacentesJ2 = 0;

	} // fin del for


	  //comprobacion de columnas
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			// para J1
			if (matriz[i][j] == 1)
			{
				adyacentesJ1++;
			}
			else
			{
				if (adyacentesJ1 > 1)
					puntosJ1 += adyacentesJ1;

				adyacentesJ1 = 0;
			} // fin del if...else


			  // para J2
			if (matriz[i][j] == 2)
			{
				adyacentesJ2++;
			}
			else
			{
				if (adyacentesJ2 > 1)
					puntosJ2 += adyacentesJ2;


				adyacentesJ2 = 0;
			}
		} // fin del for


		if (adyacentesJ1 > 1)
			puntosJ1 += adyacentesJ1;


		if (adyacentesJ2 > 1)
			puntosJ2 += adyacentesJ2;


		adyacentesJ1 = 0;
		adyacentesJ2 = 0;
	} // fin del for


	  //comprobacion de diagonales principales
	int x = 2;
	int y = 0;
	for (int i = x; y <= 4 && i < 6; i = x)
	{
		for (int j = y; y <= 4 && j < 7 && i < 6; j++, i++)
		{
			// para J1
			if (matriz[i][j] == 1)
			{
				adyacentesJ1++;
			}
			else
			{
				if (adyacentesJ1 > 1)
					puntosJ1 += adyacentesJ1;

				adyacentesJ1 = 0;
			} // fin del if...else


			  // para J2
			if (matriz[i][j] == 2)
			{
				adyacentesJ2++;
			}
			else
			{
				if (adyacentesJ2 > 1)
					puntosJ2 += adyacentesJ2;

				adyacentesJ2 = 0;
			}
		} // fin del for

		if (adyacentesJ1 > 1)
			puntosJ1 += adyacentesJ1;

		if (adyacentesJ2 > 1)
			puntosJ2 += adyacentesJ2;

		adyacentesJ1 = 0;
		adyacentesJ2 = 0;

		y += (x == 0 ? 1 : 0);
		x += (x > 0 ? -1 : 0);
	} // fin del for


	  //comprobacion de diagonales secundarias
	x = 3;
	y = 0;
	for (int i = x; y <= 3 && i < 6; i = x)
	{
		for (int j = y; y <= 3 && j < 7 && i >= 0; j++, i--)
		{
			// para J1
			if (matriz[i][j] == 1)
			{
				adyacentesJ1++;
			}
			else
			{
				if (adyacentesJ1 > 1)
					puntosJ1 += adyacentesJ1;

				adyacentesJ1 = 0;
			} // fin del if...else


			  // para J2
			if (matriz[i][j] == 2)
			{
				adyacentesJ2++;
			}
			else
			{
				if (adyacentesJ2 > 1)
					puntosJ2 += adyacentesJ2;

				adyacentesJ2 = 0;
			}
		} // fin del for

		if (adyacentesJ1 > 1)
			puntosJ1 += adyacentesJ1;


		if (adyacentesJ2 > 1)
			puntosJ2 += adyacentesJ2;

		adyacentesJ1 = 0;
		adyacentesJ2 = 0;

		y += (x == 5 ? 1 : 0);
		x += (x < 5 ? 1 : 0);
	} // fin del for


	return puntosJ1 - puntosJ2;
} // fin de la funcion evaluadora



//metodo que verifica ganador
//busca si el jugador dado ha ganado
bool verificar(int jugador, int matriz[6][7] ) 
{
	int adyacentes = 0; // cuenta las adyacentes para el jugador dado

						//comprobacion de filas
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) 
		{
			if (matriz[i][j] == jugador) 
			{
				adyacentes++;

				if (adyacentes >= 4)
					return true;
			}
			else
				adyacentes = 0;
		} // fin del for

		adyacentes = 0;
	} // fin del for


	  //comprobacion de columnas
	for (int j = 0; j < 7; j++) 
	{
		for (int i = 0; i < 6; i++) 
		{
			if (matriz[i][j] == jugador) 
			{
				adyacentes++;

				if (adyacentes >= 4)
					return true;
			}
			else
				adyacentes = 0;
		} // fin del for


		adyacentes = 0;
	} // fin del for


	  //comprobacion de diagonales principales
	int x = 2;
	int y = 0;
	for (int i = x; y <= 4 && i < 6; i = x)
	{
		for (int j = y; y <= 4 && j < 7 && i < 6; j++, i++)
		{
			if (matriz[i][j] == jugador)
			{
				adyacentes++;

				if (adyacentes >= 4)
					return true;
			}
			else
				adyacentes = 0;
		} // fin del for

		adyacentes = 0;
		y += (x == 0 ? 1 : 0);
		x += (x > 0 ? -1 : 0);
	} // fin del for


	//comprobacion de diagonales secundarias
	x = 3;
	y = 0;
	for (int i = x; y <= 3 && i < 6; i = x) 
	{
		for (int j = y; y <= 3 && j < 7 && i >= 0; j++, i--) 
		{
			if (matriz[i][j] == jugador) {
				adyacentes++;

				if (adyacentes >= 4)
					return true;
			}
			else
				adyacentes = 0;
		} // fin del for

		adyacentes = 0;
		y += (x == 5 ? 1 : 0);
		x += (x < 5 ? 1 : 0);
	} // fin del for


	return false;
} // fin de verificar


// selecciona la jugada de la IA
void IA( int nivel1, int* min)
{
	int matrizAux[6][7]; // matriz del juego
	int punt;
	int minMax[8]; // vector de minimos y maximos por nivel


	// igualo la matriz auxiliar a la matriz de juego original
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			matrizAux[i][j] = matriz[i][j];


	// inicio el vector de minimos y maximos
	for (int nivel = 0; nivel < 8; ++nivel)
	{
		if (nivel % 2 == 0)
			minMax[nivel] = INT_MAX;
		else
			minMax[nivel] = INT_MIN;
	} // fin del for de minimos y maximos


	// realiza las jugadas del nivel 1 (pc:min)
	if (llena(nivel1, matrizAux) != -1)
	{
		jugar(nivel1, 2, matrizAux);


		if (verificar(2, matrizAux))
		{
			borrar(nivel1, matrizAux);
			*min = INT_MIN;
			return;
		}
	}
	else
	{
		*min = INT_MAX;
		return;
	}


	// realiza las jugadas del nivel 2 (hm:max)
	for (int nivel2 = 0; nivel2 < 7; nivel2++)
	{
		if (llena(nivel2, matrizAux) != -1)
		{
			jugar(nivel2, 1, matrizAux);

			if (verificar(1, matrizAux))
			{
				minMax[1] = INT_MAX;
				borrar(nivel2, matrizAux);
				break;
			}
		}
		else
			continue;


		// realiza las jugadas del nivel 3 (pc:min)
		for (int nivel3 = 0; nivel3 < 7; nivel3++)
		{
			if (llena(nivel3, matrizAux) != -1)
			{
				jugar(nivel3, 2, matrizAux);


				if (verificar(2, matrizAux))
				{
					minMax[2] = INT_MIN;
					borrar(nivel3, matrizAux);
					break;
				}
			}
			else
				continue;


			// realiza las jugadas del nivel 4 (hm:max)
			for (int nivel4 = 0; nivel4 < 7; nivel4++)
			{
				if (llena(nivel4, matrizAux) != -1)
				{
					jugar(nivel4, 1, matrizAux);

					if (verificar(1, matrizAux))
					{
						minMax[3] = INT_MAX;
						borrar(nivel4, matrizAux);
						break;
					}
				}
				else
					continue;


				// realiza las jugadas del nivel 5 (pc:min)
				for (int nivel5 = 0; nivel5 < 7; nivel5++)
				{
					if (llena(nivel5, matrizAux) != -1)
					{
						jugar(nivel5, 2, matrizAux);


						if (verificar(2, matrizAux))
						{
							minMax[4] = INT_MIN;
							borrar(nivel5, matrizAux);
							break;
						}
					}
					else
						continue;


					// realiza las jugadas del nivel 6 (hm:max)
					for (int nivel6 = 0; nivel6 < 7; nivel6++)
					{
						if (llena(nivel6, matrizAux) != -1)
						{
							jugar(nivel6, 1, matrizAux);

							if (verificar(1, matrizAux))
							{
								minMax[5] = INT_MAX;
								borrar(nivel6, matrizAux);
								break;
							}
						}
						else
							continue;


						// realiza las jugadas del nivel 7 (pc:min)
						for (int nivel7 = 0; nivel7 < 7; nivel7++)
						{
							if (llena(nivel7, matrizAux) != -1)
							{
								jugar(nivel7, 2, matrizAux);


								if (verificar(2, matrizAux))
								{
									minMax[6] = INT_MIN;
									borrar(nivel7, matrizAux);
									break;
								}
							}
							else
								continue;

							// realiza las jugadas del nivel 8 (hm:max)
							for (int nivel8 = 0; nivel8 < 7; nivel8++)
							{
								if (llena(nivel8, matrizAux) != -1)
								{
									jugar(nivel8, 1, matrizAux);

									if (verificar(1, matrizAux))
									{
										minMax[7] = INT_MAX;
										borrar(nivel8, matrizAux);
										break;
									}
									else
										punt = FuncionEvaluadora(matrizAux);


									borrar(nivel8, matrizAux);

									if (punt > minMax[7])
										minMax[7] = punt;
								}
								else
									continue;
							} // fin del for del nivel 8 (hm:max)


							borrar(nivel7, matrizAux);


							if (minMax[7] < minMax[6])
								minMax[6] = minMax[7];

							minMax[7] = INT_MIN;
						} // fin del for para el nivel 7 (pc:min)

						borrar(nivel6, matrizAux);

						if (minMax[6] > minMax[5])
							minMax[5] = minMax[6];

						minMax[6] = INT_MAX;
					} // fin del for del nivel 6 (hm:max)	


					borrar(nivel5, matrizAux);


					if (minMax[5] < minMax[4])
						minMax[4] = minMax[5];

					minMax[5] = INT_MIN;
				} // fin del for para el nivel 5 (pc:min)

				borrar(nivel4, matrizAux);

				if (minMax[4] > minMax[3])
					minMax[3] = minMax[4];

				minMax[4] = INT_MAX;
			} // fin del for del nivel 4 (hm:max)

			borrar(nivel3, matrizAux);


			if (minMax[3] < minMax[2])
				minMax[2] = minMax[3];

			minMax[3] = INT_MIN;
		} // fin del for del nivel 3 (pc:min)


		borrar(nivel2, matrizAux);

		if (minMax[2] > minMax[1])
			minMax[1] = minMax[2];

		minMax[2] = INT_MAX;
	}// fin del for del nivel 2 (hm:max)


	borrar(nivel1, matrizAux);

	*min = minMax[1];// retorna el maximo del nivel 2
} // fin del IA




// retorna la jugada de la IA
int jugadaIA()
{
	// vector dinamico de enteros
	int** minimos;
	minimos = new int*[7];

	// vector dinamico de hilos
	thread** jugadas;
	jugadas = new thread*[7];


	// busca los siete minimos del primer nivel
	for (int jugada = 0; jugada < 7; jugada++)
	{
		minimos[jugada] = new int;
		jugadas[jugada] = new thread( IA, jugada, minimos[jugada] );
	} // fin del for


	// sincroniza los siete hilos
	for (int jugada = 0; jugada < 7; jugada++)
	{
		jugadas[jugada]->join(); // espera para continuar la ejecucion
	} // fin del for


	// busca el minimo y retorna jugada
	int posJug;
	int min;


	for (int jugada = 0; jugada < 7; jugada++)
	{
		if (jugada == 0)
		{
			min = *minimos[jugada];
			posJug = jugada;
		}
		else if ( *minimos[jugada] < min)
		{
			min = *minimos[jugada];
			posJug = jugada;
		} // fin del if...else
	} // fin del for


	// libero la memoria
	for (int jugada = 0; jugada < 7; jugada++)
	{
		delete minimos[jugada];
		delete jugadas[jugada];
	} // fin del for

	delete[] minimos;
	delete[] jugadas;

	return posJug; // retorna el minimo
} // fin de jugadaIA


// funcion principal de la aplicacion
int main()
{
	int jugada; // jugada
	int espaciosvacios = 48; // espacios vacios


	// inicia la matriz del juego
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			matriz[i][j] = 0;


	system("cls");
	imprimir(matriz);


	// mientras no llegue al final del juego
	while (true)
	{

		cout << "Introduzca donde desea jugar: ";
		cin >> jugada;
		jugar(jugada, 1, matriz);
		system("cls");
		imprimir(matriz);
		espaciosvacios--;


		if (verificar(1, matriz))
		{
			cout << "Gano el humano" << endl;
			break;
		} // fin del if

		if (espaciosvacios == 0)
		{
			cout << "Empate" << endl;
			break;
		} // fin del if

		jugada = jugadaIA();
		jugar(jugada, 2, matriz);
		system("cls");
		imprimir(matriz);
		espaciosvacios--;

		cout << "Jugada PC:" << jugada << endl;


		if (verificar(2, matriz))
		{
			cout << "Gano la PC" << endl;
			break;
		} // fin del if

		if (espaciosvacios == 0)
		{
			cout << "Empate" << endl;
			break;
		} // fin del if
	} // fin del while


	system("PAUSE"); 
	return 0;
} // fin del main

