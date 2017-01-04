// algoritmo heuristico

#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
using namespace std;

int jugada; // jugada hecha por el usuario
int fila=6; // fila de la matriz
int col=7; // columnas de la matriz
//int matriz[6][7]; // matriz del juego
int puntaje[7];
int minimax[6][7],aux[6][7];


int matriz[6][7] = { 2, 2, 0, 1, 2, 0, 2,
                     0, 0, 1, 0, 0, 0, 0,
                     0, 1, 0, 0, 0, 1, 0,
                     0, 0, 0, 0, 1, 0, 0,
                     1, 0, 0, 0, 0, 0, 0,
                     0, 0, 1, 2, 2, 2, 0,
                   }; 



// imprime la matriz del juego
void imprimir() {
	for(int i=0; i<fila; i++) {
		for(int j=0; j<col; j++) {
			cout<<matriz[i][j]<<" ";
		}
		cout<<endl;
	} // fin del for
} // fin de imprimir


// verifica si la columna dada esta llena
int llena(int x) {
	if(matriz[0][x]!=0) {
		return -1;
	}
} // fin de llena


// borra una jugada
void borrar(int colu) {
	for(int i=0; i<6; i++)
		if(matriz[i][colu]==1 || matriz[i][colu]==2) {
			matriz[i][colu]=0;
			break;
		}

} // fin de borrar


// realiza una jugada en la matriz del juego
void jugar( int col, int jugador ) {
	for(int i=5; i >= 0; i--) {
		if(matriz[i][col] == 0 ) {
			matriz[i][col] = jugador;
			break;
		}
	}
	
	
//	system("cls"); //////////////
//	imprimir(); ///////////////
} // fin de jugar


int FuncionEvaluadora()
 {
	int adyacentesJ1 = 0; // cuenta las adyacentes para el jugador1(Humano)
	int adyacentesJ2 = 0; // cuenta las adyacentes para el jugador1(Humano)
	int puntosJ1 = 0;
	int puntosJ2 = 0;

	//comprobacion de filas
	for( int i = 0 ; i < 6; i++ ) 
	{
		for( int j = 0; j < 7; j++ ) 
		{
			// para J1
			if( matriz[i][j] == 1 ) 
			{
				adyacentesJ1++;
			} else
			{
				if( adyacentesJ1 > 1 )
					puntosJ1 += adyacentesJ1;
					
				adyacentesJ1 = 0;
			} // fin del if...else
			 
			 
			 // para J2
			if( matriz[i][j] == 2 ) 
			{
				adyacentesJ2++;
			} else
			{
				if( adyacentesJ2 > 1 )
					puntosJ2 += adyacentesJ2;
					
				adyacentesJ2 = 0;
			}
		} // fin del for
		
		
		if( adyacentesJ1 > 1 )
			puntosJ1 += adyacentesJ1;
		
		if( adyacentesJ2 > 1 )
			puntosJ2 += adyacentesJ2;
			
		adyacentesJ1 = 0;
		adyacentesJ2 = 0;
		
	} // fin del for


	//comprobacion de columnas
	for( int j = 0 ; j < 7; j++ ) 
	{
		for( int i = 0; i < 6; i++ ) 
		{
			// para J1
			if( matriz[i][j] == 1 ) 
			{
				adyacentesJ1++;
			} else
			{
				if( adyacentesJ1 > 1 )
					puntosJ1 += adyacentesJ1;
					
				adyacentesJ1 = 0;
			} // fin del if...else
			 
			 
			 // para J2
			if( matriz[i][j] == 2 ) 
			{
				adyacentesJ2++;
			} else
			{
				if( adyacentesJ2 > 1 )
					puntosJ2 += adyacentesJ2;
					
					
				adyacentesJ2 = 0;
			}
		} // fin del for
		
		
		if( adyacentesJ1 > 1 )
			puntosJ1 += adyacentesJ1;
			
			
		if( adyacentesJ2 > 1 )		
			puntosJ2 += adyacentesJ2;
			
			
		adyacentesJ1 = 0;
		adyacentesJ2 = 0;
	} // fin del for


	//comprobacion de diagonales principales
	int x = 2;
	int y = 0;
	for( int i = x ; y <= 4 && i < 6; i = x )
	 {
		for( int j = y; y <= 4 && j < 7 && i < 6; j++, i++ )
		 {
			// para J1
			if( matriz[i][j] == 1 ) 
			{
				adyacentesJ1++;
			} else
			{
				if( adyacentesJ1 > 1 )
					puntosJ1 += adyacentesJ1;
					
				adyacentesJ1 = 0;
			} // fin del if...else
			 
			 
			 // para J2
			if( matriz[i][j] == 2 ) 
			{
				adyacentesJ2++;
			} else
			{
				if( adyacentesJ2 > 1 )
					puntosJ2 += adyacentesJ2;
					
				adyacentesJ2 = 0;
			}
		} // fin del for

		if( adyacentesJ1 > 1 )
			puntosJ1 += adyacentesJ1;
			
		if( adyacentesJ2 > 1 )
			puntosJ2 += adyacentesJ2;
			
		adyacentesJ1 = 0;
		adyacentesJ2 = 0;
		
		y += ( x == 0 ? 1 : 0 );
		x += ( x > 0 ? -1 : 0 );
	} // fin del for


	//comprobacion de diagonales secundarias
	x = 3;
	y = 0;
	for( int i = x ; y <= 3 && i < 6; i = x ) 
	{
		for( int j = y; y <= 3 && j < 7 && i >= 0; j++, i-- ) 
		{
			// para J1
			if( matriz[i][j] == 1 ) 
			{
				adyacentesJ1++;
			} else
			{
				if( adyacentesJ1 > 1 )
					puntosJ1 += adyacentesJ1;
					
				adyacentesJ1 = 0;
			} // fin del if...else
			 
			 
			 // para J2
			if( matriz[i][j] == 2 ) 
			{
				adyacentesJ2++;
			} else
			{
				if( adyacentesJ2 > 1 )
					puntosJ2 += adyacentesJ2;
					
				adyacentesJ2 = 0;
			}
		} // fin del for

		if( adyacentesJ1 > 1 )
			puntosJ1 += adyacentesJ1;
			
			
		if( adyacentesJ2 > 1 )
			puntosJ2 += adyacentesJ2;
			
		adyacentesJ1 = 0;
		adyacentesJ2 = 0;
		
		y += ( x == 5 ? 1 : 0 );
		x += ( x < 5 ? 1 : 0 );
	} // fin del for
	
	
//	cout << "PJ1: " << puntosJ1  << endl;
//	cout << "PJ2: " << puntosJ2  << endl;

	return puntosJ1 - puntosJ2;

} // fin de la funcion evaluadora


