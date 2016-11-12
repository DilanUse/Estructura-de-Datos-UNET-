#include "RawMaterial.h"

RawMaterial::RawMaterial( int purityLevel, char* observations, float weight, int toxicityLevel )
{
	this->purityLevel = purityLevel;
	strcpy( this->observations, observations );
	this->weight = weight;
	this->toxicityLevel = toxicityLevel;
	this->suc = NULL;
}
