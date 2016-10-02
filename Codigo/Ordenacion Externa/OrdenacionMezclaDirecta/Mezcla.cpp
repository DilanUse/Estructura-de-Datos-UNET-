// header files...
#include "Mezcla.h"
#include "Datos.h"
#include <fstream>
#include <iostream>
using namespace std; // uso del espacio de nombres standar...


 /**
*	@brief	constructor de Mezcla que inicia sus atributos
*	@since 1.0
*	@param string nombre del archivo original a ordenar
* 	@param string nombre del archivo auxiliar1
*	@param string nombre del archivo auxiliar2
*/
Mezcla::Mezcla(string orig, string aux1, string aux2)
{
	this->file_nom = orig;
	this->fileAux1_nom = aux1;
	this->fileAux2_nom = aux2;
	this->numReg = cuentaReg(); // inicia el numero de registros
} // fin del constructor 



  /**
  *	@brief	determina el número de registros del archivo original a ordenar
  *	@since 1.0
  *	@return int numero de registros en el archivo original a ordenar
  */
int Mezcla::cuentaReg() const
{
	int registros = 0;
	Datos buffer; // buffer para almacenar registros
	fstream file(this->file_nom.c_str(), ios::in | ios::binary);



	// cuenta los registros 
	while (!file.eof())
	{
		file.read((char*)&buffer, sizeof(Datos));
		++registros;
	} // fin del while 


	file.close();
	return registros;
} // fin de cuentaReg
