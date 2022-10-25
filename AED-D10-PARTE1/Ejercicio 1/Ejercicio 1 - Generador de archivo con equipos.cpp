#include <iostream>
#include <cstring>

using namespace std;

////////////////////////////////////////////////////////////////////
struct paises{									//Struct de paises, el cual en cada caso se asignan los datos de forma directa
	char pais[20];	
	char confederacion[20];
	int numero_bolillero;
};

paises bolillero1[8]=
{
	 {"Rusia","UEFA",1},	
	 {"Alemania","UEFA",1},	
	 {"Brasil","CONMEBOL",1},	
	 {"Portugal","UEFA",1},	
	 {"Argentina","CONMEBOL",1},	
	 {"Belgica","UEFA",1},	
	 {"Polonia","UEFA",1},	
	 {"Francia","UEFA",1},
	 
};
paises bolillero2[8]=
{
	 {"Espana","UEFA",2},	
	 {"Peru","CONMEBOL",2},		
	 {"Suiza","UEFA",2},		
	 {"Inglaterra","UEFA",2},	
	 {"Colombia","CONMEBOL",2},	
	 {"Mexico","CONCACAF",2},	
	 {"Uruguay","CONMEBOL",2},	
	 {"Croacia","UEFA",2},	
};
paises bolillero3[8]=
{
	 {"Dinamarca","UEFA",3},
	 {"Islandia","UEFA",3},
	 {"CostaRica","CONCACAF",3},
	 {"Suecia","UEFA",3},
	 {"Tunez","CAF",3},
	 {"Egipto","CAF",3},
	 {"Senegal","CAF",3},
	 {"Iran","AFC",3},
};
paises bolillero4[8]=
{
	 {"Serbia","UEFA",4},
	 {"Nigeria","CAF",4},
	 {"Australia","CAF",4},
	 {"Japon","AFC",4},
	 {"Marruecos","CAF",4},
	 {"Panama","CONCACAF",4},
	 {"CoreadelSur","AFC",4},
	 {"ArabiaSaudita","AFC",4},
};
paises listado[32];
////////////////////////////////////////////////////////////////////

int main() 
{
	int aux=0;
	FILE* f;												//Creo archivo y le doy nombre
	f=fopen("mundial.dat","wb+");							//Abro el archivo, como lo voy a borrar y editar agrego wt+
	cout<<"Generando archivo..."<<endl;
	fwrite(bolillero1,sizeof(bolillero1),1,f);				//Escribo en el archivo los datos
	fwrite(bolillero2,sizeof(bolillero2),1,f);
	fwrite(bolillero3,sizeof(bolillero3),1,f);
	fwrite(bolillero4,sizeof(bolillero4),1,f);
	fflush(f);
	fseek(f,0,SEEK_SET);
	fread(listado,sizeof(listado),1,f);				//Los muestro en pantalla (Agregado, no lo pide el enunciado)
	for(aux=0;aux<32;aux++){
		cout<<listado[aux].pais<<" "<<listado[aux].confederacion<<" "<<listado[aux].numero_bolillero<<endl;
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////
