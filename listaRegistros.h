#ifndef LISTAREGISTRO_H
#define LISTAREGISTRO_H

using namespace std;

const int REGISTROS_INICIAL = 2;

typedef struct{
	string identificador;
	bool leido;
}tRegistro;


typedef struct{
	tRegistro* registros;//Array dinamico
	int contador;
	int capacidad;
}tListaRegistros;

//tListaRegistrosPtr punteroLR = &registros; WhereTF goes this?


/**
* Inicializa la lista
*/
void inicializar(tListaRegistros& listaRegistros, int capInicial);

/**
* Dado un flujo de archivo de entrada (ya abierto),
* lee los datos que corresponden a una lista de registros y la devuelve.
*/
void cargar(tListaRegistros &listaRegistros, ifstream& archivo);

/**
* Dado un flujo de archivo de salida (ya abierto), guarda los datos de la lista de registro.
*/
void guardar(const tListaRegistros &listaRegistros, ofstream& archivo);

/**
* Dado un registro lo inserta al final de la lista. Si la lista est� llena devuelve false,
* en otro caso devuelve true. Este subprograma se ejecutar� cuando un usuario env�e un correo
* ya que se insertar� el registro correspondiente en la lista de registros que representa su bandeja de salida,
* y tambi�n en las listas de registros que representan las bandejas de entrada de cada uno de los destinatarios del correo
*/
void insertar(tListaRegistros &listaRegistros, tRegistro registro);

/**
* Dado un identificador de correo, busca el registro correspondiente y si lo encuentra lo elimina de la lista (�sin dejar huecos!).
* Si no lo encuentra, devuelve false, en otro caso devuelve true. Este subprograma representa la acci�n de un usuario del borrado de un determinado correo de una de sus bandejas.
* OJO: esta operaci�n s�lo supone que el registro es borrado de la lista de registros, pero el correo seguir� existiendo en la lista de correos.
*/
bool borrar(tListaRegistros &listaRegistros, string id);

/**
* Dado un identificador de correo, busca el correspondiente registro y pone el indicador de le�do a true. La operaci�n devuelve un booleano indicando si se encontr� o no el registro.
*/
bool correoLeido(tListaRegistros &listaRegistros, string id);

/**
* Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posici�n, y si no existe devuelve -1.
*/
int buscar(const tListaRegistros &listaRegistros, string id);

/**
*  Dado un flujo de archivo de entrada (ya abierto),  cargar los datos en la estrucutra de un registro
*/
void cargarRegistro(tRegistro& registro, ifstream& archivo);

/**
* Recibe una lista de registros redimensionando (siempre al alza) el tamaño limite del array dinamico.
*/
void redimensionar (tListaRegistros &listaRegistros);

/**
*	Funcion que elimina los punteros asignados por el SGDM de la lista de registros.
*/
void destruir(tListaRegistros &listaRegistros);

#endif
