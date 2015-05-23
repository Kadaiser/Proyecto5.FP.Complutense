#ifndef LISTACORREOS_H
#define LISTACORREOS_H

using namespace std;

#include "correo.h"

const string ficheroCorreos = "ListaCorreo.txt";
const int MAXCORREOS = 100;

//typedef tCorreoPtr tArrayCorreoPtr [MAXCORREOS];
typedef struct{
	//tCorreo correo[MAXCORREOS];
	//tArrayCorreoPtr correos;
	tCorreo* correos = new tCorreo[10]; //array dinamicos
	int contador;
	int capacidad; //indica la capacidad reservada en memoria del ultimo new
} tListaCorreos;


/**
Creacion de array
hay dos contextos:
CARGA DE FICHEROS
void inicializar;
*/

/**
*  Inicializa la lista
*/
void inicializar(tListaCorreos &listaCorreos, int capacidadInicial);

/**
* Implementa la carga de la lista de correos desde el fichero de correos de nombre <NombreDominio>_correos.txt.
*/
bool cargar(tListaCorreos &listaCorreos, string dominio);

/**
* Implementa el guardado de la lista de correos en el fichero de correos de nombre <NombreDominio>_ correos.txt 
* Guarda en fichero la lista de correos. El nombre del fichero será como en el subprograma anterior
*/
void guardar(const tListaCorreos &listaCorreos, string dominio); 

/**
* Dado un correo, si hay espacio en la lista, lo coloca en la posición de la lista que le corresponda 
* de acuerdo con su identificador y devuelve true. Si no lo ha podido colocar devuelve false
*/
bool insertar(tListaCorreos &listaCorreos, const tCorreo &correo);

/**
* Dado un identificador de correo, busca el correo correspondiente y si lo encuentra lo elimina de la lista. 
* Si no lo encuentra, devuelve false, en otro caso devuelve true. 
*/
bool borrar(tListaCorreos &listaCorreos, string id);

/**
* Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true, 
* y si no existe en la lista, la posición que le correspondería y el valor false.
*/
bool buscar(const tListaCorreos &listaCorreos, string id, int &pos);

/**
* Dada una lista de correos la devuelve ordenada por asunto y fecha. 
* Como es una clave de ordenación doble, habrá que redefinir el operador de comparación en el módulo que corresponda.
*/
void ordenar_AF(tListaCorreos &listaCorreos);

#endif
