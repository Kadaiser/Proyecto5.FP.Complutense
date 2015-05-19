#ifndef LISTAREGISTRO_H
#define LISTAREGISTRO_H

using namespace std;

const int MAXREGISTROS = 100;

typedef struct{
string identificador;
bool leido;
}tRegistro;

typedef struct{
tRegistro registro[MAXREGISTROS];
int contador;
}tListaRegistros;

/**
* Inicializa la lista
*/
void inicializar(tListaRegistros &registros);

/**
* Dado un flujo de archivo de entrada (ya abierto), 
* lee los datos que corresponden a una lista de registros y la devuelve.
*/
void cargar(tListaRegistros &registros, ifstream& archivo);

/**
* Dado un flujo de archivo de salida (ya abierto), guarda los datos de la lista de registro.
*/
void guardar(const tListaRegistros &registros, ofstream& archivo);

/**
* Dado un registro lo inserta al final de la lista. Si la lista está llena devuelve false, 
* en otro caso devuelve true. Este subprograma se ejecutará cuando un usuario envíe un correo 
* ya que se insertará el registro correspondiente en la lista de registros que representa su bandeja de salida,
* y también en las listas de registros que representan las bandejas de entrada de cada uno de los destinatarios del correo
*/
bool insertar(tListaRegistros &registros, tRegistro registro);

/**
* Dado un identificador de correo, busca el registro correspondiente y si lo encuentra lo elimina de la lista (¡sin dejar huecos!). 
* Si no lo encuentra, devuelve false, en otro caso devuelve true. Este subprograma representa la acción de un usuario del borrado de un determinado correo de una de sus bandejas.
* OJO: esta operación sólo supone que el registro es borrado de la lista de registros, pero el correo seguirá existiendo en la lista de correos.
*/
bool borrar(tListaRegistros &registros, string id);

/**
* Dado un identificador de correo, busca el correspondiente registro y pone el indicador de leído a true. La operación devuelve un booleano indicando si se encontró o no el registro.
*/
bool correoLeido(tListaRegistros &registros, string id);

/**
* Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posición, y si no existe devuelve -1.
*/
int buscar(const tListaRegistros &registros, string id);

/**
*  Dado un flujo de archivo de entrada (ya abierto),  cargar los datos en la estrucutra de un registro
*/
void cargarRegistro(tRegistro& registro, ifstream& archivo);
#endif