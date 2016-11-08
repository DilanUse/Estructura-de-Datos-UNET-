#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "library.h"


class Customer
{
	public:
		Customer();
		Customer( int, int );
		~Customer();
		
		int codeCustomer;
		int buyAmount;
		Customer* pre;
	protected:
};

#endif
