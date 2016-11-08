#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

class Customer
{
	// función para sobrecargar operador de inserción de flujo
	friend std::ostream& operator<<( std::ostream&, const Customer& );
	public:
		Customer();
		Customer( int, int );
		~Customer();
		
		int codeCustomer;
		int buyAmount;
};

#endif
