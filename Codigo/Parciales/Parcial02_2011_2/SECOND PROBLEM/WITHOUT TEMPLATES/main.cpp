#include "Library.h"
#include "City.h"
#include "Village.h"
#include "Route.h"


City* head = NULL, *end = NULL;
Route* top = NULL;

void extractingData( char* fileName );
void createCityStructure( City* add );
void addVillage( Village* add );
void showStructure();	
void showRoute();


// extract data of the text file specified
void extractingData( char* fileName1, char* fileName2  )
{
	ifstream inFlow;
	
	
	inFlow.open( fileName1 );
	
	
	if( !inFlow.fail() )
	{
		char* buffer = new char[30];
		int code;
		char* name = new char[30];
		float distance;
		
		
		while( !inFlow.eof() )
		{
			inFlow.getline( buffer, 30, ',' );
			code = atoi( buffer );
			inFlow.getline( buffer, 30, ',' );
			strcpy( name, buffer );
			inFlow.getline( buffer, 30, '\n' );
			distance = atof( buffer );
			
			
			City *add = new City( code, name, distance );
			
			createCityStructure( add );
		}
		
		
		inFlow.close();
		
		inFlow.open( fileName2 );
		

		while( !inFlow.eof() )
		{
			inFlow.getline( buffer, 30, ',' );
			code = atoi( buffer );
			inFlow.getline( buffer, 30, ',' );
			strcpy( name, buffer );
			inFlow.getline( buffer, 30, '\n' );
			distance = atof( buffer );
			
			
			Village *add = new Village( code, name, distance );
			
			addVillage( add );
		}
		
		delete[] buffer;
		delete[] name;
		
	}
	else 
		return;
} // endl extractingData


// creates a structure add the received city
void createCityStructure( City* add )
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
} // end create 




void addVillage( Village* add )
{
	City* route = head; // for principal structure 
	Village* travel = NULL; // for secundary structure
	
	while( route )
	{
		if( route->cityCode == add->cityCode )
			break;
			
		route = route->suc;
	}

	
	while( route )
	{
		if( !route->subL )
		{
			route->subL = add;
			break;
		}
		else
		{
			travel = route->subL;

			while( travel->suc )
				travel = travel->suc;
					
			travel->suc = add;
			
			break;
		}
	}
}



// show the structure with the cities and villages
void showStructure()
{
	City* route = head;
	Village* travel = NULL;
	
	while( route )
	{
		cout << route->cityName << "-->" << ( route->suc ? route->suc->cityName : "0" ) << "/Villages: " << endl;
		
		travel = route->subL;
		
		while( travel )
		{
			cout << "--->" << travel->villageName;
			travel= travel->suc;
		}
		
		route = route->suc;
		
		cout << endl << endl;
	}
}



void showRoute()
{
	City* route = head;
	Village* travel = NULL;
	Route* remove = NULL;
	char* startCity = new char[30];
	char* endCity = new char[30];
	bool found = false;
	float distance = 0;
	
	cout << "Enter start city: ";
	gets( startCity );
	
	cout << endl << endl << "Enter end city: ";
	gets( endCity );
	
	
	while( route )
	{
		if( top )
		{
			Route *add = new Route( route->cityName, route->distNextTown );
			add->pre = top;
			top = add;
		}
		else
		{
			if( !strcmpi( route->cityName, startCity ) )
			{
				Route *add = new Route( route->cityName, route->distNextTown );
				top = add;
			}
		}
		
		
		if( top && route->subL )
			travel = route->subL;
		
			
		while( top && travel )
		{
			if( !strcmpi( travel->villageName, endCity ) && !found )
			{
				found = true;
				travel = route->subL;
			}
			
			if( found )
			{
				Route *add = new Route( travel->villageName, travel->distNextTown );
				add->pre = top;
				top = add;
				
				if( !strcmpi( travel->villageName, endCity ) )
					break;
			}
			
			travel = travel->suc;
		}

		if( found )
			break;
		
		route = route->suc;
	}
	
	
	while( top && found )
	{
		remove = top;
		
		
		if( !top->pre )
		{
			cout << top->townName;
			delete top;
			top = NULL;
		}
		else
		{
			distance += top->pre->distNextTown;
			cout << top->townName << "<--";
			top = top->pre;
			delete remove;
		}
		
	}
	
	
	if( !found )
		cout << endl << endl << "Ruta inexistente...";
	else
		cout << endl << "Distance: " << distance; 
	
	
}



int main(int argc, char** argv) 
{
	extractingData( "cities.txt", "villages.txt" );
	showStructure();
	
	cout << endl << endl;
	
	showRoute();
	return 0;
}
