#include "libreria.h"
#include "letra.h"

Letra *cab = NULL, *final = NULL;



void crearEstructura( char* frase )
{
	
	for( int i = 0; i < strlen(frase); ++i )	
	{
		if( frase[i] != ' ' )
		{
			
			Letra* nuevo = new Letra( frase[i] );
			
			if( final == NULL )
			{
				final = nuevo;
				cab = nuevo;
			}
			else
			{
				final->suc = nuevo;
				nuevo->pre = final;
				final = nuevo;
			}
		}
	}
}

void mostrarEstructura()
{
	Letra *recorrido;
	recorrido = cab;
	
	cout <<".-Estructura: ";
	while( recorrido )
	{
		cout << recorrido->letra;
		
		recorrido = recorrido->suc;
	}
	
	cout << endl;
}

void comprobarPalindromo( char* frase )
{
	Letra *recDer, *recIzq;
	recDer = cab;
	recIzq = final;
	bool palindroma = true;
	
	
	
	while( recDer && recIzq )
	{
		
		if( recDer->letra != recIzq->letra )
		{
			palindroma = false;
			break;
		}
		recDer = recDer->suc;
		recIzq = recIzq->pre;
	}
	
	if( palindroma )
		cout << ".-" << frase << " es palindromo" << endl;
	else
		cout << ".-" << frase << " no es palindromo" << endl;
}

void eliminarEstructura()
{
	Letra *recorrido = cab;
	
	
	while( recorrido )
	{
		if( recorrido == final )
		{
			delete recorrido;
			break;
		}
		else
		{
			recorrido = recorrido->suc;
			delete recorrido->pre;
		}
	}
	
	
	cab = NULL;
	final = NULL;
	
}

void extraerDatos( char* archivo )
{
	ifstream file;
	
	
	file.open( archivo );
	
	
	if( !file.fail() )
	{
		while( !file.eof() )
		{
			char* buffer;
			
			file.getline( buffer = new char[100], 100, '\n' );
			
			crearEstructura( buffer );
			mostrarEstructura();
			comprobarPalindromo( buffer );
			eliminarEstructura();
			
			cout << endl<< endl;
			
			
			delete buffer;
			
		}
	}
	else
		return;
	
}


int main(int argc, char** argv) 
{
	extraerDatos( "data.txt" );
	return 0;
}
