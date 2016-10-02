#include "Archivo.h"

class Alumno
{
      unsigned int ced;
      char nom[30];
  public:
      Alumno()                 { ced=0;                }
      Alumno( char *n, int c ) { ced=c; strcpy(nom,n); }
      int  get_clave()         { return ced;           }
      char *get_nom()          { return nom;           }
      void set_nom(char *n)    { strcpy(nom,n);        } 
      void set_ced(char *n)    { ced= atoi(n);         }
      void imprime()     { cout<<ced<<"  "<<nom<<endl; }
};

class Materia
{
      unsigned int cod;
      char tit[80], uc;
  public:
      Materia( char *n, int c, char v ) { cod=c; strcpy(tit,n); uc=v; }
      Materia()                { cod=0;                }
      int  get_clave()         { return cod;           }
      char get_uc()            { return uc;            }
      char *get_tit()          { return tit;           }
      void set_tit(char *n)    { strcpy(tit,n);        } 
      void set_cod(char *n)    { cod= atoi(n);         }
      void set_uc( char v )    { uc=v;                 }
      void imprime()     { cout<<cod<<"  "<<tit<<"  "<<uc<<endl; }
};

class Semestre
{
      unsigned int cod;
      unsigned int ced;
  public:
      Semestre ( int v1, int v2 ) { cod=v1; ced=v2; }
      Semestre ( )                {                 }
      int  get_cod()  { return cod;                 }
      int  get_ced()  { return ced;                 }
      void imprime()  { cout<<cod<<"  "<<ced<<endl; }             
};


int main(int argc, char *argv[])
{
    Alumno clabus("",19567987);
    Archivo<Alumno>  objalu("Datos.dat");
    Archivo<Materia> objmat("Materia.dat");
    Archivo<Semestre>objsem("Inscritos.dat");
    objmat.Abrir(ios::in | ios::binary);    
    objalu.Abrir(ios::in | ios::binary);
    objsem.Abrir(ios::in | ios::binary);
    objalu.Imprimir();
    if ( objalu.Buscar_Sec(clabus) ) 
    {
             cout<<"Alumno encontrado:"<<endl;
             clabus.imprime();
             Materia clamat("",111,' ');
             if ( objmat.Buscar_Sec(clamat) )
             {
                  cout<<"Materia encontrada: ";
                  clamat.imprime();
             }
    }
    else
             cout<<"No se localizo Alumno!"<<endl;
    cout<<endl;
    objmat.Imprimir();  
    cout<<endl;
    objsem.Imprimir();        
    objalu.Cerrar();   
    objmat.Cerrar();
    objsem.Cerrar();
    system("PAUSE");
    return EXIT_SUCCESS;
}
