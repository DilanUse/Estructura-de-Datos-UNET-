#ifndef VILLAGE_H
#define VILLAGE_H

#include "Library.h"

class Village
{
	public:
		int cityCode;
		char villageName[30];
		float distNextTown;
		Village* suc;
		
		Village();
		Village( int cityCode, char* villageName, float distNextTown );
		~Village();
	protected:
};

#endif
