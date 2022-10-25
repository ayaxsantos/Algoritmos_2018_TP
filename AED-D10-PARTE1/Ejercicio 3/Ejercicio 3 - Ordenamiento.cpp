///////////////////Programa Ordenamiento////////////////////
#include <iostream>
#include <cstring>

using namespace std;

////////////////////////////////////////////////////////////
struct archivo_general{																	//Struct correspondiente a el formato a utilizar para mostrar informacion
	char nombre_equipo[20];
	char confederacion[20];
	char letra_grupo[2];
};

struct final{																			//Struct correspondiente al formato de salida del algoritmo para sorteo aleatorio
	char pais[20];
	char confederacion[20];
	int bolillero;
};
final lista_lectura[32];																//Crear un vector de 32 posiciones, el cual se utilizara para ordenar y mostrar en pantalla
archivo_general lista_final[32];														//Creacion de un vector de 32 posiciones, para la lectura de datos

////////////////////////Funciones///////////////////////////
void conversion_archivos(char[],int,int);
void inicio_archivos();
void ordenamientos_individuales(int);
void ordenamiento_confeynombre();
void ordenamiento_total();
////////////////////////////////////////////////////////////
int main()
{
	while(true)																							//Ciclo infinito para repetir el menu
	{
		int seleccion_menu=0;																			//Variable para guardar ingreso del usuario
		cout<<"Elija el criterio de ordenameinto de los equipos sorteados de RUSIA 2018:"<<endl;		//Muestrar en pantalla titular
		cout<<"Seleccion a traves de numeros del 1 al 5..."<<endl;										//Muestrar opciones al usuario y su significado
		cout<<"1- Nombre de Grupo\n"<<"2- Nombre de Equipo\n"<<"3- Confederacion\n"<<"4- Numero de Grupo y Confederacion\n"<<"5- Numero de Grupo, Confederacion y nombre de equipo\n"<<"#Para salir ingrese cualquier letra o numero"<<endl;
		cin>>seleccion_menu;																			//Leer el valor ingresado por teclado
		inicio_archivos();																				//Llamo a la funcion, la cual lee el contenido de los archivos previos
		if(seleccion_menu==1)	ordenamientos_individuales(0);											//Si ingresa 1, ejecutar y ordeno en base a la letra de grupo enviando 0 como parametro
		else if(seleccion_menu==2)	ordenamientos_individuales(1);										//Si ingresa 2, ejecutar y ordeno en base al nombre de los equipos enviando 1 como parametro
		else if(seleccion_menu==3)	ordenamientos_individuales(2);										//Si ingresa 3, ejecutar y ordeno en base a la confederacion enviando 2 como parametro
		else if(seleccion_menu==4)	ordenamiento_confeynombre();										//Si ingresa 4, ordenar en base a la letra del grupo y a la confederacion, invocando a la funcion
		else if(seleccion_menu==5)	ordenamiento_total();												//Si ingresa 5,	ordenar en base a todos los textos que se encuentren, llamando a la respectiva funcion
		else	return 0;																				//En caso de cualquier ingreso que no sea de los anteriores, retornar 0 para finalizar el programa (se puede utilizar break tambien)
		cout<<" "<<endl;
	}
	return 0;																								
}																													
////////////////////////////////////////////////////////////
void inicio_archivos()
{
	FILE* archivo_grupoA;																				//Creacion de los archivos para ser leidos (objeto)
	FILE* archivo_grupoB;																				//Se crean en total 8 archivos, uno para cada grupo
	FILE* archivo_grupoC;																				//en especifico.
	FILE* archivo_grupoD;
	FILE* archivo_grupoE;
	FILE* archivo_grupoF;
	FILE* archivo_grupoG;
	FILE* archivo_grupoH;
	archivo_grupoA=fopen("resultadoA.dat","r");															//Se abren los archivos, cada uno con su nombre y
	archivo_grupoB=fopen("resultadoB.dat","r");															//con el parametro "r" ya que solo se leeran
	archivo_grupoC=fopen("resultadoC.dat","r");															//Estos archivos deben ser generados por el programa
	archivo_grupoD=fopen("resultadoD.dat","r");															//que hace su reespectivo sorteo aleatorio.
	archivo_grupoE=fopen("resultadoE.dat","r");
	archivo_grupoF=fopen("resultadoF.dat","r");
	archivo_grupoG=fopen("resultadoG.dat","r");
	archivo_grupoH=fopen("resultadoH.dat","r");
	
	fread(lista_lectura,sizeof(lista_lectura),1,archivo_grupoA);										//Leer contenido del primer archivo,y lo guardo en el vector que contendra los datos
	conversion_archivos("A",0,4);																		//Como los archivos no tienen letra de grupo indicada, se los asigno a cada posicion
	
	fread(&lista_lectura[4],sizeof(lista_lectura),1,archivo_grupoB); 									//Leer contenido del segundo archivo, y lo guardo a partir de la posicion 4 del vector
	conversion_archivos("B",4,8);																		//Asigno letra B en cada posicion del vector (a partir de la 4 hasta la 8, ya que hay 4 equipos por grupo)
	
	fread(&lista_lectura[8],sizeof(lista_lectura),1,archivo_grupoC);									//Se lee contenido del archivo, y vuelca el contenido para los grupos restantes
	conversion_archivos("C",8,12);																		//Asi como se asigna la letra de grupo para cada caso, respetando que son siemrpe 4 por grupo
	
	fread(&lista_lectura[12],sizeof(lista_lectura),1,archivo_grupoD);									//Se repite el proceso en los siguientes casos, siempre comenzando a guardar cada 4 posiciones
	conversion_archivos("D",12,16);
	
	fread(&lista_lectura[16],sizeof(lista_lectura),1,archivo_grupoE);
	conversion_archivos("E",16,20);
	
	fread(&lista_lectura[20],sizeof(lista_lectura),1,archivo_grupoF);
	conversion_archivos("F",20,24);
	
	fread(&lista_lectura[24],sizeof(lista_lectura),1,archivo_grupoG);
	conversion_archivos("G",24,28);	
	
	fread(&lista_lectura[28],sizeof(lista_lectura),1,archivo_grupoH);
	conversion_archivos("H",28,32);	 
}

