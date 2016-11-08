#include "library.h"
#include "Military.h"
#define R0 "R0"
#define R1 "R1"
#define R2 "R2"

Military *head = NULL, *end = NULL;

 
void extractingData( char* nameFile );
void createStructure( Military* add );
void removeMilitary();
void showStructure();
void searchStructure();


void extractingData( char* nameFile )
{
	ifstream dataLine;
	
	dataLine.open( nameFile );
	
	
	if( !dataLine.fail() )
	{
		while( !dataLine.eof() )
		{
			char *name, *grade;
			
			
			dataLine.getline( name = new char[60], 60, ',' );
			dataLine.getline( grade = new char[4], 4, '\n' );
			
			Military* add = new Military( name, grade );
			
			createStructure( add );
			
			delete name;
			delete grade;
		} 
	}
	else
		return;
	
	
} // end extractingData


void createStructure( Military* add )
{
	
	if( head == NULL )
	{
		head = end = add->pre = add->suc = add;
	}
	else
	{
		end->suc = add;
		add->pre = end;
		end = add;
		add->suc = head;
		head->pre = add;
	}
} // end createStructure


void showStructure()
{
	int counter = 0;
	bool exit = false;
	
	Military *route = head;
	
	
	cout << "Structure: " << endl;
	
	
	while( !exit )
	{		 
		cout << route->pre->name << "<--" << route->name << "/" << route->grade << "-->" << route->suc->name;	
			
			
		if( route == end )
			exit = true;
			
		
		route = route->suc;
		cout << endl;
	}
} // end showStructure


void removeMilitary( char* fileName )
{
	ifstream dataLine;
	
	
	dataLine.open(fileName );
	
	
	if( !dataLine.fail() )
	{
		int count = 0;
		int round = 1;
		bool direction = 0; // intial clockwise diretion
		char* buffer = new char[3];  
		Military* route = NULL; 
		Military* start = NULL; // do not NULL after
		Military* startAux = NULL; 
		Military* selected = NULL;
		Military* lessGrade = NULL;
		Military* removed = NULL;
		
		
		while( !dataLine.eof() )
		{
			if( !start )
			{
				
				char *initialName = new char[60];
				bool* found = new bool;
				*found = false;
				route = head;
				
				dataLine.getline( initialName, 60, ',' );
				dataLine.getline( buffer, 2, '\n' );
				count = atoi( buffer );


				while( !*found )
				{
					if( strcmpi( route->name, initialName ) == 0 )
					{
						start = route;
						*found = true;
					}
					
					route = route->suc;
				}
				
				delete[] initialName;
				delete found;
			}
			else
			{
				dataLine.getline( buffer, 3, ',' );
				count = atoi(buffer);
				dataLine.getline( buffer, 3, '\n' );
				direction = atoi(buffer);
			}
			
			route = start;
			
			for( int i = 0; i < count; ++i )
				route = ( direction ? route->pre : route->suc ); // move for structure in value of diretion
				
			
			selected = route;
			route = ( direction ? route->suc : route->pre );
			
			
			while( route != selected )
			{
				if( ( strcmp( route->grade, R1 ) == 0 ) && !lessGrade )
				{
					lessGrade = route;
				}
				
				if( strcmp( route->grade, R0 ) == 0 )
				{
					lessGrade = route;
					break;
				}
				
				route = ( direction ? route->suc : route->pre );
			}
			
			
			if( !lessGrade )
			{
				removed = selected; 
				startAux = ( direction ? removed->pre : removed->suc ); // new start
			}
			else
			{
				if( strcmp( selected->grade, lessGrade->grade ) > 0 )
				{
					removed = lessGrade;
					startAux = ( direction ? removed->suc : removed->pre ); // new start
				}
				else
				{
					removed = selected;
					startAux = ( direction ? removed->pre : removed->suc ); // new start
				}
			}
			
			
			cout << "*Ronda: " << round << endl;
			cout << ".-Militar Donde se partio el recorrido: " << start->name << endl; 
			cout << ".-Sentido del recorrido: " << ( direction ? "Antihorario" : "Horario" ) << endl;
			cout << ".-Numero de conteo: " << count << endl;
			cout << ".-Militar seleccionado: " << selected->name << ", " << selected->grade << endl;
			cout << ".-Militar reemplazado por su rango: ";
			
			
			if( removed == selected )
				cout << "No hay" << endl;
			else
				cout << lessGrade->name << ", " << lessGrade->grade << endl;
				
			
			cout << ".-Militar eliminado del juego: " << removed->name << ", " << removed->grade << endl;
			
				
			if( removed == head )
				head = head->suc;
				
			if( removed == end )	
				end = end->pre;
				
					
			removed->pre->suc = removed->suc;
			removed->suc->pre = removed->pre;
			
			delete removed;
			
			start = startAux;
			lessGrade = NULL;
			removed = NULL;
			selected = NULL;
			route = NULL;
			startAux = NULL;
			++round;
			
			
			getch();
			cout << endl << endl;
			
			
			if( head == end )
				break;
		} // end while
		
		
		cout << "***El militar que se escapara sera: " << head->name;
	}
	else
		return;
}


int main(int argc, char** argv)
{
	extractingData( "milicia.txt" );
	showStructure();
	
	getch();	
	cout << endl << endl;
	
	removeMilitary( "jugada.txt" );
	return 0;
}

