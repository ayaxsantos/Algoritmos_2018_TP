////////////////////////Programa ordenamiento/////////////////////////
#include <iostream>
#include <cstring>
using namespace std;

////////////////////////Estructuras archivo//////////////////////////
struct formato{												 //Formato leido del archivo con los datos necesarios
	int id_gol,cod_equipo,fecha;
	char nombre_jugador[20];
	int id_partido;
};

//////////////////////Estructuras auxiliares/////////////////////////
struct fechas{												//Formato auxiliar con los datos de salida solicitados, para los diferentes
	char jugador_fecha[20];									//criterios de ordenamiento
	char equipo[20];
	int goles;
	int fecha;
};

struct paises{												//Estructura para listado de paises, el cual posee asociada la clave posicional
	char pais[20];											//al codigo de equipo
};

paises lista_paises[32]={"Rusia","Uruguay","Iran","Portugal","España","Francia","Australia","Argentina","Islandia",
						"Dinamarca","Croacia","Serbia","Mexico","Brasil","Suiza","Suecia","Belgica","Tunez","Inglaterra","Colombia",
						"Japon","Polinia","Senegal","Egipto","Nigeria","Corea","Alemania","Panama","Arabia_Saudita","Marruecos","Peru",
						"Costa_Rica"};						//Listado de paises auxiliar
///////////////////////////Parte matriz////////////////////////////
struct nodo_b{												//Nodo de la lista, la cual su puntero de inicio se encontrara en la matriz						
	char jugador[20];		
	int fecha,goles;
	nodo_b* sgte;
};

struct fmt_matriz{											//Formato de la matriz, donde cada posicion es un puntero a una lista enlazada
	nodo_b* lista=NULL;
};

fmt_matriz mat[32][7];										//Declaracion de la matriz, junto con su tamaño correspondiente (32x7) (equipos x partidos)
fechas global[25];											//Declaracion de vector auxiliar para ordenamiento goles por fecha
fechas auxiliar[25]={										//Vector auxiliar de fechas, para el ordenamiento goles por fecha (clave de acceso, seria la fecha)
					 {"0","0",0,20180614},
					 {"0","0",0,20180615},
					 {"0","0",0,20180616},
					 {"0","0",0,20180617},
					 {"0","0",0,20180618},
					 {"0","0",0,20180619},
					 {"0","0",0,20180620},
					 {"0","0",0,20180621},
					 {"0","0",0,20180622},
					 {"0","0",0,20180623},
					 {"0","0",0,20180624},
					 {"0","0",0,20180625},
					 {"0","0",0,20180626},
					 {"0","0",0,20180627},
					 {"0","0",0,20180628},
					 {"0","0",0,20180630},
					 {"0","0",0,20180701},
					 {"0","0",0,20180702},
					 {"0","0",0,20180703},
					 {"0","0",0,20180706},
					 {"0","0",0,20180707},
					 {"0","0",0,20180710},
					 {"0","0",0,20180711},
					 {"0","0",0,20180714},
					 {"0","0",0,20180715},  
					};
