#include "Library.h"
#include "ProcessingLine.h"
#include "RawMaterial.h"


ProcessingLine *head = NULL, *end = NULL;

void extractingData( char* fileName1, char* fileName2 );
void createProductionLine( ProcessingLine* add );
void addRawMaterial( RawMaterial* add );
void showStructure();


void extractingData( char* fileName1, char* fileName2 )
{
	ifstream inflow; 
	
	
	inflow.open( fileName1 );
	
	
	if( !inflow.fail() )
	{
		char* buffer = new char[30];
		int purityLevel;
		
		
		while( !inflow.eof() )
		{
			inflow.getline( buffer, 5, ',' );
			purityLevel = atoi( buffer );
			inflow.getline( buffer, 30, '\n' );
			
			ProcessingLine* add = new ProcessingLine( purityLevel, buffer );	
			
			createProductionLine( add );
		}
		
		
		delete buffer;
		
		inflow.close();
		
		inflow.open( fileName2 );
		
		
		if( !inflow.fail() )
		{
			char* buffer = new char[20];
			int purityLevel;
			char observations[20];
			float weight;
			int toxicityLevel;
			
			
			while( !inflow.eof() )
			{
				inflow.getline( buffer, 5, ',' );
				purityLevel = atoi( buffer );
				inflow.getline( buffer, 20, ',' );
				strcpy( observations, buffer );
				inflow.getline( buffer, 10, ',' );
				weight = atof( buffer );
				inflow.getline( buffer, 10, '\n' );
				toxicityLevel = atoi( buffer );
			
				RawMaterial* add = new RawMaterial( purityLevel, observations, weight, toxicityLevel );	
			
				addRawMaterial( add );
			}
			
			delete buffer;
		}
	}
	else
		return;
}


void createProductionLine( ProcessingLine* add )
{
	if( !head )
	{
		head = add;
		end = add;
	}
	else
	{
		end->suc = add;
		end = add;
	}
}


void addRawMaterial( RawMaterial* add )
{
	ProcessingLine* route = head;
	RawMaterial* travel = NULL;
	
	
	while( route )
	{
		if( route->purityLevel == add->purityLevel )
		{
			if( !route->subL )
				route->subL = add;
			else
			{
				travel = route->subL;
				
				
				while( travel->suc )
					travel = travel->suc;
				
				
				travel->suc = add;
			}
			
			break;
		}
		
		route = route->suc;
	}
}


void showStructure()
{
	ProcessingLine* route = head;
	RawMaterial* travel = NULL;
	
	
	while( route )
	{
		cout << ".-" << route->description << "--->" << ( route->suc ? route->suc->description : "void" ) << endl;
		
		if( route->subL )
		{
			travel = route->subL;
			
			cout << "*)Processes: " << endl;
			
			
			while( travel )
			{
				cout << travel->purityLevel << "," << travel->observations << ","; 
				cout << travel->weight << "," << travel->toxicityLevel << endl;  
				travel = travel->suc;
			}
		}
		
		cout << endl << endl;
		
		route = route->suc;
	}
}


int main(int argc, char** argv) 
{
	extractingData( "nivel.txt", "data.txt" );
	showStructure();
	return 0;
}
