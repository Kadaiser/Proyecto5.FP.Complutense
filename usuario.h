#ifndef USUARIO_H
#define USUARIO_H

using namespace std;

const string CENTINELA= "XXX";

#include "listaRegistros.h"

typedef struct{
string identificador;
string contrasenia;
tListaRegistros bandejaEntrada;
tListaRegistros bandejaSalida;
}tUsuario;


typedef tUsuario *tUsuarioPtr = new tUsuario; //puntero a un usuario

/**
* Dado un flujo de archivo (ya abierto), se carga un usuario de fichero
*/
bool cargar(tUsuario& usuario, ifstream& archivo);

/**
* Dado un flujo de archivo (ya abierto), se guarda un usuario en fichero
*/
void guardar(const tUsuario& usuario, ofstream& archivo);

/**
* Recibe un identificador de usuario y una contrase�a y los asigna al usuario.
*/
void inicializar(tUsuario& usuario, string id, string contrasenia);

/**
* Recibe una contrase�a y un usuario y devuelve si la contrase�a es correcta o no.
*/
bool validarContrasenia(const tUsuario &usuario, string contrasenia);


#endif