#pragma once
// header files...
#include <string>


/**
*	@Autor: Dilan Useche
*	@Date: 21/09/2016
*	@Release: 21/09/2016
*	@Version: 1.0
*	@brief Representación de la Mezcla de Archivos externos.
*/
class Mezcla
{
public:
	std::string file_nom; // nombre del archivo original a ordenar
	std::string fileAux1_nom; // nombre del archivo auxiliar1
	std::string fileAux2_nom; // nombre del archivo auxiliar2
	int numReg; // numero de registros en el archivo original a ordenar
	int cuentaReg() const; // determina el numero de registros en el archivo

public:
	Mezcla(std::string, std::string, std::string);
}; // fin de Mezcla 

