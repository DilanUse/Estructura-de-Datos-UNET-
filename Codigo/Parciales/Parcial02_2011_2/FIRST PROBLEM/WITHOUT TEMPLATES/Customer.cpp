#include "Customer.h"

Customer::Customer(){}


Customer::Customer( int codeCustomer, int buyAmount )
{
	this->codeCustomer = codeCustomer;
	this->buyAmount = buyAmount;
	this->pre = NULL;
} // end Customer builder


Customer::~Customer(){}
