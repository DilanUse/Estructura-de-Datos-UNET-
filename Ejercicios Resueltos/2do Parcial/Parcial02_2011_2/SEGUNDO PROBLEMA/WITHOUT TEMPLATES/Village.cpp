#include "Village.h"

Village::Village(){}


Village::Village( int cityCode,char* villageName, float distNextTown )
{
	this->cityCode = cityCode;
	strcpy( this->villageName, villageName);
	this->distNextTown = distNextTown;
	this->suc = NULL;
}


Village::~Village(){}
