#include <iostream>
#include <string>
#include "ColaD.h"
#include "ArchivoMp3.h"
#include <conio.h>
#include "Archivo.h"
#include <windows.h>

using namespace std; // uso del espacio de nombres std


int main(int argc, char** argv) 
{
	Archivo* mp3_text = new Archivo("mp3.txt"); // archivo de etxto
	ColaD<ArchivoMp3>* mp3_cola = new ColaD<ArchivoMp3>(); // vola de canciones
	string* buffer; // leer del archivo
	ArchivoMp3* reproduciendo = NULL; // archivo que se reproduce actualmente 
	int tiempoRepro = 0; // tiempo transcurrido para una cancion que se reproduce
	bool pausa = true; // determina si esta pausada la reproduccion
	string mensaje; // mensaje especial para el usuario
	char res; // almacena la respuesta del usuario
	
	
	mp3_text->abrir(); // abre el archivo

	 
	// mientras la opcion selecionada sea diferente de X(salir)
    do
	{
		system("cls"); 
        cout<<"**************'Reproductor MP3'*************\n"<<endl;
        cout<<"\tc.-Agregar archivo mp3"<<endl;
        cout<<"\tr.-Reproducir archivo mp3"<<endl;
        cout<<"\tp.-Pausar archivo: "<<endl;
        cout<<"\tn.-Siguiente archivo: "<<endl;
        cout<<"\ts.-Detener archivo: "<<endl;
        cout<<"\tx.Salir del reproductor "<<endl;
        cout<<"\tMensaje: "<< mensaje << endl;
        mensaje = ""; // borro mensaje
        
        
        // muetro la cola de reproduccion
        cout << endl << "\t*Cola de reproduccion: " << endl << "\t";
        
        if( mp3_cola->getFrente() == NULL )
        	cout << "Vacia..." << endl;
        else
        	mp3_cola->imprimir();
        
        
        // muetro la informacion de la cancion actual
        cout << endl << "\t* Informacion de la cancion actual: " << endl;
        
		if( reproduciendo != NULL )
		{
			cout << "\tTitulo:" << reproduciendo->nombre << endl;
			cout << "\tDuracion: " << reproduciendo->minuto << ":" << reproduciendo->segundo << endl;
			cout << "\tEstado: " << ( pausa ? "Pausada" : "Reproduciendo" ) << endl;
			cout << "\tTiempo transcurrido: " << tiempoRepro / 60 << ":" << tiempoRepro % 60 << endl;
		}
		else
			cout << "\tNinguna..." << endl;
			
			
		cout << endl << "\t*Su opcion: ";  
			
        
        // si hay una tecla en el buffer del teclado
        if( kbhit() )
        	res = getche(); // leo la tecla
        	
        
		// reacciona de acuerdo a la opcion de usuario        
        switch(res)
		{	
			// leeemos una cancion y la agregamos a la cola 
			case 'C':
            case 'c':
            	if( !mp3_text->isFinal() )
            	{
            		buffer = mp3_text->leerCampos( ',', 3 );
				 	mp3_cola->agregar( new ArchivoMp3( buffer[0], 
					 atoi( buffer[1].c_str()), atoi( buffer[2].c_str()) ));
				}
				else
					mensaje = "No hay canciones para agregar...";
					
            	break; // fin de C
        
        	// elimina de la cola y pasa la informacion al reproductor 
        	case 'R':
            case 'r': 
            	// si la cola esta vacia y no hay canciones reproduciendose
            	if( mp3_cola->getFrente() == NULL && reproduciendo == NULL )
            	{
            		mensaje = "No hay canciones en la cola de reproduccion...";
            		break;
				} // fin del if
				
				
				// si ya hay una cancion en reproduccion
				if( !pausa )
					mensaje = "Ya se esta reproducciendo uan cancion...";
				
				
				// si esta pausada la reproduccion 
            	if( pausa )
            	{
					// si es la primera cancion a reproduccion
					if( reproduciendo == NULL )
					{
						reproduciendo = mp3_cola->getFrente()->getInfo(); // obtengo la cancion
                		mp3_cola->eliminar(); 
                		pausa = false;
					}
					else
					{
						pausa = false;
					} // fin del if...else
                } // fin del if
                
                break; // fin de R
            
            // pauso el contador de tiempo de reproduccion
            case 'P':
            case 'p':       	
            	// si no se esta reproduciendo nada
            	if( reproduciendo == NULL || pausa )
            		mensaje = "Debe iniciar la reproduccion ...";
            		
            	pausa = true; // reproduccion pausada
            	break; // fin de P
            	
               
            // elimina de la cola y pasa la informacion al reproductor
            case 'N':
            case 'n': 
            	// si se esta reproduciendo y la cola no esta vacia
            	if( reproduciendo != NULL && mp3_cola->getFrente() != NULL )
            	{
                	reproduciendo = mp3_cola->getFrente()->getInfo(); // obtengo la cancion
                	mp3_cola->eliminar();  // la saco de la cola
                	tiempoRepro = 0; // inicio el tiempo de la nueva cancion 
                } // fin del if
               
                if( reproduciendo == NULL )
                	mensaje = "Debe iniciar la reproduccion...";
                else if( mp3_cola->getFrente() == NULL )
                	mensaje = "No hay canciones en la cola de reproduccion...";
                	
            	break; // fin de N
            	
            // pauso la reproduccion y reinicio la cancion
			case 'S':	
            case 's': 
            	pausa = true; // reproduccion pausada
            	tiempoRepro = 0; // reinicio la cancion

            	// si no se esta reproduciendo nada
            	if( reproduciendo == NULL || pausa )
            		mensaje = "Debe iniciar la reproduccion...";
            		
            	break; // fin de S
        } // fin del switch
                
             
		// si la reproduccion no esta pausada   
    	if( !pausa)
    		tiempoRepro++; // aumento tiempo de reproduccion
    		
    		
    	// si cancion termino
    	if( reproduciendo != NULL && tiempoRepro >= ( reproduciendo->minuto * 60 + reproduciendo->segundo) )
    	{
    		// si la cola no esta vacia
    		if( mp3_cola->getFrente() != NULL )
    		{
    			reproduciendo = mp3_cola->getFrente()->getInfo(); // obtengo la cancion
        		mp3_cola->eliminar(); 
        		tiempoRepro = 0; // inicio el tiempo de la nueva cancion 
        	}
        	else
        	{
        		mensaje = "No hay mas canciones para reproducir";
        		reproduciendo = NULL; // ya no hay nada reproduciendose 
        	}
		} // fin del if
    		
    	
    	Sleep(1000); // retraso un segundo la ejecucion
    	fflush(stdin); // limpio buffer de entrada
    	res = ' '; // reinicio caracter de entrada del usuario
    }while(toupper(res)!='X');
    
    
    
	return 0;
}
