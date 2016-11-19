#include "RawMaterial.h"

RawMaterial::RawMaterial( int purityLevel, std::string observations, float weight, int toxicityLevel )
{
	this->purityLevel = purityLevel;
	this->observations = observations;
	this->weight = weight;
	this->toxicityLevel = toxicityLevel;
}


std::ostream& operator<<( std::ostream& salida, const RawMaterial& datos )
{
	char delim = ','; // separador 
	
	// imprime atribtos separados por delim
	salida << datos.observations;
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<
