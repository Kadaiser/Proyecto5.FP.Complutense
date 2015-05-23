#ifndef CORREO_H
#define CORREO_H

#include "fecha.h"

using namespace std;
const string CENTINELACORREO= "XXX";
const string CENTINELACUERPO= "X";

typedef struct{
string emisor;
string destinatario;
string asunto;
string cuerpo;
tFecha fecha;
string identificador;
} tCorreo;

/**
* Recibe un identificador de emisor y devuelve un correo con todos sus datos rellenos
*/
void correoNuevo(tCorreo &correo, string emisor);

/**
* Recibe un identificador de emisor y el correo original que se va a contestar, y devuelve un correo con todos sus datos rellenos
*/
void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor);

/**
* Devuelve un string con el contenido completo del correo para poderlo mostrar por consola,

*/
string aCadena(const tCorreo &correo);

/**
* Devuelve un string que contiene la información que se mostrará en la bandeja de entrada/salida: emisor, asunto y fecha sin hora
*/
string obtenerCabecera(const tCorreo &correo);

/**
* Dado un flujo de archivo de entrada (ya abierto), lee los datos que corresponden a un correo y lo devuelve. Devuelve false sólo si el correo cargado no es válido.
*/
bool cargar(tCorreo &correo, ifstream& archivo);

/**
* Dado un flujo de archivo de salida (ya abierto), escribe en el flujo los datos que corresponden a un correo
*/
void guardar(const tCorreo &correo, ofstream& archivo);

/**
* Genera el cuerpo del correo a partir de un flujo de entrada (ya abierto), escribe almacenandolo en una variable tipo string
*/
void leerCuerpo(string& cuerpo, ifstream& archivo);

/**
* Recibe una variable tipo string para solicitar al usuario rellenarla a traves de la consola, compone el campo destinatario de un correo.
* Solicitara en una primera fase el primer destinatario 
*/
void correoDestino(string& destinatario);

/**
* Recibe una variable tipo string para solicitar al usuario rellenarla a traves de la consola, compone el campo asunto de un correo.
*/
void correoAsunto(string& asunto);
/**
* Solicita al usuario recursivamente lineas de texo hasta que una linea solo con el centinel "XXX", despues lo construlle todo en una unica variable tipo string.
*/
void correoCuerpo(string& cuerpo);

/**
* Funcion que recibe dos correos y devuelve true, si el primer correo es mayor que el segundo
* Se considera mayor un correo que otro si en caso de se tener el mismo asunto (no se tiene en cuenta que un asunto empiece por "Re: ")
* se ordenan por fecha de creacion.
*/
bool operator< (const tCorreo & correo1, const tCorreo & correo2);

/**
* Funcion que recibe u correo elimina la concatenacion "Re: " del asunto en caso de que lo hubiere 
*/
void quitarRe(tCorreo & correo);

#endif
