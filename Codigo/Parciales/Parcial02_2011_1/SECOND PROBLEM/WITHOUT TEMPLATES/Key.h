#ifndef KEY_H
#define KEY_H

#include "Library.h"

class Key
{
	public:
		char key;
		Key* pre;
		Key* suc;
	
		Key( char );
	protected:
};

#endif
