#ifndef ARCHIVOMP3_H
#define ARCHIVOMP3_H

#include <iostream>
#include <string>

class ArchivoMp3
{
        public:
                std::string nombre;                
                int minuto;
                int segundo;
 //               int id;
                
        public:
                ArchivoMp3(){ minuto = 100; segundo = 100;}
                ArchivoMp3( std::string nom, int min, int seg )
                {
                	this->nombre = nom;
                	this->minuto = min;
                	this->segundo = seg;
				}
				
						// función para sobrecargar operador de inserción de flujo
	friend std::ostream& operator<<( std::ostream& salida, const ArchivoMp3& datos )
	{
		char delim = ','; // separador 
	
		// imprime atribtos separados por delim
		salida << datos.nombre;
		
		return salida; // retorna el objeto del flujo de salida
	}
				
				
  /*             void setNombre(char Nombre[]){strcpy(this->Nombre,Nombre);}
    //            char *getNombre(){return Nombre;}  
	//			void setminuto(){ this->minuto=minuto;}              
      //          float getminuto(){return minuto;}   
				void setsegundo(){ this->segundo=segundo;}         
                float getsegundo(){return segundo;}   
				void Cargar();    
				void setId(int Id){this->Id=Id;}
                int getId(){return Id;}    */
};

#endif
