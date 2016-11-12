#ifndef ROUTE_H
#define ROUTE_H

#include "Library.h"


class Route
{
	public:
		char townName[30];
		float distNextTown;
		Route* pre;
		
		Route( char* townName, float  );
	protected:
};

#endif
