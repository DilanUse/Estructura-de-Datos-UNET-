#include "ProcessingLine.h"

ProcessingLine::ProcessingLine( int purityLevel, char* description )
{
	this->purityLevel = purityLevel;
	strcpy( this->description, description );
	this->suc = NULL;
	this->subL = NULL;
}
