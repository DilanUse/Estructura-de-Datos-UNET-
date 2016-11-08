#ifndef LETRA_H
#define LETRA_H

#include "libreria.h"

class Letra
{
	public:
		Letra( char );
		
		char letra;
		Letra *pre, *suc;
	protected:
};

#endif
