#ifndef PALABRA_H
#define PALABRA_H

#include <string>
#include <iostream>
using namespace std;

class Palabra
{
	friend std::ostream& operator<<( std::ostream&, const Palabra& );
	
	public:
		string palabra;
		int ocurrencia;
		
		
		Palabra( string );		
		bool operator==( const Palabra& ); // sobrecarga el operador de igualdad
		bool operator<( const Palabra& ); // sobrecarga el operador relacional menor que
		bool operator>( const Palabra& ); // sobrecarga el operador relacional menor que
};

#endif
