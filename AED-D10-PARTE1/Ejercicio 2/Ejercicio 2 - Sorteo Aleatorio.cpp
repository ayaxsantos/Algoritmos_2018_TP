////////////////////Sorteo Aleatorio Mundial/////////////////////
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>

using namespace std;

/////////////////////Variables y estructuras globales//////////////////
struct lectura_bolilleros{												//Declaracion estructura tipo lectura_bolilleros
	char pais[20];
	char confederacion[20];
	int bolillero;
};

struct grupo{															//Declaracion estructura tipo grupo
	char pais[20];
	char confederacion[20];	
	int bolillero;
};

lectura_bolilleros equipos[32];											//Estructura que contendra la lista general de equipos con todos ellos

grupo grupo_a[4];														//Estructuras correspondientes a cada grupo, para asi escribir en 8 archivos diferentes
grupo grupo_b[4];
grupo grupo_c[4];
grupo grupo_d[4];
grupo grupo_e[4];
grupo grupo_f[4];
grupo grupo_g[4];
grupo grupo_h[4];

int variable_pasoA=0;													//Variables utilizadas para el paso 2, para sortear primero cabeza de grupo de la "CONMEBOL"
int variable_pasoB=0;
int variable_pasoC=0;
int variable_pasoD=0;
int variable_pasoE=0;
int variable_pasoF=0;
int variable_pasoG=0;
int variable_pasoH=0;
bool resorteo=true;
bool repeticionA,repeticionB,repeticionC,repeticionD,repeticionE,repeticionF,repeticionG,repeticionH;

