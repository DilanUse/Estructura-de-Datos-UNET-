#ifndef RECETA_H
#define RECETA_H

#include <string>
#include <iostream>
#include "ListaD.h"
#include "Ingrediente.h"



class Receta
{
	public:
		std::string nombre; 
		int codigo;
		int calorias;
		ListaD<Ingrediente>* ingredientes;
		
		Receta( )
		{
			this->nombre = "";
			this->codigo = 0;
			this->calorias = 0;
			this->ingredientes = NULL;
		}
		Receta( int cod, std::string nom, int cal )
		{
			this->nombre = nom;
			this->codigo = cod;
			this->calorias = cal;
			this->ingredientes = new ListaD<Ingrediente>();
		}
		
		
		bool operator==( const Receta &datos )
		{
			return this->codigo ==  datos.codigo;
		}
		
		
		bool operator<( const Receta& datos )
		{
			return this->codigo < datos.codigo;
		}
		
		bool operator>( const Receta& datos )
		{
			return this->codigo > datos.codigo;
		}
		
		friend std::ostream& operator<<( std::ostream& salida, const Receta& datos )
		{
			salida << datos.codigo << ", " << datos.nombre << ", " << datos.calorias;
	
			return salida; 
		}
};







#endif
