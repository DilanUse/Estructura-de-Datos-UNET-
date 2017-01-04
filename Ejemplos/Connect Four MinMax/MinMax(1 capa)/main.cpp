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


	for(int n = 0; n < 7; n++) 
	{
		if( llena(n) != -1 )
		{
			jugar( n, 2 );
			
			
			if( verificar( 2 ) )
			{
				borrar( n );
				return n;
			}
		}
		else
			continue;


		for(int o = 0; o < 7; o++) 
		{
			if( llena( o ) != -1 )
			{
				jugar( o, 1 );
				
				if( verificar( 1 ) )
				{
					max = INT_MAX;
					borrar( o );
					break;
				}
				else 
					punt = FuncionEvaluadora();


				if( punt > max )
					max = punt;
			}
			else
				continue;
		
		
			borrar( o );
		}//for o
		
		
		borrar( n );

		
		if( max < min )
		{
			min = max;
		    posjug = n;
		}
		
		max = INT_MIN;
	}//for n


	return posjug;// retorna la posicion(columna) de la jugada
} // fin del IA




/// funcion principal de la aplicacion
int main() 
{

	imprimir();
	//FuncionEvaluadora();
	
	bool finJuego = false; // determina si se llego al fin del juego

	// inicia la matriz del juego
	for( int i = 0; i < 6; i++ )
		for( int j = 0; j < 7; j++ )
	  		matriz[i][j] = 0;


	// mientras no llegue al final del juego
	while( !finJuego )
	{
		system("cls");
		imprimir();
		cout<<"Introduzca donde desea jugar: ";
		cin>>jugada;
		jugar(jugada, 1);
		system("cls");
		imprimir();

		Sleep( 1000 );


		jugada = IA();
		jugar(jugada, 2);
		system("cls");
		imprimir();

	} // fin del while
	
	
	return 0;
} // fin del main
