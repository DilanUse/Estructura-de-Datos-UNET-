#ifndef RAWMATERIAL_H
#define RAWMATERIAL_H

#include <string>

class RawMaterial
{
	friend std::ostream& operator<<( std::ostream&, const RawMaterial& );
	public:
		int purityLevel;
		std::string observations;
		float weight;
		int toxicityLevel;
		
		RawMaterial( int, std::string, float, int );
		bool operator==( const RawMaterial& ){} // sobrecarga el operador de igualdad
		bool operator<( const RawMaterial& ){} // sobrecarga el operador relacional menor que
		bool operator>( const RawMaterial& ){} // sobrecarga el operador relacional menor que
};

#endif
