////////////////////Ordenamiento con arbol/////////////////////
#include <iostream>

using namespace std;
//////////////////////////////////////////////////////////////
struct NodoArbol{											//Formato del cada nodo del arbol 
	struct NodoArbol *ptrIzq;
	int equipo;
	int goles;
	struct NodoArbol *ptrDer; 
};

struct formato{												//Formato de datos leido del archivo
	int id_gol,cod_equipo,fecha;
	char nombre_jugador[20];
	int id_partido;
};

struct paises{												//Struct para el listado auxiliar de los paises participantes
	char pais[20];
};

paises lista_paises[32]={"Rusia","Uruguay","Iran","Portugal","España","Francia","Australia","Argentina","Islandia",
						"Dinamarca","Croacia","Serbia","Mexico","Brasil","Suiza","Suecia","Belgica","Tunez","Inglaterra","Colombia",
						"Japon","Polinia","Senegal","Egipto","Nigeria","Corea","Alemania","Panama","Arabia_Saudita","Marruecos","Peru",
						"Costa_Rica"};													
															//Listado de paises para mostrar en pantalla el correspondiente a los goles marcados
typedef NodoArbol *ptrNodoArbol; 							//Crear el arbol
ptrNodoArbol ptrRaiz=NULL;									//Inicializar raiz del arbol en NULL
///////////////////////////Prototipos///////////////////////////////
void insertarNodo(NodoArbol*&,int,int);
void cargo_arbol();
void inOrden(ptrNodoArbol);
////////////////////////////////////////////////////////////////////
int main() 
{
	cout<<"RUSIA 2018 FIFA WORLD CUP, listado de goles por equipo durante el torneo: "<<endl;
	cargo_arbol();											//Funcion que lee el archivo, carga el arbol e imprime en pantalla el resultado: una lista ordenada de los goles por paises
	return 0;
}
////////////////////////////////////////////////////////////////////
void cargo_arbol()
{
	int conta_equipo=0;											
	FILE* archivo_f;												
	formato auxiliar[1];									//Vector auxiliar para lectura de datos
	int listado[32]={0};									//Vector auxiliar para guardar cantidad de goles, debido al formato del archivo (un gol por cada linea leida del mismo, para el equipo que se encuentra en ella)
	archivo_f=fopen("archivo.dat","rb");					//Abrir el archivo, solo para lectura de los datos
	while(!feof(archivo_f))									//Mientras no sea fin de archivo...
	{
		fread(&auxiliar[0],sizeof(formato),1,archivo_f);	//Leer una linea del archivo
		conta_equipo=auxiliar[0].cod_equipo;				//Guardar numero de equipo para linea del archivo leida
		listado[conta_equipo-1]++;							//Incrementar cantidad de gol para el equipo que corresponde (codigo de equipo coincide con el subindice del vector)
	}
	for(int aux=0;aux<32;aux++)								//Bucle para recorrer el vector con los goles guardados
	{	
		insertarNodo(ptrRaiz,aux,listado[aux]);				//Insertar nodo en el arbol con los datos correspondientes a cada equipo
	}
	inOrden(ptrRaiz);										//Mostrar los datos cargados en el arbol inOrden
}
/////////////////////////////////////////////////////////////////////////
void inOrden(ptrNodoArbol ptrArbol)							//Funcion para recorrer arbol, criterio inOrden
{
	if (ptrArbol != NULL) 									//Recorrer el árbol si no está vacío
	{				
		inOrden(ptrArbol->ptrIzq); 							//Avanzar por la rama izquierda hasta agotarla
		cout<<"El equipo "<<lista_paises[ptrArbol->equipo].pais<<" hizo: "<<ptrArbol->goles<<" goles."<<endl;		//Mostrar datos del listado (con formato para su visializacion amigable)
		inOrden(ptrArbol->ptrDer);							//Recorrer la rama derecha
	}
}
//////////////////////////////////////////////////////////////////////////
void insertarNodo(NodoArbol*& ptrArbol,int equipo, int cantgol)			//Funcion recursiva, para insertar nodos en el arbol
{
	if(ptrArbol==NULL)								//Si el arbol esta vacio...				
	{
		NodoArbol*aux=new NodoArbol();				//Crear nuevo nodo
		aux->goles=cantgol;							//Insertar los datos de goles y equipo en el nodo
		aux->equipo=equipo;
		aux->ptrIzq=NULL;							//Crear punteros de izquierda y derecha e inicializar en null
		aux->ptrDer=NULL;	
		ptrArbol=aux;
	}
	else											//En cambio, si el arbol no esta vacio...
	{
		if(cantgol<ptrArbol->goles)					//Verificar si el dato es menor que el nodo actual, de serlo...
		{
			insertarNodo(ptrArbol->ptrIzq,equipo,cantgol);		//Avanzar y cargar en la rama izquierda
		}
		else if(cantgol>=ptrArbol->goles)			//Si la cantidad de goles es mayor o igual a los goles del nodo actual...
		{
			insertarNodo(ptrArbol->ptrDer,equipo,cantgol);		//Avanzar e insertar por la derecha
		}
		else
		{
			cout<<"VALOR INVALIDO"<<endl;			//Linea de error en caso de que no se cumpla ninguna de las condiciones anteriores
		}	
	}
}
////////////////////////////////////////////////////////////
