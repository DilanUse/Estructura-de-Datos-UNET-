#ifndef PROCESSINGLINE_H
#define PROCESSINGLINE_H

#include "Library.h"
#include "RawMaterial.h"


class ProcessingLine
{
	public:
		int purityLevel;
		char description[25];
		ProcessingLine* suc;
		RawMaterial* subL;
		
		ProcessingLine( int, char* );
	protected:
};

#endif
