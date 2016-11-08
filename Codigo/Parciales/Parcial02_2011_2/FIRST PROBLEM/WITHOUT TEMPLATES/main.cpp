#include "Library.h"
#include "Customer.h"


Customer *front = NULL, *end = NULL;

void extractingData( char* fileName );
void createStructure( Customer* add );
void showStruture();
void buyProducts();
bool existProducts(  Customer* client, int &productAmount );
void showFinalResults();


// extract data of the text file
void extractingData( char* fileName )
{
	ifstream file;
	
	
	file.open( fileName );
	
	
	if( !file.fail() )
	{
		char* buffer = new char[20];
		int codeCustomer;
		int buyAmount;
		
		
		while( !file.eof() )
		{
			file.getline( buffer, 20, ',' );
			codeCustomer = atof( buffer );
			file.getline( buffer, 5, '\n' );
			buyAmount = atoi( buffer );
			
			Customer *add = new Customer( codeCustomer, buyAmount );
			
			createStructure( add );
		}
		
		delete[] buffer;
	}
	else
		return;
} // end extractingData



// create a structure dinamic with the data of the text file
void createStructure( Customer* add )
{
	if( !front )
		front = add;
	else
		end->pre = add;
		
		
	end = add;
} // end createStructure


// show structure create from text file
void showStruture()
{
	Customer *route;
	route = front;
	
	cout <<".-Estructura: " << endl;
	while( route )
	{
		cout << route->codeCustomer << "-->" << ( route->pre ? route->pre->codeCustomer : 0 ) << endl;
		
		route = route->pre;
	}
} // end showStructure


// 
void buyProducts()
{
	Customer* frontAux;
	Customer* route;
	int productAmount;
	
	
	cout << "Ingrese la cantidad del producto: ";
	cin >> productAmount;
	cout << endl << endl << "**Procces of buy: " << endl << endl;
	
	
	while( true )
	{
		if( front )
		{
			frontAux = front;
			
			
			if( front == end )
			{	
				if( existProducts( front, productAmount ) )
					front = end = NULL;
					
				break;
			}
			else
			{
				if( existProducts( front, productAmount ) )	
					front = front->pre;
				else 
					break;
			}
			
			getch();
			cout << endl;
			delete frontAux;
		}
	}

	
	cout << endl << endl << ".-Customers not buy: ";
	
	
	if( !front )
		cout << 0 << endl;
	else
	{
		route = front;
		cout << endl;
		
		while( route )
		{
			cout << "Client code: " << route->codeCustomer << endl;
			route = route->pre;
		}
	}
	
	
	cout << endl << endl << ".-Amount of product not sell: " << productAmount;

	
} // end buyProducts



bool existProducts(  Customer* client, int &productAmount )
{
	if( client->buyAmount <= productAmount )
	{
		productAmount -= client->buyAmount;
		
		cout << ".-Client code: " << client->codeCustomer << endl;
		cout << ".-Buy amount: " << client->buyAmount << endl;
		cout << ".- Existing product: " << productAmount << endl;
		
		return true; 
	}
	
	return false;
}





int main(int argc, char** argv) 
{
	extractingData( "cola.txt" );
	showStruture();
	
	getch();
	system( "cls" );
	
	buyProducts();
	return 0;
}
