#ifndef RAWMATERIAL_H
#define RAWMATERIAL_H

#include "Library.h"

class RawMaterial
{
	public:
		int purityLevel;
		char observations[20];
		float weight;
		int toxicityLevel;
		RawMaterial* suc;
		
		RawMaterial( int, char*, float, int );
	protected:
};

#endif
