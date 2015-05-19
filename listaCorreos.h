#ifndef LISTACORREOS_H
#define LISTACORREOS_H

using namespace std;

#include "correo.h"

const string ficheroCorreos = "ListaCorreo.txt";
const int MAXCORREOS = 100;

typedef struct{
	tCorreo correo[MAXCORREOS];
	int contador;
} tListaCorreos;



/**
*  Inicializa la lista
*/
void inicializar(tListaCorreos &correos);

/**
* Implementa la carga de la lista de correos desde el fichero de correos de nombre <NombreDominio>_correos.txt.
*/
bool cargar(tListaCorreos &correos, string dominio);

/**
* Implementa el guardado de la lista de correos en el fichero de correos de nombre <NombreDominio>_ correos.txt 
* Guarda en fichero la lista de correos. El nombre del fichero será como en el subprograma anterior
*/
void guardar(const tListaCorreos &correos, string dominio); 

/**
* Dado un correo, si hay espacio en la lista, lo coloca en la posición de la lista que le corresponda 
* de acuerdo con su identificador y devuelve true. Si no lo ha podido colocar devuelve false
*/
bool insertar(tListaCorreos &correos, const tCorreo &correo);

/**
* Dado un identificador de correo, busca el correo correspondiente y si lo encuentra lo elimina de la lista. 
* Si no lo encuentra, devuelve false, en otro caso devuelve true. 
*/
bool borrar(tListaCorreos &correos, string id);

/**
* Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true, 
* y si no existe en la lista, la posición que le correspondería y el valor false.
*/
bool buscar(const tListaCorreos &correos, string id, int &pos);

/**
* Dada una lista de correos la devuelve ordenada por asunto y fecha. 
* Como es una clave de ordenación doble, habrá que redefinir el operador de comparación en el módulo que corresponda.
*/
void ordenar_AF(tListaCorreos &correos);

#endif