//////////////////////////////////////////////////////////////
void conversion_archivos(char letra[],int menor,int mayor)										/*Funcion que agrega letra de grupo y pasa los datos del vector del formato anterior al solicitado 
																								recibe la letra y la posicion donde inicia y termina en el vector principal*/
{
	for(int pos=menor;pos<mayor;pos++)
	{
		strcpy(lista_final[pos].letra_grupo,letra);												//Colocar la letra de grupo en la posicion actual
		strcpy(lista_final[pos].nombre_equipo,lista_lectura[pos].pais);							//Copiar el nombre del pais de un vector a otro (el utilizado para ordenar)
		strcpy(lista_final[pos].confederacion,lista_lectura[pos].confederacion);				//Y finalemnte se copia la confederacion correspondiente a la posicion actual
	}
}
//////////////////////////////////////////////////////////////
void ordenamientos_individuales(int habilitacion)											//Metodo de la burbuja, espera numero entero para decidir el criterio
{
	archivo_general aux[1];																	//Crear variable auxiliar, del mismo tipo que el vector para poder igualar datos
	for(int pos1=0;pos1<32;pos1++)
	{
		for(int pos2=0;pos2<32-1;pos2++)
		{
			if((habilitacion==0) && (strcmp(lista_final[pos2].letra_grupo,lista_final[pos2+1].letra_grupo)>0))	//strcmp si devuelve <0,el primer caracter es menor (ASCII) aplicado a la letra de grupo (criterio)
			{																									//Si un caracter es menor, significa que esta antes en el alfabeto
				aux[0]=lista_final[pos2];																		//Guardar valor de la posicion  en variable auxiliar
				lista_final[pos2]=lista_final[pos2+1];															//Modificar el valor de la posicion actual por el de la siguiente
				lista_final[pos2+1]=aux[0];																		//Mover el valor de auxiliar a la posicion siguiente de la actual, completando el intercalado
			}
			if((habilitacion==1) && (strcmp(lista_final[pos2].nombre_equipo,lista_final[pos2+1].nombre_equipo)>0))	//strcmp si devuelve <0,el primer caracter es menor (ASCII) aplicado al nombre de equipo (criterio)
			{
				aux[0]=lista_final[pos2];																		//Guardar valor actual en auxiliar
				lista_final[pos2]=lista_final[pos2+1];															//Igualar posicion actual con valor de la posicion siguiente
				lista_final[pos2+1]=aux[0];																		//Completar intercalado, moviendo el valor de auxiliar a la siguiente posicion
			}
			if((habilitacion==2) && (strcmp(lista_final[pos2].confederacion,lista_final[pos2+1].confederacion)>0))	//Si el valor de la posicion actual es menor que el proximo (ASCII) aplicado a la confederacion (criterio)
			{
				aux[0]=lista_final[pos2];																		//Repite proceso de intercalado
				lista_final[pos2]=lista_final[pos2+1];
				lista_final[pos2+1]=aux[0];
			}
		}
	}
	for(int pos=0;pos<32;pos++)	cout<<lista_final[pos].nombre_equipo<<" "<<lista_final[pos].confederacion<<" "<<lista_final[pos].letra_grupo<<endl;		//Mostrar conjunto ordenado en pantalla, con todos sus datos
}
//////////////////////////////////////////////////////////////
void ordenamiento_confeynombre()																//Funcion que ordena en base a la letra de grupo y la confederacion
{
	archivo_general aux[1];																		//Crear variable auxiliar, del mismo tipo que el vector para poder igualar datos
	for(int rec1=0;rec1<32;rec1++)																//Recorrer todo el vector
	{
		for(int rec2=0;rec2<32-1;rec2++)
		{																						//Comparar, si la letra de grupo es menor que el siguiente, y en caso de ser iguales comparar si la confederacion es menor que en la posicion siguiente
			if((strcmp(lista_final[rec2].letra_grupo,lista_final[rec2+1].letra_grupo)>0) || ((strcmp(lista_final[rec2].letra_grupo,lista_final[rec2+1].letra_grupo)==0) && ( strcmp(lista_final[rec2].confederacion,lista_final[rec2+1].confederacion) >0)))
				{					
					aux[0]=lista_final[rec2];													//Proceso de intercalado, guardando valor posicion actual en auxiliar									
					lista_final[rec2]=lista_final[rec2+1];										//Mover el valor de la posicion siguiente a la actual
					lista_final[rec2+1]=aux[0];													//Y cambiar valor posicion siguiente por el guardado en auxiliar(posicion actual)
				}
			}
		}
	
	for(int pos=0;pos<32;pos++)	cout<<lista_final[pos].nombre_equipo<<" "<<lista_final[pos].confederacion<<" "<<lista_final[pos].letra_grupo<<endl;			//Mostrar conjunto ordenado en pantalla, con todos sus datos
}
//////////////////////////////////////////////////////////////
void ordenamiento_total()																		//Funcion que ordena en base al nombre de equipo, confederacion y la letra de grupo
{
	archivo_general aux[1];																		//Crear variable auxiliar, del mismo tipo que el vector para poder igualar datos
	for(int rec1=0;rec1<32;rec1++)																//Recorrer todo el vector
	{
		for(int rec2=0;rec2<32-1;rec2++)																	
		{																									//Comparar, si el nombre de equipo es menor que el siguiente, y en caso de ser iguales pasar al siguiente parametro; para luego
			if((strcmp(lista_final[rec2].nombre_equipo,lista_final[rec2+1].nombre_equipo) >0) ||			//comparar ahora si la confederacion es menor a la siguiente, y de ser iguales pasar al proximo parametro, para finalmente comparar si la letra de grupo es menor que la siguiente
          	((strcmp(lista_final[rec2].nombre_equipo,lista_final[rec2+1].nombre_equipo)==0) &&( strcmp(lista_final[rec2].confederacion,lista_final[rec2+1].confederacion) >0)) || 
           	((strcmp(lista_final[rec2].nombre_equipo,lista_final[rec2+1].nombre_equipo)==0) &&( strcmp(lista_final[rec2].confederacion,lista_final[rec2+1].confederacion) ==0)) &&
		    (strcmp(lista_final[rec2].letra_grupo,lista_final[rec2+1].letra_grupo) >0))
			  	{
			  
					aux[0]=lista_final[rec2];													//Proceso de intercalado, guardando valor posicion actual en auxiliar							
					lista_final[rec2]=lista_final[rec2+1];										//Mover el valor de la posicion siguiente a la actual
					lista_final[rec2+1]=aux[0];													//Y cambiar valor posicion siguiente por el guardado en auxiliar(posicion actual)
				}
			}
		}
	for(int pos=0;pos<32;pos++)	cout<<lista_final[pos].nombre_equipo<<" "<<lista_final[pos].confederacion<<" "<<lista_final[pos].letra_grupo<<endl;			//Mostrar conjunto ordenado en pantalla, con todos sus datos
}
///////////////////////////////////////////////////////////////
