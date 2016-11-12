#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

class Customer
{
	// funci�n para sobrecargar operador de inserci�n de flujo
	friend std::ostream& operator<<( std::ostream&, const Customer& );
	public:
		Customer();
		Customer( int, int );
		~Customer();
		
		int codeCustomer;
		int buyAmount;
};

#endif
