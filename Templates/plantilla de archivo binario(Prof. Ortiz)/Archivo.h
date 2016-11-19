#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Archivo
{
      fstream pf;
      char nom[40];
      T buffer;
      int lon, N;
  public:
      Archivo( )                               {                 }   
      Archivo(char *n)                         { strcpy(nom,n);  }
      void Abrir( const std::_Ios_Openmode &t ){ pf.open(nom,t); }
      void Longi( )             { lon= sizeof(T);                }
      void Leer    ( T &b )     { pf.read ((char*)&b,sizeof(T)); }
      void Escribir( T &b )     { pf.write((char*)&b,sizeof(T)); }
      void Cerrar()             { pf.close();                    } 
      bool EsFin()              { return pf.eof();               } 
      bool Falla()              { return pf.fail();              }
      void Limpiar()            { pf.clear();                    }
      void Posicionar( int p )  { pf.seekg(p*lon, ios::beg );    }
      void Tamano();
      void Imprimir(); 
      void Ordenar(); 
      bool Buscar_Sec     ( T &bus, int pos=0, int Max=99999999 );
      bool Buscar_Binario ( T &bus );  
};

template <class T>
void Archivo<T>::Tamano() 
{ 
     Longi(); 
     pf.seekg(0,ios::end); 
     pf.clear(); 
     N= pf.tellg()/lon; 
}

template <class T>
void Archivo<T>::Imprimir()
{
    Limpiar();
    Posicionar(0);  
    while ( true )
    { 
      Leer(buffer);  
      if ( EsFin() ) break;    
      buffer.imprime();
    }
    cout<<endl;
}

template <class T>
bool Archivo<T>::Buscar_Sec( T &bus, int pos, int Max )
{
     int i;
     bool enc=false;
     Limpiar();
     Posicionar(pos);
     while ( i<=Max && !enc )
     { 
       Leer(buffer);  
       if ( EsFin() ) break;    
       if ( bus.get_clave()==buffer.get_clave() )
       {
           enc=true;
           bus= buffer;
       }
	   else i++;
     } // fin while 
     return enc;        
}

template <class T>
bool Archivo<T>::Buscar_Binario( T &bus )
{
     bool enc=false;
     int li=0, ls=N-1, pm;
     Limpiar();
     while ( !enc && li<=ls )
     {
           pm= (li+ls)/2;
           Posicionar(pm);
           Leer(buffer);
           if ( bus.get_clave()==buffer.get_clave() )
           {
                enc=true;
                bus=buffer;
           }
           else if ( bus.get_clave()< buffer.get_clave() )
                ls= pm-1;
           else
                li= pm+1;
     }
     return enc;
}

template <class T>
void Archivo<T>::Ordenar()
{
     T aux, ini;
     int i, j, pmen;  
     Tamano();
     for ( i=0; i<N-1; i++ )
     {
        Posicionar(i);
        Leer (aux); ini= aux;
        pmen=i;
        for (j=i+1; j<N; j++)
        {
            Posicionar(j);
            Leer(buffer);
            if ( buffer.get_clave()< aux.get_clave() )
            {
                 aux= buffer;
                 pmen= j;
            }
        } // fin for j
        if ( i!=pmen )
        {
             Posicionar(i);
             Escribir(aux);
             Posicionar(pmen);
             Escribir(ini);
        } 
     }// fin for i 
}
