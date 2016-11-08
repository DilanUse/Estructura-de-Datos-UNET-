#include "Route.h"

Route::Route( char* townName, float distNextTown )
{
	strcpy( this->townName, townName );
	this->distNextTown = distNextTown;
	this->pre = NULL;
}
