//////////////////Programa para grabar archivo///////////////////////
#include <iostream>
#include <cstring>
using namespace std;

////////////////////////////////////////////////////////////////////
struct formato{									//Formato del archivo a grabar 
	int id_gol,cod_equipo,fecha;
	char nombre_jugador[20];
	int id_partido;
};

formato listado[169]={							//Listado de goles del mundial
		{1,1,20180614,"Gazinsky",1},			//Codigo equipo de Rusia = 1
		{2,1,20180614,"Cheryshev",1},
		{3,1,20180614,"Dzyuba",1},
		{4,1,20180614,"Cheryshev",1},
		{5,1,20180614,"Golovin",1},
		{6,2,20180615,"Gimenez",2},				//Codigo equipo de Uruguay = 2
		{7,3,20180615,"Bouhaddouz",3},			//Cogigo equipo de Iran = 3
		{8,4,20180615,"Ronaldo",4},				//Codigo equipo Portugal = 4
		{9,4,20180615,"Ronaldo",4},
		{10,4,20180615,"Ronaldo",4},
		{11,5,20180615,"Costa",4},				//Codigo equipo España = 5
		{12,5,20180615,"Costa",4},
		{13,5,20180615,"Nacho",4},
		{14,6,20180616,"Griezmann",5},			//Codigo equipo Francia = 6
		{15,6,20180616,"Benich",5},
		{16,7,20180616,"Jedinak",5},			//Codigo equipo Australia = 7
		{17,8,20180616,"Aguero",6},				//Codigo equipo Argentina =8
		{18,9,20180616,"Finnbogason",6},		//Codigo equipo Islandia = 9
		{19,10,20180616,"Poulsen",7},			//Codigo equipo Dinamarca = 10
		{20,11,20180616,"Etebo",8},				//Codigo equipo Croacia = 11	
		{21,11,20180616,"Modric",8},
		{22,12,20180617,"Kolarov",9},			//Codigo equipo Serbia = 12
		{23,13,20180617,"Lozano",10},			//Codigo equipo Mexico = 13
		{24,14,20180617,"Coutinho",11},			//Codigo equipo Brasil = 14
		{25,15,20180617,"Zuber",11},			//Codigo equipo Suiza = 15
		{26,16,20180618,"Granqvist",12},		//Codigo quipo Suecia = 16
		{27,17,20180618,"Mertens",13},			//Codigo equipo Belgica = 17
		{28,17,20180618,"Lukaku",13},
		{29,17,20180618,"Lukaku",13},
		{30,18,20180618,"Sassi",14},			//Codigo equipo Tunez  =18
		{31,19,20180618,"Kane",14},				//Codigo equipo Inglaterra = 19
		{32,19,20180618,"Kane",14},
		{33,20,20180619,"Quintero",15},			//Codigo equipo Colombia = 20
		{34,21,20180619,"Kagawa",15},			//Codigo equipo Japon = 21
		{35,21,20180619,"Osako",15},
		{36,22,20180619,"Krychowiak",16},		//Codigo equipo Polonia = 22
		{37,23,20180619,"Cionek",16},			//Codigo equipo Senegal = 23
		{38,23,20180619,"Niang",16},
		{39,1,20180619,"Fathi",17},
		{40,1,20180618,"Cheryshev",17},
		{41,1,20180619,"Dzyuba",17},
		{42,24,20180619,"Salah",17},			//Codigo equipo Egipto = 24
		{43,4,20180620,"Ronaldo",18},
		{45,2,20180620,"Suarez",19},
		{46,5,20180620,"Costa",20},
		{47,10,20180621,"Eriksen",21},
		{48,7,20180621,"Jedinak",21},
		{49,6,20180621,"Mbappe",22},
		{50,11,20180621,"Rebic",23},
		{51,11,20180621,"Modric",23},
		{52,11,20180621,"Rakitic",23},
		{53,14,20180622,"Coutinho",24},
		{54,14,20180622,"Neymar",24},
		{55,25,20180622,"Musa",25},				//Codigo equipo Nigeria = 25
		{56,25,20180622,"Musa",25},
		{57,12,20180622,"Mitrovic",26},
		{58,15,20180622,"Xhaka",26},
		{59,15,20180622,"Shaqiri",26},
		{60,17,20180623,"Hazard",27},
		{61,17,20180623,"Lukaku",27},
		{62,17,20180623,"Lukaku",27},
		{63,17,20180623,"Hazard",27},
		{64,17,20180623,"Batshuayi",27},
		{65,18,20180623,"Bronn",27},
		{66,18,20180623,"Khazri",27},
		{67,13,20180623,"Vela",28},
		{68,13,20180623,"Hernandez",28},
		{69,26,20180623,"Son",28},				//Codigo equipo Corea = 26
		{70,27,20180623,"Reus",29},				//Codigo equipo Alemania = 27
		{71,27,20180623,"Kroos",29},
		{72,16,20180623,"Toivonen",29},
		{73,19,20180624,"Stones",30},
		{74,19,20180624,"Kane",30},
		{75,19,20180624,"Lingard",30},
		{76,19,20180624,"Stones",30},
		{77,19,20180624,"Kane",30},
		{78,19,20180624,"Kane",30},
		{79,28,20180624,"Baloy",30},			//Codigo equipo Panama = 28
		{80,21,20180624,"Inui",31},
		{81,21,20180624,"Honda",31},
		{82,23,20180624,"Mane",31},
		{83,23,20180624,"Wague",31},
		{84,20,20180624,"Mina",32},
		{85,20,20180624,"Falcao",32},
		{86,20,20180624,"Cuadrado",32},
		{87,2,20180625,"Suarez",33},
		{88,1,20180625,"Cheryshev",33},
		{89,24,20180625,"Salah",34},
		{90,29,20180625,"Alfaraj",34},			//Codigo equipo Arabia Saudita= 29
		{91,29,20180625,"Aldawsari",34},
		{92,5,20180625,"Isco",35},
		{93,5,20180625,"Aspas",35},
		{94,30,20180625,"Boutaib",35},			//Codigo equipo Marruecos = 30
		{95,30,20180625,"Nesyri",35},
		{96,3,20180625,"Ansarifard",36},
		{97,4,20180625,"Quaresma",36},
		{98,31,20180626,"Carillo",37},			//Codigo equipo Peru = 31
		{99,31,20180626,"Guerrero",37},
		{100,8,20180626,"Messi",39},
		{101,8,20180626,"Rojo",39},
		{102,25,20180626,"Moses",39},
		{103,9,20180626,"Sigurdsson",40},
		{104,11,20180626,"Badelj",40},
		{105,11,20180626,"Perisic",40},
		{106,26,20180627,"Kim",41},
		{107,26,20180627,"Son",41},
		{108,16,20180627,"Augustinsson",42},
		{109,16,20180627,"Granqvist",42},
		{110,16,20180627,"Alvarez",42},
		{111,14,20180627,"Paulinho",43},
		{112,14,20180627,"Silva",43},
		{113,15,20180627,"Dzemaili",44},
		{114,15,20180627,"Drmic",44},
		{115,32,20180627,"Waston",44},			//Codigo equipo Costa Rica = 32
		{116,32,20180627,"Sommer",44},
		{117,22,20180628,"Bednarek",45},
		{118,20,20180628,"Mina",46},
		{119,18,20180628,"Youssef",47},
		{120,18,20180628,"Khazri",47},
		{121,28,20180628,"Meriah",47},
		{122,17,20180628,"Januzaj",48},
		{123,6,20180630,"Griezmann",49},
		{124,6,20180630,"Pavard",49},
		{125,6,20180630,"Mbappe",49},
		{126,6,20180630,"Mbappe",49},
		{127,8,20180630,"Di maria",49},
		{128,8,20180630,"Mercado",49},
		{129,8,20180630,"Aguero",49},
		{130,2,20180630,"Cavani",50},
		{131,2,20180630,"Cavani",50},
		{132,4,20180630,"Pepe",50},
		{133,4,20180701,"Ignashevich",51},
		{134,1,20180701,"Dzyuba",51},
		{135,11,20180701,"Mandzukic",52},
		{136,10,20180701,"Jorgensen",52},
		{137,14,20180702,"Neymar",53},
		{138,14,20180702,"Firmino",53},
		{139,17,20180702,"Vertonghen",54},
		{140,17,20180702,"Fellaini",54},
		{141,17,20180702,"Chadli",54},
		{142,21,20180702,"Haraguchi",54},
		{143,21,20180702,"Inui",54},
		{144,16,20180703,"Forsberg",55},
		{145,20,20180703,"Mina",56},
		{146,19,20180703,"Kane",56},
		{147,6,20180706,"Varane",57},
		{148,6,20180706,"Griezmann",57},
		{149,14,20180706,"Augusto",58},
		{150,17,20180706,"Fernandinho",58},
		{151,17,20180706,"De Bruyne",58},
		{152,19,20180707,"Maguire",59},
		{153,19,20180707,"Alli",59},
		{154,1,20180707,"Cheryshev",60},
		{155,1,20180707,"Fernandes",60},
		{156,11,20180707,"Kramaric",60},
		{157,11,20180707,"Vida",60},
		{158,6,20180710,"Umtiti",61},
		{159,11,20180711,"Perisic",62},
		{160,11,20180711,"Mandzukic",62},
		{161,19,20180711,"Trippier",62},
		{162,17,20180714,"Meunier",63},
		{163,17,20180714,"Hazard",63},
		{164,6,20180715,"Mandzukic",64},
		{165,6,20180715,"Griezmann",64},
		{166,6,20180715,"Pogba",64},
		{167,6,20180715,"Mbappe",64},
		{168,11,20180715,"Perisic",64},
		{169,11,20180715,"Mandzukic",64},
		};

