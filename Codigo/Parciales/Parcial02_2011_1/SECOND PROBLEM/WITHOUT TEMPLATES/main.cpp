#include "Library.h"
#include "Key.h"


Key* head = NULL;

void extractingData( char* fileName );
void createStructure( Key* add );
void showStructure();
void decodeMessage( char* fileName );
Key* goStrtucture( Key* Initialposition, int direction, int displacement );



void extractingData( char* fileName )
{
	ifstream inflow;
	
	
	inflow.open( fileName );
	
	
	if( !inflow.fail() )
	{
		char key;
		
		
		while( !inflow.eof() )
		{
			inflow.getline( (char*)& key, 3, ' ' );
			
			Key* add = new Key( key );
			
			createStructure( add );
		}
	}
	else
		return;
}


void createStructure( Key* add )
{
	Key* route = head;
	Key* before = NULL;
	bool found = false;
	
	                                                                                                                                                           
	if( !head )
	{
		head = add;
		head->suc = add;
		head->pre = add;
	}
	else
	{
		while( !found )
		{
			if( add->key < route->key )
			{
				found = true;
				break;
			}
			
			route = route->suc;
			
			if( route == head )
				break;
		}
		
		
		if( found )
			before = route->pre;
		else
			before = head->pre;
		
		before->suc = add;
		add->pre = before;
		add->suc = route;
		route->pre = add;
		
		if( route == head && found )
			head = add;
	}
}


void showStructure()
{
	Key* route = head;
	
	
	while( true )
	{
		cout << route->pre->key << "<---" << route->key << "--->" << route->suc->key << endl;
		
		route = route->suc;
			
		if( route == head )
			break;
	}
}


void decodeMessage( char* fileName )
{
	FILE *inflow;
	Key* position = head;
	
	
	inflow = fopen( fileName, "r" );
	
	
	if( inflow )
	{
		char letterBuffer;
		char* lineBuffer = new char[3];
		int direction;
		int displacement;
		
		
		while( !feof(inflow) )
		{
			letterBuffer = fgetc( inflow );
			fgets( lineBuffer, 3, inflow );
			direction = atoi( (char*)&letterBuffer );
			displacement = atoi( lineBuffer );
			
			
			position = goStrtucture( position, direction, displacement );
			
			cout << position->key;
			
			fgetc( inflow );
			
		}
	}
	else
		return;

}


Key* goStrtucture( Key* position, int direction, int displacement )
{
	--displacement;
	
	
	while( displacement )
	{
		position = ( direction == 1 ? position->suc : position->pre );
		--displacement;
	}
}


int main(int argc, char** argv) 
{
	extractingData( "claves.txt" );
	showStructure();
	
	cout << endl << endl << "Messaje: ";
	decodeMessage( "mensa.txt" );	
	return 0;
}
