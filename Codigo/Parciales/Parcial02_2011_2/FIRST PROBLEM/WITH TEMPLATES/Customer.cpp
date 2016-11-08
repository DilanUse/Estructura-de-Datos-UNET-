#include "Customer.h"

using namespace std;

Customer::Customer(){}


Customer::Customer( int codeCustomer, int buyAmount )
{
	this->codeCustomer = codeCustomer;
	this->buyAmount = buyAmount;
} // end Customer builder


Customer::~Customer(){}


ostream& operator<<( ostream& salida, const Customer& datos )
{
	char delim = ','; // separador 
	
	// imprime atribtos separados por delim
	salida << datos.codeCustomer << delim << datos.buyAmount;
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<