/*
 *	metodo que verifica ganador
 *	busca si el jugador dado ha ganado
**/
bool verificar( int jugador ) {
	int adyacentes = 0; // cuenta las adyacentes para el jugador dado

	//comprobacion de filas
	for( int i = 0 ; i < 6; i++ ) {
		for( int j = 0; j < 7; j++ ) {
			if( matriz[i][j] == jugador ) {
				adyacentes++;

				if( adyacentes >= 4 )
					return true;
			} else
				adyacentes = 0;
		} // fin del for
		
		adyacentes = 0;
	} // fin del for


	//comprobacion de columnas
	for( int j = 0 ; j < 7; j++ ) {
		for( int i = 0; i < 6; i++ ) {
			if( matriz[i][j] == jugador ) {
				adyacentes++;

				if( adyacentes >= 4 )
					return true;
			} else
				adyacentes = 0;
		} // fin del for
		
		
		adyacentes = 0;
	} // fin del for


	//comprobacion de diagonales principales
	int x = 2;
	int y = 0;
	for( int i = x ; y <= 4 && i < 6; i = x )
	 {
		for( int j = y; y <= 4 && j < 7 && i < 6; j++, i++ )
		 {
			if( matriz[i][j] == jugador ) 
			{
				adyacentes++;

				if( adyacentes >= 4  )
					return true;
			} else
				adyacentes = 0;
		} // fin del for

		adyacentes = 0;
		y += ( x == 0 ? 1 : 0 );
		x += ( x > 0 ? -1 : 0 );
	} // fin del for


	//comprobacion de diagonales secundarias
	x = 3;
	y = 0;
	for( int i = x ; y <= 3 && i < 6; i = x ) {
		for( int j = y; y <= 3 && j < 7 && i >= 0; j++, i-- ) {
			if( matriz[i][j] == jugador ) {
				adyacentes++;

				if( adyacentes >= 4 )
					return true;
			} else
				adyacentes = 0;
		} // fin del for

		adyacentes = 0;
		y += ( x == 5 ? 1 : 0 );
		x += ( x < 5 ? 1 : 0 );
	} // fin del for

	
//	cout << false << endl;//////////////////////////
	return false;
} // fin de verificar


