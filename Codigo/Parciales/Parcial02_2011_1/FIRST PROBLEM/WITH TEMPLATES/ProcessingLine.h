#ifndef PROCESSINGLINE_H
#define PROCESSINGLINE_H

#include "RawMaterial.h"
#include "ListaD.h"
#include <string>
#include <iostream>

class ProcessingLine
{
	friend std::ostream& operator<<( std::ostream&, const ProcessingLine& );
	public:
		int purityLevel;
		std::string description;
		ListaD<RawMaterial>* materials; 
		
		ProcessingLine( int, std::string );
		bool operator==( const ProcessingLine& ){} // sobrecarga el operador de igualdad
		bool operator<( const ProcessingLine& ){} // sobrecarga el operador relacional menor que
		bool operator>( const ProcessingLine& ){} // sobrecarga el operador relacional menor que
};

#endif
