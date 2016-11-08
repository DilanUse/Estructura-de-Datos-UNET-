#ifndef CITY_H
#define CITY_H

#include "Library.h"
#include "Village.h"

class City
{
	public:
		int cityCode;
		char cityName[30];
		float distNextTown;
		City* suc;
		Village* subL;
		
		City();
		City( int cityCode, char* cityName, float distNextTown );
		~City();
	protected:
};

#endif
