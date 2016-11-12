#include "City.h"

City::City(){}


City::City( int cityCode, char* cityName, float distNextTown )
{
	this->cityCode = cityCode;
	strcpy( this->cityName, cityName );
	this->distNextTown = distNextTown;
	this->suc = NULL;
	this->subL = NULL;
}


City::~City(){}
