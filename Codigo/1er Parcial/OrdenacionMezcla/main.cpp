#include <iostream>
#include <fstream>
#include <string>

using namespace std; // uso del espacio de nombres estandar
typedef string nomArch; // declaracion del tipo nomArchi


void leerArchivoBinario( string ); // lee y muestra contenido de archivos binarios
void mezclaDirecta( nomArch ); // controla la mezcla
int cuentaReg( nomArch ); // cuenta el numero de registros 
void distribuir( nomArch, nomArch, nomArch, int longSubSec, int numReg ); // separa secuencias ordenadas
void subSecuencia( nomArch, nomArch, int, int ); // toma subSecuencias y las escribe
void mezclar(nomArch, nomArch, nomArch, int&, int ); // mezcla pares de subsecuencias



// funcion principal del programa
int main(int argc, char** argv)
{
	leerArchivoBinario( "numeros1.dat" );
//	mezclaDirecta( "numeros1.dat" );
//	cout << endl << endl;
//	leerArchivoBinario( "numeros1.dat" );
} // fin de main


/**
 *	@brief	ee el archivo binario y muestra su contenido
*/
void leerArchivoBinario( string nomFile )
{
	int buffer; 
	ifstream file( nomFile.c_str(), ifstream::binary );
	
	
	while( file )
	{
		file.read( (char*)&buffer, sizeof(int) );
				
		if( file.eof() )
			break;
						
		cout << buffer << endl;
	} // fin del while
	
	
	file.close();
} // fin de leerArchivoBinario



//-------------------------------------------- mezcla ----------------------------------------------------------//
/**
 *	@brief	función que controla el algoritmo de ordenación
 *	@param nomArch nombre del archivo original a ordenar
*/
void mezclaDirecta( nomArch f )
{
	int longSubSec; // longitud de las SubSecuencias
	int numReg; // numero de registros en el archivo
	
	nomArch f1 = "auxiliar1.dat"; // archivo auxiliar1
	nomArch f2 = "auxiliar2.dat"; // archivo auxiliar2
	numReg = cuentaReg(f); // determina número de registros
	longSubSec = 1; // la longitud de las secuencias inicia en uno( cada registro)
	
	
	// mientras la longitud de las secuencias sea menor al numero de registro
	// se realizan pasadas de separación y mezcla
	while ( longSubSec < numReg )
	{
		distribuir( f, f1, f2, longSubSec, numReg ); // separacion
		mezclar( f1, f2, f, longSubSec, numReg ); // mezcla
	} // fin del while
} // fin de mezclaDirecta



// variables globales para distribuir--------------------------------------------
	ifstream f; // flujo para el archivo original
	ofstream f1; // flujo para el archivo auxiliar1
	ofstream f2; // flujo para el archivo auxiliar2

/**
 *	@brief	separa secuencias ordenadas de registros
 *	@param nomArch nombre del archivo original a ordenar
 *	@param nomArch nombre del archivo auxiliar1
 *	@param nomArch nombre del archivo auxiliar2
 *	@param int longitud de las secuencias
 *	@param int numero de registros en el archivo
*/
void distribuir( nomArch nf, nomArch nf1, nomArch nf2, int longSubSec, int numReg )
{
	int numSec; // numero de secuencias(siendo las secuencias pares de subsecuencias de igual longitud)
	int resto; // registros no tomados en cuenta( fuera de las secuencias)
	numSec = numReg / ( 2 * longSubSec ); // calculo del numero de secuencias
	resto = numReg % ( 2 * longSubSec ); // calculo de los registros restantes
/*	
	ifstream f( nf.c_str(), ifstream::binary ); // abro archivo original para leer
	ofstream f1( nf1.c_str(), ofstream::binary ); // abro archivo auxiliar1 para escribir
	ofstream f2( nf2.c_str(), ofstream::binary ); // abro archivo auxiliar1 para escribir
*/
	f.open( nf.c_str(), ifstream::binary ); // abro archivo original para leer
	f1.open( nf1.c_str(), ofstream::binary ); // abro archivo auxiliar1 para escribir
	f2.open( nf2.c_str(), ofstream::binary ); // abro archivo auxiliar1 para escribir
	
	
	// compruebo la correcta apertura de los archivos
	if ( f.fail() || f1.fail() || f2.fail() )
		throw " Error en el proceso de separación ";
		
	
	// llamo a subsecuencia para escribir las SubSecuencias en 
	// los archivos auxiliares y formar las secuencias	
	for ( int i = 1; i <= numSec; ++i )
	{
		subSecuencia( nf, nf1, longSubSec, 1 );
		subSecuencia( nf, nf2, longSubSec, 2 );
	} // fin del for
	
	
	/*
	Se procesa el resto de registros que no se tomaron en cuenta,
	es decir, que no entraron en ninguna secuencia
	*/
	// si la cantidad de registros restante es mayor a la
	// longitud de las subsecuencias
	if ( resto > longSubSec )
		resto -= longSubSec;
	else
	{
		longSubSec = resto;
		resto = 0;
	} // fin del if..else
	
	
	subSecuencia( nf, nf1, longSubSec, 1 );
	subSecuencia( nf, nf2, resto, 2 );
	f1.close(); f2.close(); f.close();
} // fin de distribuir


