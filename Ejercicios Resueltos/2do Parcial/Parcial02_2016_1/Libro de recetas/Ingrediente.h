#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include <string>

class Ingrediente
{
	public:
		std::string nombre;
		int calorias;
		
		
		Ingrediente( std::string nom, int cal)
		{
			this->nombre = nom;
			this->calorias = cal;
		}
		
		
		Ingrediente()
		{
			this->nombre = "";
			this->calorias = 0;
		}
		
		
		
		bool operator==( const Ingrediente &datos )
		{
			return this->nombre ==  datos.nombre;
		}
		
		
		bool operator<( const Ingrediente& datos )
		{
			return this->nombre < datos.nombre;
		}
		
		bool operator>( const Ingrediente& datos )
		{
			return this->nombre > datos.nombre;
		}
		
		friend std::ostream& operator<<( std::ostream& salida, const Ingrediente& datos )
		{
			salida << datos.nombre << ", " << datos.calorias;
	
			return salida; 
		}
};

#endif