///////////////////////////Funciones//////////////////////////////
void archivos();
void sorteo();
void genero_archivos();
grupo paso1(grupo[]);														
grupo paso2(grupo[]);
grupo paso3(grupo[]);
grupo paso4repetido(grupo[]);
int numero_aleatorio();
bool decidir_resorteo(grupo[]);
int comparacion_paises(grupo[],char[]);
////////////////////////////////////////////////////////////////
int main()													
{
	srand(time(NULL));																			//InicializAar la seed para la funcion rand()
	int seleccion_menu=0;																		//Variable de seleccion de menu
	cout<<"Bienvenido al programa de sorteo de grupos de Rusia 2018 FIFA WORLD CUP:"<<endl;		//Muestrar en pantalla titulo
	cout<<"Presione 1 si quiere realizar el sorteo: "<<endl;		
	cin>>seleccion_menu;																		//Leer Valor del usuario
	if(seleccion_menu==1)																		//Si es 1...
	{
		archivos();																				//Leer el archivo y lo vuelco en un vector
		sorteo();																				//Realizar el sorteo de cada grupo
		genero_archivos();																		//Vuelcar su contenido en los 8 nuevos archivos
	}
	else																						//Si no es 1...
	{
		cout<<"El programa finalizara aqui"<<endl;												//Muestrar en pantalla fin del programa
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////
void archivos() 														//Funcion que lee el cotenido del archivo fuente con los grupos, confederaciones y bolilleros
{
	FILE* f;																					//Crar un archivo F*
	f=fopen("mundial.dat","r");																	//Abrir el archivo creado
	fread(equipos,sizeof(equipos),1,f);															//Leer su contenido
	strcpy(grupo_a[0].pais,equipos[0].pais);													//Copio los datos del pais en la primera posicion del vector (RUSIA)
	strcpy(grupo_a[0].confederacion,equipos[0].confederacion);									//Asi como su confederacion y bolillero, al primer grupo por ser el anfitrion
	grupo_a[0].bolillero=equipos[0].bolillero;
	equipos[0].bolillero=0;																		//Igualo a 0 el bolillero para que no salga seleccionado en los sorteos
}
//////////////////////////////////////////////////////////////////////
void sorteo()															//Realiza el sorteo total, llamando otras funciones dividias por pasos
{
	grupo_b[0] = paso1(grupo_b);															//Se ejecuta la funcion paso 1 para todos los grupos
	grupo_c[0] = paso1(grupo_c);															//la cual recibe como parametro el vector de grupo
	grupo_d[0] = paso1(grupo_d);															//Para trabajar con el, y como retorna el equipo sorteado		
	grupo_e[0] = paso1(grupo_e);															//Lo coloco en la primera posicion de cada grupo
	grupo_f[0] = paso1(grupo_f);
	grupo_g[0] = paso1(grupo_g);
	grupo_h[0] = paso1(grupo_h);
//Realizo el primero donde en cabeza de grupo sea de la conmebol	
	if(strcmp(grupo_b[0].confederacion,"CONMEBOL")==0)										//Si la confederacion del cabeza de grupo es "CONMEBOL"...
	{	
		grupo_b[1] = paso2(grupo_b);														//Sorteo y asigno una variable, lo mismo para los demas casos
		variable_pasoB=1;
	}
	if(strcmp(grupo_c[0].confederacion,"CONMEBOL")==0)
	{
		grupo_c[1] = paso2(grupo_c);														//Sortea y asigna variable
		variable_pasoC=1;
	}
	if(strcmp(grupo_d[0].confederacion,"CONMEBOL")==0)
	{
		grupo_d[1] = paso2(grupo_d);														//Sortea y asigna variable
		variable_pasoD=1;
	}
	if(strcmp(grupo_e[0].confederacion,"CONMEBOL")==0)
	{
		grupo_e[1] = paso2(grupo_e);														//Sortea y asigna variable
		variable_pasoE=1;
	}
	if(strcmp(grupo_f[0].confederacion,"CONMEBOL")==0)										
	{
		grupo_f[1] = paso2(grupo_f);														//Sortea y asigna variable
		variable_pasoF=1;
	}
	if(strcmp(grupo_g[0].confederacion,"CONMEBOL")==0)
	{
		grupo_g[1] = paso2(grupo_g);														//Sortea y asigna variable
		variable_pasoG=1;
	}
	if(strcmp(grupo_h[0].confederacion,"CONMEBOL")==0)
	{
		grupo_h[1] = paso2(grupo_h);														//Sortea y asigna variable para el grupo h, finalizando el sorteo del paso 2
		variable_pasoH=1;
	}
	if(variable_pasoA==0)	grupo_a[1] = paso2(grupo_a);				//En los grupos donde no se asigno variable, realizo el sorteo asi ignoro los sorteados anteriormente
	if(variable_pasoB==0)	grupo_b[1] = paso2(grupo_b);				//Como la funcion paso2 retorna el equipo sorteado, lo guardo
	if(variable_pasoC==0)	grupo_c[1] = paso2(grupo_c);				//en la segunda posicion del grupo
	if(variable_pasoD==0)	grupo_d[1] = paso2(grupo_d);				//Esto se realiza con todos los grupos, respetando la segunda posicion
	if(variable_pasoE==0)	grupo_e[1] = paso2(grupo_e);
	if(variable_pasoF==0)	grupo_f[1] = paso2(grupo_f);
	if(variable_pasoG==0)	grupo_g[1] = paso2(grupo_g);
	if(variable_pasoH==0)	grupo_h[1] = paso2(grupo_h);
///////////////////////////////////////////////////////////////////////////////
	while(resorteo==true)
	{	
		for(int conta=16;conta<24;conta++)	equipos[conta].bolillero=3;		//Reasigno numero de bolillero, ya que se utiliza el numero de bolillero "0" simbolicamente para representar equipos ya sorteados
		resorteo=false;														//Bajar bandera de resorteo											
		
		grupo_a[2] = paso3(grupo_a);										//Realizo el paso 3, enviando como parametro el grupo nuevamente
		grupo_b[2] = paso3(grupo_b);										//Y asignando el equipo sorteado a la posicion 3 de cada grupo
		grupo_c[2] = paso3(grupo_c);	
		grupo_d[2] = paso3(grupo_d);	
		grupo_e[2] = paso3(grupo_e);	
		grupo_f[2] = paso3(grupo_f);	
		grupo_g[2] = paso3(grupo_g);
		grupo_h[2] = paso3(grupo_h);
		if(repeticionA=decidir_resorteo(grupo_a))	resorteo=true;		//Para cada grupo sorteado, evaluo si ocurrieron repeticiones
		if(repeticionB=decidir_resorteo(grupo_b))	resorteo=true;		//de confederaciones que no esten permitidas por consigna
		if(repeticionC=decidir_resorteo(grupo_c))	resorteo=true;		//En caso de que esten, la funcion decidir_resorteo() devuelve true
		if(repeticionD=decidir_resorteo(grupo_d))	resorteo=true;		//y debido a los if levantar la bandera para resorteo
		if(repeticionE=decidir_resorteo(grupo_e))	resorteo=true;		//El bucle se repetira hasta que no haya ninguna repeticion no permitida
		if(repeticionF=decidir_resorteo(grupo_f))	resorteo=true;		//quedando la variable resorteo el false rompiendo el bucle.
		if(repeticionG=decidir_resorteo(grupo_g))	resorteo=true;
		if(repeticionH=decidir_resorteo(grupo_h))	resorteo=true;		
	}
	resorteo=true;
	
	while(resorteo==true)
	{
		for(int conta=24;conta<32;conta++)	equipos[conta].bolillero=4;			//Reasignar numero de bolillero, porque se utilizan para representar equipos sorteados
		resorteo=false;															//Igualar a 0 la bandera de resorteo	
		
		grupo_a[3] = paso4repetido(grupo_a);									//Relizar el sorteo con los grupos del cuarto bolillero
		grupo_b[3] = paso4repetido(grupo_b);									//igualando el pais retornado por la funcion 
		grupo_c[3] = paso4repetido(grupo_c);									//En este caso, con paises del bolillero4
		grupo_d[3] = paso4repetido(grupo_d);									//Se debe igualar a la ultima posicion del vector de cada grupo
		grupo_e[3] = paso4repetido(grupo_e);	
		grupo_f[3] = paso4repetido(grupo_f);	
		grupo_g[3] = paso4repetido(grupo_g);
		grupo_h[3] = paso4repetido(grupo_h);
		
		if(repeticionA=decidir_resorteo(grupo_a))	resorteo=true;				//Verificar repeticion de confederacion no permitidas
		if(repeticionB=decidir_resorteo(grupo_b))	resorteo=true;				//llamando a la funcion que las compara, retornando true o false
		if(repeticionC=decidir_resorteo(grupo_c))	resorteo=true;				//Si devuelve true encontrando repeticiones, levantar flag de resorteo
		if(repeticionD=decidir_resorteo(grupo_d))	resorteo=true;
		if(repeticionE=decidir_resorteo(grupo_e))	resorteo=true;
		if(repeticionF=decidir_resorteo(grupo_f))	resorteo=true;
		if(repeticionG=decidir_resorteo(grupo_g))	resorteo=true;
		if(repeticionH=decidir_resorteo(grupo_h))	resorteo=true;
	}	
}//Finaliza el sorteo y se lo considera valido
//////////////////////////////////////////////////////////////////////
int numero_aleatorio()													//Funcion que devuelve un numero aleatorio de tipo entero
{	
	int numero=rand();													//utilizo la funcion rand() para obtener un numero aleatorio, con la seed de tiempo
	return numero;														//retorno el numero
}
//////////////////////////////////////////////////////////////////////
grupo paso1(grupo sorteado[])											//Funcion que devuelve una variable de tipo "grupo", el valor retornado de esta funcion se guarda dentro de un vector de struct tipo grupo
{																		
	int valor=numero_aleatorio()%8;										//Llamo a la funcion y genero un numero aleatorio entre 0 y 8 que voy a utilizar para posicionarme en un vector con todos los equipos
	while(equipos[valor].bolillero!=1)									//Mientras el pais de la posicion, que es aleatoria no pertenezca al bolillero 1...
	{
		valor=numero_aleatorio()%8;										//Sigo obteniendo numeros aleatorios
	}
	strcpy(sorteado[0].pais,equipos[valor].pais);						//De pertenecer al bolillero 1, guardo el pais en sorteado
	strcpy(sorteado[0].confederacion,equipos[valor].confederacion);		//Asi como su confederacion
	sorteado[0].bolillero=equipos[valor].bolillero;						//Y numero de bolillero
	equipos[valor].bolillero=0;											//Igualo a 0 el bolillero del pais en la lista general para identificar que salio sorteado
	return sorteado[0];													//Devuelvo el valor
}
//////////////////////////////////////////////////////////////////////
grupo paso2(grupo sorteado[])											//Fucion correspondiente al paso 2, del mismo tipo que el paso anterior
{
	int valor=numero_aleatorio()%16;									//Busco numero aleatorio del 0 al 16
	while((equipos[valor].bolillero!=2) || ((strcmp(sorteado[0].confederacion,"CONMEBOL")==0) && (strcmp(equipos[valor].confederacion,"CONMEBOL")==0)))
	{																	//Mientras no pertenezca al bolillero 2 y strcmp sea 0 en ambos casos
		valor=numero_aleatorio()%16;									//Sigo buscando numeros
	}
	strcpy(sorteado[1].pais,equipos[valor].pais);						//Si es correcto guardo todos los datos en sorteado
	strcpy(sorteado[1].confederacion,equipos[valor].confederacion);
	sorteado[1].bolillero=equipos[valor].bolillero;
	equipos[valor].bolillero=0;											//Igualo a 0 para que no salga sorteado nuevamente
	return sorteado[1];													//Retorno sorteado[1]
}
//////////////////////////////////////////////////////////////////////
grupo paso3(grupo sorteado[])											//Funcion que realiza el sorteo del paso 3, devuelve posicion e informacion del vector grupo
{
	int valor=numero_aleatorio()%24;									//Obtengo numero aleatorio del 0 a 24
		while(equipos[valor].bolillero!=3)								//Mientras no sea del bolillero 3 o se repitan confederaciones...
	{		
		valor=numero_aleatorio()%24;									//Sigo buscando numeros
	}
	strcpy(sorteado[2].pais,equipos[valor].pais);						//Cuando sea correcto, guardo todos sus datos en sorteado
	strcpy(sorteado[2].confederacion,equipos[valor].confederacion);
	sorteado[2].bolillero=equipos[valor].bolillero;
	equipos[valor].bolillero=0;											//Igualo a 0 para que no vuelva a sortearse
	return sorteado[2];													//Devuelvo sorteado[2]
}
//////////////////////////////////////////////////////////////////////
grupo paso4repetido(grupo sorteado[])									//Funcion similar al paso 3, solo que utilizando equipos del bolillero 4
{
	int valor=numero_aleatorio()%32;									//Finalmente, obtengo numeros de 0 a 32
	while(equipos[valor].bolillero!=4)									//Mientras no sea del bolillero 4 y se repitan confederaciones...
	{
		valor=numero_aleatorio()%32;									//Busco numeros y verifico las confederaciones
	}
	strcpy(sorteado[3].pais,equipos[valor].pais);						//Cuando es correcto, guardo sus datos en sorteado
	strcpy(sorteado[3].confederacion,equipos[valor].confederacion);
	sorteado[3].bolillero=equipos[valor].bolillero;
	equipos[valor].bolillero=0;											//Igualo para que no se vuelva a sortear
	return sorteado[3];													//Retorno sorteado [3]
}
//////////////////////////////////////////////////////////////////////
bool decidir_resorteo(grupo grupo[])									//Funcion que verifica repeticiones de confederaciones en grupo
{
	int conta=0,conta_caf=0,conta_afc=0,conta_concacaf=0,conta_conmebol=0;				//Crear variables contadoras para cada confederacion
	char cadena_uefa[20]="UEFA", cadena_concacaf[20]="CONCACAF", cadena_caf[20]="CAF", cadena_afc[20]="AFC";	//Cadena de caracteres con las confederaciones, se realizo de esta forma para evitar advertencias en el compilador
	conta=comparacion_paises(grupo,cadena_uefa);																//LLamar funcion que recorre el vector del grupo, buscando las repeticiones. Sus parametros son la confederacion y el vector del grupo	
	if(conta<=2)																								//Permito que haya 2 equipos de la UEFA, de lo contrario devuelvo true
	{			
		conta_caf=comparacion_paises(grupo,cadena_caf);															//LLamo a las funciones para recorrer el vector del grupo con cada confederacion restante
		conta_afc=comparacion_paises(grupo,cadena_afc);															//Cabe recalcar, que no se compara con la conmebol debido a que no hay ningun equipo
		conta_concacaf=comparacion_paises(grupo,cadena_concacaf);												//perteneciente a esta confederacion en los ultimos 2 grupos
		if((conta_caf!=0) || (conta_afc!=0) || (conta_concacaf!=0))	return true;								//Coincidencias de estas ultimas confederaciones, devuelve true
		else return false;
	}
	else	return true;																						//si no hay conincidencias de ningun tipo, devuelve false
}
//////////////////////////////////////////////////////////////////////
int comparacion_paises(grupo grupo[],char confe[])						//Compara coincidencias de cadenas de caracteres, utilizada para comparar las confederaciones
{
	int conta=0;																								//Variable contadora de repeticiones
	for(int rec=0;rec<4;rec++)								
	{
		for(int rec2=0;rec2<4;rec2++)																			//Recorrer todo el vector del grupo
		{
			if((strcmp(grupo[rec].confederacion,confe)==0) && (strcmp(grupo[rec2].confederacion,confe)==0) && (rec!=rec2))	conta++;	//Cada vez que encuentra concidencia, incrementa el contador
		}
	}
	return conta;																								//Devuelve cantidad de repeticiones
}
//////////////////////////////////////////////////////////////////////
void genero_archivos()													//Funcion que genera archivos y a su vez muestra en pantalla el resultado del sorteo
{
	FILE* archivo_grupoA;										//Genero los archivos
	FILE* archivo_grupoB;										//Para guardar los valores de cada grupo
	FILE* archivo_grupoC;										//(pedido por consigna)
	FILE* archivo_grupoD;
	FILE* archivo_grupoE;
	FILE* archivo_grupoF;
	FILE* archivo_grupoG;
	FILE* archivo_grupoH;
//Abro los Archivos	
	archivo_grupoA=fopen("resultadoA.dat","wb+");
	archivo_grupoB=fopen("resultadoB.dat","wb+");
	archivo_grupoC=fopen("resultadoC.dat","wb+");
	archivo_grupoD=fopen("resultadoD.dat","wb+");
	archivo_grupoE=fopen("resultadoE.dat","wb+");
	archivo_grupoF=fopen("resultadoF.dat","wb+");
	archivo_grupoG=fopen("resultadoG.dat","wb+");
	archivo_grupoH=fopen("resultadoH.dat","wb+");
//Escribo en archivos
	fwrite(grupo_a,sizeof(grupo_a),1,archivo_grupoA);
	fwrite(grupo_b,sizeof(grupo_b),1,archivo_grupoB);
	fwrite(grupo_c,sizeof(grupo_c),1,archivo_grupoC);
	fwrite(grupo_d,sizeof(grupo_d),1,archivo_grupoD);
	fwrite(grupo_e,sizeof(grupo_e),1,archivo_grupoE);
	fwrite(grupo_f,sizeof(grupo_f),1,archivo_grupoF);
	fwrite(grupo_g,sizeof(grupo_g),1,archivo_grupoG);
	fwrite(grupo_h,sizeof(grupo_h),1,archivo_grupoH);
//Borro el buffer de los archivos
	fflush(archivo_grupoA);
	fflush(archivo_grupoB);
	fflush(archivo_grupoC);
	fflush(archivo_grupoD);
	fflush(archivo_grupoE);
	fflush(archivo_grupoF);
	fflush(archivo_grupoG);
	fflush(archivo_grupoH);
//Leo los archivos generados
	fseek(archivo_grupoA,0,SEEK_SET);
	fread(grupo_a,sizeof(grupo_a),1,archivo_grupoA);
	
	fseek(archivo_grupoB,0,SEEK_SET);
	fread(grupo_b,sizeof(grupo_b),1,archivo_grupoB);
	
	fseek(archivo_grupoC,0,SEEK_SET);
	fread(grupo_c,sizeof(grupo_c),1,archivo_grupoC);
	
	fseek(archivo_grupoD,0,SEEK_SET);
	fread(grupo_d,sizeof(grupo_d),1,archivo_grupoD);
	
	fseek(archivo_grupoE,0,SEEK_SET);
	fread(grupo_e,sizeof(grupo_e),1,archivo_grupoE);
	
	fseek(archivo_grupoF,0,SEEK_SET);
	fread(grupo_f,sizeof(grupo_f),1,archivo_grupoF);
	
	fseek(archivo_grupoG,0,SEEK_SET);
	fread(grupo_g,sizeof(grupo_g),1,archivo_grupoG);

	fseek(archivo_grupoH,0,SEEK_SET);
	fread(grupo_h,sizeof(grupo_h),1,archivo_grupoH);
//Muestro su contenido	
	for(int val=0;val<4;val++)	cout<<grupo_a[val].pais<<" "<<grupo_a[val].bolillero<<" "<<grupo_a[val].confederacion<<endl;
	cout<<""<<endl;
	for(int val=0;val<4;val++)	cout<<grupo_b[val].pais<<" "<<grupo_b[val].bolillero<<" "<<grupo_b[val].confederacion<<endl;
	cout<<""<<endl;
	for(int val=0;val<4;val++)	cout<<grupo_c[val].pais<<" "<<grupo_c[val].bolillero<<" "<<grupo_c[val].confederacion<<endl;
	cout<<""<<endl;
	for(int val=0;val<4;val++)	cout<<grupo_d[val].pais<<" "<<grupo_d[val].bolillero<<" "<<grupo_d[val].confederacion<<endl;
	cout<<""<<endl;
	for(int val=0;val<4;val++)	cout<<grupo_e[val].pais<<" "<<grupo_e[val].bolillero<<" "<<grupo_e[val].confederacion<<endl;
	cout<<""<<endl;
	for(int val=0;val<4;val++)	cout<<grupo_f[val].pais<<" "<<grupo_f[val].bolillero<<" "<<grupo_f[val].confederacion<<endl;
	cout<<""<<endl;
	for(int val=0;val<4;val++)	cout<<grupo_g[val].pais<<" "<<grupo_g[val].bolillero<<" "<<grupo_g[val].confederacion<<endl;
	cout<<""<<endl;
	for(int val=0;val<4;val++)	cout<<grupo_h[val].pais<<" "<<grupo_h[val].bolillero<<" "<<grupo_h[val].confederacion<<endl;
}
//////////////////////////////////////////////////////////////////////