/**
 *	@brief	lee una subSecuencia del archivo original y la escribe
 *	en un archivo auxiliar
 *	@param nomArch nombre del archivo original a ordenar
 *	@param nomArch nombre del archivo auxiliar
 *	@param int longitud de las secuencias
*/
void subSecuencia( nomArch nf, nomArch nfAux, int longSubSec, int aux )
{
	int buffer; // almacena registros
//	ifstream f( nf.c_str(), ifstream::binary ); // abro archivo original para leer
//	ofstream fAux( nfAux.c_str(), ofstream::binary ); // abro archivo auxiliar para escribir
	
	
	// lee un registro a la vez del archivo original y lo escribe 
	// en el archivo auxiliar hasta completar una subSecuencia
	for (int j = 1; j <= longSubSec; j++)
	{
		f.read( (char*)&buffer, sizeof(int) );
//		fAux.write( (char*)&buffer, sizeof(int) );

		if( aux == 1 )
			f1.write( (char*)&buffer, sizeof(int) );
		else
			f2.write( (char*)&buffer, sizeof(int) );
	} // fin del for
} // fin de subSecuencia


/**
 *	@brief	mezcla pares de subsecuencias ordenadas en una secuencia
 *	@param nomArch nombre del archivo original a ordenar
 *	@param nomArch nombre del archivo auxiliar
 *	@param int longitud de las secuencias
*/
void mezclar(nomArch nf1, nomArch nf2, nomArch nf, int& longSubSec, int numReg)
{
	int numSec; // numero de secuencias(siendo las secuencias pares de subsecuencias de igual longitud)
	int resto; // registros no tomados en cuenta( fuera de las secuencias)
	int i, j; // cuenta la cantidad de registros procesado para los auxiliares 1 y 2 respectivamente 
	int n1, n2; // longitudes de las subSecuencias para los auxiliares 1 y 2 respectivamente
	int reg1, reg2; // registros a comparar
	int actual; // buffer para guardar el registro a ser escrito es el archivo original
	
	
	numSec = numReg / ( 2 * longSubSec ); // calculo del numero de secuencias
	resto = numReg % ( 2 * longSubSec ); // calculo de los registros restantes
	ofstream f( nf.c_str(), ofstream::binary ); // abro archivo original para escribir
	ifstream f1( nf1.c_str(), ifstream::binary ); // abro archivo auxiliar1 para leer
	ifstream f2( nf2.c_str(), ifstream::binary ); // abro archivo auxiliar1 para leer
	
	
	f1.read( (char*)&reg1, sizeof(int) ); // leo un registro del archivo auxiliar1
	f2.read( (char*)&reg2, sizeof(int) ); // leo un registro del archivo auxiliar2
	
	
	// mezcla las Secuencias formando las nuevas subSecuencias
	for( int s = 1; s <= numSec + 1; ++s )
	{
		n1 = n2 = longSubSec; // las longitudes de n1 y n2 empiezan iguales 
		
		
		// procesa los registros de la subsecuencia incompleta,
		// es decir, la subsecuencia que no formo una secuencia
		if ( s == numSec + 1 )
		{ 
			// si el resto es mayor a la longitud de las subSecuencias
			if ( resto > longSubSec )
				n2 = resto - longSubSec; // longitud de la subSecuencia de Aux2 
			else
			{
				n1 = resto; // longitud de la subSecuencia de aux1 son los registros restantes
				n2 = 0; // Aux2 no tiene resgitros restantes
			} // fin del if...else
		} // fin del fi
		
		
		i = j = 1; // contamos el primer registro de ambos auxiliares
		 
		
		// mientras aun no procese la cantidad de registros 
		// de las subsecuencias
		while ( i <= n1 && j <= n2 )
		{
			// si el resgitro en el archivo auxiliar1 es menor 
			if ( reg1 < reg2 )
			{
				actual = reg1; // almaceno el registro del auxiliar1
				f1.read( (char*)&reg1, sizeof(int) ); // leo el siguiente registro del auxiliar1
				i++; // paso a precesar un registro más del auxiliar1
			}
			else
			{
				actual = reg2; // almaceno el registro del auxiliar2
				f2.read( (char*)&reg2, sizeof(int) ); // leo el siguiente registro del auxiliar2
				j++; // paso a precesar un registro más del auxiliar2
			} // fin del if...else
			
			// escreibo en el archivo original el registro de menor valor
			f.write( (char*)&actual, sizeof(int) ); 
		} // fin del while
		
		
		
		/*
			Los registros no procesados se escriben directamente,
		*/
		// procesa los registros sin procesar del auxiliar1
		for ( int k = i; k <= n1; k++)
		{
			f.write( (char*)&reg1, sizeof(int) );
			f1.read( (char*)&reg1, sizeof(int) );
		} // fin del for
		
		
		// procesa los registros sin procesar del auxiliar1
		for ( int k = j; k <= n2; k++ )
		{
			f.write( (char*)&reg2, sizeof(int) );
			f2.read( (char*)&reg2, sizeof(int) );
		} // fin del for
	} // fin del for
	
	
	longSubSec *= 2; // aumento la longitud de las subSecuencias en un factor de 2
	f.close(); f1.close();f2.close(); // cierro todos los flujos
} // fin de mezclar


/**
 *	@brief	determinar el número de registros ene la archivo
 *	@param nomArch nombre del archivo original a ordenar
*/
int cuentaReg( nomArch nomFile )
{
	int registros = 0;
	int buffer;
	ifstream file( nomFile.c_str(), ifstream::binary );
	
	
	while ( file )
	{
		file.read( (char*)&buffer, sizeof(int) );
		
		if( file.eof() )
			break;
			
		++registros;
	} // fin del while
	
	
	file.close();
	return registros;
} // fin de cuentaReg
