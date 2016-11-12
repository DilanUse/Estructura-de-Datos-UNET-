#include "Military.h"

Military::Military(){}

Military::Military( char* name, char* grade )
{
	strcpy( this->name = new char[60], name );
	strcpy( this->grade = new char[4], grade );
	
	this->pre = NULL;
	this->suc = NULL;
} // end Military builder  

Military::~Military(){}