//////////////////////////Prototipos/////////////////////////////
void procesamiento_archivo(int);
void corte_control(FILE*&,fmt_matriz[][7]);
bool buscar_datos(FILE*&);
void cargar_datos(FILE*&,nodo_b*&,int&,int&);
nodo_b* insertar_lista(nodo_b*&,char[],int,int&);
nodo_b* pop(nodo_b*&,int,int&,char[]);
nodo_b* buscar(nodo_b*, char[],int&);
nodo_b* insertar_s_clave(nodo_b*&,char[],int,int&);
void goles_por_equipo(fmt_matriz[][7]);
void goles_por_fecha(fmt_matriz[][7]);
void goles_mundial(fmt_matriz[][7]);
void metodo_burbuja(fechas[]);
int verificar_repeticion(fechas[],char[]);
////////////////////////////////////////////////////////////////
int main() 
{
	int selec=0;												//Variable de seleccion en el menu de usuario (colocado para demostracion)
	cout<<"Bienvenido a listados de goleadores de RUSIA 2018 FIFA WORLD CUP..."<<endl;
	cout<<"Seleccione que lista desea visualizar: \n 1 - Listado de goleadores por equipo \n 2 - Listado de goleadores por fecha \n 3 - Listado de goleadores del mundial"<<endl;
	cin>>selec;													//Lectura del valor ingresado por el usuario correspondiente al menu 
	procesamiento_archivo(selec);								//Invocacion a la funcion que realiza la lectura y procesado del archivo
	return 0;
}
////////////////////////////////////////////////////////////////
void procesamiento_archivo(int selec)							
{
	FILE* archivo_salida;										//Crear archivo y asociar nombre
	archivo_salida=fopen("archivo.dat","rb");					//Abrir archivo en formato de lectura
	corte_control(archivo_salida,mat);							//Invocacion a la funcion para leer archivo y volcar datos en la matriz
	if(selec==1)		goles_por_equipo(mat);					//Si seleccion es 1, invocar funcion que ordena goles por cada equipo
	else if (selec==2)	goles_por_fecha(mat);					//Si es 2, invocar funcion que ordena los goles por cada fecha
	else if (selec==3)	goles_mundial(mat);						//Y si es 3, se invoca la funcion de goles durante todo el torneo
	else return; 												//Si no es ninguna, retornar al main para finalizar ejecucion del programa
}
////////////////////////////////////////////////////////////////
void corte_control(FILE*& archivo_salida,fmt_matriz mat[][7])	//Funcion que inserta en la lista realizando un corte de control. Recibe el archivo y la matriz
{
	int equip=0,fech=0,control=0,control_2;						//Variables de control y posiciones de la matriz
	int goles=0;												//Variable contadora de goles								
	formato listado_aux[1];										//Vector uuxiliar de una posicion para la lectura de datos desde el archivo
	fseek(archivo_salida,0,SEEK_SET);							//Posicionar al comienzo del archivo
	fread(listado_aux,sizeof(formato),1,archivo_salida);		//Realizar lectura
	while(!feof(archivo_salida))								//Mientras no sea fin de archivo...
	{
		control=listado_aux[0].cod_equipo;										//Guardo valor anterior del codigo de equipo en control, para la secuencia del bucle
		while(!feof(archivo_salida) && (listado_aux[0].cod_equipo==control))	//Mientras sea del mismo equipo...
		{
			control_2=listado_aux[0].fecha;										//Guardo fecha anterior en control_2, para que el corte de control continue
			while(!feof(archivo_salida) && (listado_aux[0].cod_equipo==control) && (listado_aux[0].fecha==control_2))	//Mientras sean del mismo equuipo y la misma fecha...
			{ 			
				goles++;
				insertar_s_clave(mat[equip][fech].lista,listado_aux[0].nombre_jugador,listado_aux[0].fecha,goles);		//Inserto en la lista correspondiente al puntero en la matriz en la posicion del equipo y fecha
				fread(listado_aux,sizeof(formato),1,archivo_salida); 													//Leo siguiente valor del archivo
				goles=0;																								//Reestablecer contador de goles
			}
			fech++;												//Incrementar contador de fecha para avanzar en el posicionamiento de la matriz
		}
		equip++;												//Incrementar contador de equipos para avanzar en el eje y de la matriz
		fech=0;													//Reestablecer el contador de fecha para comenzar de nuevo en la linea de equipo actual
	}
	return;
}	
////////////////////////////////////////////////////////////////
nodo_b* insertar_lista(nodo_b*& lista,char jugador[],int fecha, int& goles)		//Funcion que inserta en la lista de forma ordenada, recibe la lista por referencia y los datos: los goles tambien por referencia
{
	nodo_b *p=new nodo_b();										//Crear nuevo nodo de la lista
	p->fecha=fecha;												//Guardar fechas (la cual se recibe como parametro) en la lista
	p->goles=goles; 											//Asi como los goles y el nombre del jugador
	strcpy(p->jugador,jugador);
	if(lista==NULL || goles<lista->goles)						//Si la lista esta vacia o el valor del gol del nodo a ingresar es menor que el primer valor actual de la lista...
	{
		p->sgte=lista;											//Inserto al comienzo de la lista
		lista=p;												//Guardo la lista, los datos hasta este momento se encontraban en el nodo auxiliar creado al comienzo		
		return p;												//Fin de ejecucion de la funcion
	}
	nodo_b *q=lista;											//Si no se cumple el if anterior, creo un nuevo nodo y guardo una copia de la lista para recorrerla 
	while(q->sgte!=NULL && goles>q->sgte->goles)	q=q->sgte;	//Mientras no sea fin de lista (NULL) y los goles del nodo a insertar sean mayores al siguiente de la lista, avanzar en el recorrido
	p->sgte=q->sgte;											//Cuando deja de avanzar, inserta el nodo y guarda la lista
	q->sgte=p;
	return p;													//Fin de ejecucion de la funcion
}
////////////////////////////////////////////////////////////////	
nodo_b* buscar(nodo_b* lista, char criterio[],int& goles)		//Funcion que busca en la lista repeticiones del nombre de jugador (lo recibe en criterio, asi como la lista y a los goles por referencia)
{																
	while(lista!=NULL && (strcmp(criterio,lista->jugador)<=0))	//Mientras no sea fin de lista y el nombre del jugador sea menor o igual...
	{
		if(lista!=NULL && strcmp(criterio,lista->jugador)==0)	//Si no es fin de lisa y el nombre es igual
		{
			lista->goles++;										//Incrementa la cantidad de goles en el nodo correspondiente
			return lista;
		}
		lista=lista->sgte;										//Si no se cumple el if, continua avanzando para seguir la busqueda
	}	
	return NULL;												//Fin de ejecucion de la funcion
}
////////////////////////////////////////////////////////////////
nodo_b* insertar_s_clave(nodo_b*& lista, char jugador[],int fecha, int& goles)	//Funcion para insertar sin repetir la clave, (para evitar duplicados de jugadores en la lista), recibe la lista y los datos para el nodo
{
	nodo_b* p=buscar(lista,jugador,goles);										//Realiza la busqueda de coincidencia e incrementa goles en caso de repeticion en el jugador correspondiente
	if(p==NULL)	p=insertar_lista(lista,jugador,fecha,goles);					//Si la funcion no detecta coincidencia (valor de retorno NULL) inserta en la lista como un nodo nuevo	
}
////////////////////////////////////////////////////////////////
void goles_por_equipo(fmt_matriz mat[][7])						//Funcion que muestra en pantalla los goles por equipo, recibe como parametro la matriz
{
	int fecha=0,goles=0;										//Variables para el recorrido de la matriz
	char jugador[20];											//Variable auxiiliar para guardar y mostrar el jugador extraido de la lista
	for(int equip=0;equip<32;equip++)							//Recorrer la lista en el eje x...
	{	
		for(int part=0;part<7;part++)							//Y a su vez recorrer en el eje y por cada valor de x...
		{
			pop(mat[equip][part].lista,fecha,goles,jugador);	//Sacar los datos de la lista (esta funcion incrementa los goles con un contador, y los guarda en la variable goles pasada por referencia)
		}
		cout<<"El equipo "<<lista_paises[equip].pais<<" realizo: "<<goles<<" goles."<<endl;		//Mostrar la lista solicitada por cada equipo
		goles=0;																				//Reiniciar contador de goles por equipo
	}	
}
////////////////////////////////////////////////////////////////
nodo_b* pop(nodo_b*& lista,int fecha, int &goles, char jugador[])	//Funcion que recibe como parametros lista y datos: Goles por referencia. Esto ultimo ocurre
{																	//debido a que en lugar de procesar el dato en pop, se incrementa la cantidad de goles en el nodo correspondiente
	nodo_b* p= new nodo_b();									//Crear nuevo nodo llamado p
	p=lista;													//Guardar una copia de la lista en p
	while(p!=NULL)												//Mientras no sea fil de lista (NULL)
	{	
		goles+=p->goles;										//Incremento la cantidad de goles del nodo
		p=p->sgte;												//Y continuo avanzando en la lista
	}
	return p;													//Fin de ejecucion de la funcion
}
////////////////////////////////////////////////////////////////
void goles_por_fecha(fmt_matriz mat[][7])				//Funcion que muestra en pantalla los goles por fecha (en el caso de un solo gol, muestra uno solo de los goles en esa fecha)
{														
	int equip=0,fech=0;									//Variables para posicionamiento de la matriz
	int control_fecha=0;								//Variable para el control de la fecha										
	while(fech<7)										//La matriz se recorre en orden inverso, mientras la fecha (posicionamiento y) sea menor a 7...
	{
		while(equip<32)									//Mientras equipo (posicionamiento x) sea menor a 32...
		{
			while(mat[equip][fech].lista!=NULL)			//Mientras no sea final de lista (en el puntero a la lista almacenado en la posicion de la matriz)
			{
				control_fecha=mat[equip][fech].lista->fecha;												//Guardar valor anterior de fecha en control
				while(mat[equip][fech].lista!=NULL && mat[equip][fech].lista->fecha==control_fecha)			//Mientras no sea fin de lista y la fecha sea igual a la anterior...
				{	
					for(int rec=0;rec<25;rec++)																//Recorro listado de fechas auxiliar
					{
						if(auxiliar[rec].fecha==control_fecha && mat[equip][fech].lista->goles>auxiliar[rec].goles)		//Si el jugador actual hizo mas goles en la fecha que el anterior colocado en la lista
						{
							auxiliar[rec].goles=mat[equip][fech].lista->goles;											//Copio los datos del nodo (gol, fecha, jugador y pais) en el vector auxiliar de fechas
							auxiliar[rec].fecha=mat[equip][fech].lista->fecha;
							strcpy(auxiliar[rec].jugador_fecha,mat[equip][fech].lista->jugador);
							strcpy(auxiliar[rec].equipo,lista_paises[equip].pais);
						}
					}
					mat[equip][fech].lista=mat[equip][fech].lista->sgte;						//Avanzo en la lista actual
				}	
			}
			equip++;			//Incrementar equipo por cada posicion de la matriz leida	
		}
	fech++;						//Incrementar fecha por cada columna terminada de procesar
	equip=0;					//Y reinicio el contador de columnas (se reinicia el recorrido en el eje y)
	}
	for(int rec=0;rec<25;rec++)	cout<<"El jugador "<<auxiliar[rec].jugador_fecha<<" del equipo "<<auxiliar[rec].equipo<<" convirtio "<<auxiliar[rec].goles<<" goles."<<endl;
}	//Muestro la lista auxiliar con los datos y termina ejecuion de la funcion
////////////////////////////////////////////////////////////////
void goles_mundial(fmt_matriz mat[][7])						//Funcion que muestra los goles durante toda la competencia, ordenado de mayor a menor
{															//Recibe como parametro la matriz
	int recorrido=0,recorrido_aux=0,equip=0,fech=0;			//Variables de recorrido para la matriz y para el listado final
	fechas vector_general[120]={0};							//Listado final (de 120 posiciones, coincidente con la cantidad de goles hechos por cada jugador que logro convertir)
	while(equip<32)											//Mientras el contador del eje x sea menor a 32 (limite de la matriz)..
	{
		while(fech<7)										//Mientras el contador del eje y sea menor a 7...
		{
			while(mat[equip][fech].lista!=NULL)				//Y mientras no sea fin de lista...
			{
				recorrido=verificar_repeticion(vector_general,mat[equip][fech].lista->jugador);		//Verifico repeticion de jugadores en el listado final a mostrar (devuelve 0 si no hay, y en caso de haber la posicion donde encontro la repeticion)
				if(recorrido==0)																	//Si no se encuentran repeticiones
				{
					vector_general[recorrido_aux].goles=mat[equip][fech].lista->goles;				//Inserto los datos  de goles, fecha y jugador en el vector
					vector_general[recorrido_aux].fecha=mat[equip][fech].lista->fecha;
					strcpy(vector_general[recorrido_aux].equipo,lista_paises[equip].pais);
					strcpy(vector_general[recorrido_aux].jugador_fecha,mat[equip][fech].lista->jugador);
					recorrido_aux++;
				}
				else																			//Si hay repeticion...
				{
					vector_general[recorrido].goles+=mat[equip][fech].lista->goles;				//Incrementa la cantidad de goles en la posicion que se encuentra el jugador (donde encontro la repeticion)
				}
				mat[equip][fech].lista=mat[equip][fech].lista->sgte;							//Avanzo en la lectura de la lista
			}
			fech++;							//Incremento el contador del eje y para cuando termino la lista en la posicion actual
		}
	equip++;								//Incremento el contador del eje x
	fech=0;									//Reinicio contador del eje y
	}
	metodo_burbuja(vector_general);			//Invocacion a uncion que ordena listado y muestra el contenido
}
////////////////////////////////////////////////////////////////
void metodo_burbuja(fechas vector_p_ordenar[])			//Funcion que ordena el listado de goles en el torneo y muestra su resultado (metodo de burbuja)
{
	fechas vector_auxiliar[1];							//Vector auxiliar de una posicion para mover los datos durante el ordenamiento
	for(int rec1=0;rec1<120;rec1++)						//Bucle 1 
	{
		for(int rec2=0;rec2<119;rec2++)					//Bucle 2 (ambos para recorrer el vector y ordenar)
		{
			if(vector_p_ordenar[rec2].goles<vector_p_ordenar[rec2+1].goles)			//Si los goles en la posicion actual son menores que en la siguiente...
			{
				vector_auxiliar[0]=vector_p_ordenar[rec2];							//Intercambio los datos entre posiciones
				vector_p_ordenar[rec2]=vector_p_ordenar[rec2+1];
				vector_p_ordenar[rec2+1]=vector_auxiliar[0];
			}
		}
	}
	for(int rec=0;rec<120;rec++)	cout<<"El jugador: "<<vector_p_ordenar[rec].jugador_fecha<<" del equipo "<<vector_p_ordenar[rec].equipo<<" convirtio "<<vector_p_ordenar[rec].goles<<" goles."<<endl;
}																					//Muestro finalmente, el contenido ordenado del vector con la lista de goleeadores del mundial
////////////////////////////////////////////////////////////////
int verificar_repeticion(fechas vector_recorrer[],char buscado[])			//Funcion que recibe vector y caracter a buscar, evalua repeticiones en el vector recibido
{
	int rec=0;																//Variable auxiliar para el retorno
	for(int pos=0;pos<120;pos++)											//Recorro el vector (posicion ya conocida)
	{	
		if(strcmp(vector_recorrer[pos].jugador_fecha,buscado)==0)	rec=pos;		//Si encuentra repeticion, guarda la posicion donde la encontro
	}
	if(rec==0)	return rec;															//Si no encontro repeticion, retorna 0
	else if(rec!=0)	return rec;														//De lo contrario retorna el valor donde habia repeticion
}
////////////////////////////////////////////////////////////////