struct nodo{										//Formato nodo de lista para generar orden
	formato campo1;
	nodo* sgte;
};

struct fechas{										//Campo de datos dentro del nodo de la lista
	char jugador_fecha[20];
	int goles=0;
	int fecha=0;
};
/////////////////////////////////////////////////////////
void generar_listado();
void insertar_ordenado(nodo*&,int,int,int,int,char[]);
void escribir_archivo(nodo*&,FILE*&);
/////////////////////////////////////////////////////////
int main()
{
	cout<<"EL PRESENTE PROGRAMA REALIZA UN ARCHIVO ORDENADO DE LOS RESULTADOS DEL MUNDIAL RUSIA 2018 DE LA FIFA"<<endl;
	generar_listado();																//LLamado a la funcion que realiza el volcado de datos en el archivo
	return 0;
}
/////////////////////////////////////////////////////////
void generar_listado()
{
	FILE* archivo_salida;
	archivo_salida=fopen("archivo.dat","wb+");										//Abrir el archivo de salida para los datos
	nodo* lista=NULL;																//Inicializar la lista en NULL
	for(int rec=0;rec<168;rec++)													//Recorrer los datos a grabar en el archivo, que corresponden a los goles del mundial Rusia 2018
	{
		insertar_ordenado(lista,listado[rec].id_gol,listado[rec].cod_equipo,listado[rec].id_partido,listado[rec].fecha,listado[rec].nombre_jugador);	//Ejecutar funcion instertar ordenado para asi generar el orden del archivo solicitado
	}
	escribir_archivo(lista,archivo_salida);											//Escribir los datos ordenados de la lista en el archivo de salida
}
/////////////////////////////////////////////////////
void insertar_ordenado(nodo*& lista,int ingreso_gol,int ingreso_equipo,int ingreso_id_partido,int ingreso_fecha,char ingreso_nombre_jug[])
{																					//Funcion que inserta bajo 2 criterios de ordenamiento en la lista, esta ultima pasada por referencia
	nodo *p= new nodo();															//Crear un nuevo nodo
	p->campo1.id_gol=ingreso_gol;													//Guardo los datos pasados por parametro en el nuevo nodo de la lista
	p->campo1.cod_equipo=ingreso_equipo;											//Los goles, el nombre del jugador, el codigo de equipo
	strcpy(p->campo1.nombre_jugador,ingreso_nombre_jug);							//la fecha e id del partido
	p->campo1.id_partido=ingreso_id_partido;
	p->campo1.fecha=ingreso_fecha;
	if(lista==NULL || ingreso_equipo<lista->campo1.cod_equipo)						//Si es comienzo de lista o el codigo de equipo es menor al ultimo nodo de la lista...
	{	
		p->sgte=lista;																//Agrego el nuevo nodo a la lista contiguamente 
		lista=p;
		return;																		//Se utiliza el return como si fuera un else...
	}
	nodo* q=lista;																	
	while(q->sgte!=NULL && (ingreso_equipo>q->sgte->campo1.cod_equipo || (ingreso_equipo==q->sgte->campo1.cod_equipo && ingreso_fecha>q->sgte->campo1.fecha)))	q=q->sgte;
	p->sgte=q->sgte;																//Recorro la lista para ver donde insertar el nodo, compara nuevamente el codigo de equipo, y en caso de repeticion compara con la fecha...
	q->sgte=p;																		//e inserta el nodo donde corresponda
	return;						
}
////////////////////////////////////////////////////////
void escribir_archivo(nodo*& datos,FILE*& archivo)			//Fucion que graba el archivo la lista deseada, ambos pasados por referencia
{
	nodo* p= new nodo();									//Creo nuevo nodo para sacar los datos de la lista
	p=datos;												//Copio la lista en el nuevo nodo 
	while((p!=NULL))										//Mientras haya datos en la lista...
	{
		cout<<p->campo1.cod_equipo<<" "<<p->campo1.fecha<<" "<<p->campo1.id_gol<<" "<<p->campo1.id_partido<<endl;		//Muestro el contenido a grabar en el arhivo
		fwrite(&p->campo1,sizeof(formato),1,archivo);																	//Escribo el archivo de salida
		p=p->sgte;																										//Avanzo en la lista hasta terminarla (debido al bucle)
	}
	fflush(archivo);										//Vacio el buffer para finalizar el guardado en el archivo
}
////////////////////////////////////////////////////////