// selecciona la jugada de la IA
int IA() 
{
	int punt;
	int min = INT_MAX;
	int max = INT_MIN;
	int posjug;
	int minMax[4]; // vector de minimos y maximos por nivel
	
	
	// inicio el vector de minimos y maximos
	for( int nivel = 0; nivel < 4; ++nivel)
	{
		if( nivel % 2 == 0 )
			minMax[nivel] = INT_MAX;
		else
			minMax[nivel] = INT_MIN; 
	} // fin del for d


	// realiza las jugadas del nivel 1 (min)
	for(int nivel1 = 0; nivel1 < 7; nivel1++) 
	{
		if( llena(nivel1) != -1 )
		{
			jugar( nivel1, 2 );
			
			
			if( verificar( 2 ) )
			{
				borrar( nivel1 );
				return nivel1;
			}
		}
		else
			continue;

		
		// realiza las jugadas del nivel 2 (max)
		for(int nivel2 = 0; nivel2 < 7; nivel2++) 
		{
			if( llena( nivel2 ) != -1 )
			{
				jugar( nivel2, 1 );
				
				if( verificar( 1 ) )
				{
					minMax[1] = INT_MAX;
					borrar( nivel2 );
					break;
				}
			}
			else
				continue;
				
				
			// realiza las jugadas del nivel 3 (min)
			for(int nivel3 = 0; nivel3 < 7; nivel3++) 
			{
				if( llena(nivel3) != -1 )
				{
					jugar( nivel3, 2 );
					
					
					if( verificar( 2 ) )
					{
						minMax[2] = INT_MIN;
						borrar( nivel3 );
						break;
					}
				}
				else
					continue;
					
					
				// realiza las jugadas del nivel 4 (max)
				for(int nivel4 = 0; nivel4 < 7; nivel4++) 
				{
					if( llena( nivel4 ) != -1 )
					{
						jugar( nivel4, 1 );
						
						if( verificar( 1 ) )
						{
							minMax[3] = INT_MAX;
							borrar( nivel4 );
							break;
						}
						else 
							punt = FuncionEvaluadora();
		
						
						borrar( nivel4 );
						
						if( punt > minMax[3] )
							minMax[3] = punt;
					}
					else
						continue;	
				} // fin del for del nivel 4 (max)
					
					
				borrar( nivel3 );
		
				
				if( minMax[3] < minMax[2] )
					minMax[2] = minMax[3];
				
				minMax[3] = INT_MIN;
			} // fin del for del nivel 3 (min)
		
		
			borrar( nivel2 );
			
			if( minMax[2] > minMax[1] )
				minMax[1] = minMax[2];
			
			minMax[2] = INT_MAX;
		}// fin del for del nivel 2 (max)
		
		
		borrar( nivel1 );

		
		if( minMax[1] < minMax[0] )
		{
			minMax[0] = minMax[1];
		    posjug = nivel1;
		}
		
		minMax[1] = INT_MIN;
	}// for del for del nivel 1 (min)


	return posjug;// retorna la posicion(columna) de la jugada
} // fin del IA




/// funcion principal de la aplicacion
int main() 
{

	imprimir();
	//FuncionEvaluadora();

	// inicia la matriz del juego
	for( int i = 0; i < 6; i++ )
		for( int j = 0; j < 7; j++ )
	  		matriz[i][j] = 0;


	system("cls");
	imprimir();
	
	
	// mientras no llegue al final del juego
	while( true )
	{

		cout<<"Introduzca donde desea jugar: ";
		cin>>jugada;
		jugar(jugada, 1);
		system("cls");
		imprimir();


		if( verificar(1) )
		{
			cout << "Gano el humano" << endl;
			break;
		}


		jugada = IA();
		jugar(jugada, 2);
		system("cls");
		imprimir();
		cout << "Jugada PC:" << jugada << endl;
		
		
		if( verificar(2) )
		{
			cout << "Gano la PC" << endl;
			break;
		}

	} // fin del while
	
	
	return 0;
} // fin del main
