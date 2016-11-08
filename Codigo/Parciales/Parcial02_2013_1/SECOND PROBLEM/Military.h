#ifndef MILITARY_H
#define MILITARY_H

#include "Library.h"

class Military
{
	public:
		Military();
		Military( char*, char* );
		~Military();
		
		char* name;
		char* grade;
		Military *suc, *pre;
	protected:
};

#endif
