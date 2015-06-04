#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

using namespace std;

#include "usuario.h"

const string ficheroUsuarios = "Usuarios.txt";
const int MAXUSUARIOS = 3;


typedef tUsuario *tUsuarioPtr; //puntero a un usuario

typedef struct{
	tUsuarioPtr usuarios[MAXUSUARIOS];
	int contador;
}tListaUsuarios;

/**
* Inicializa la lista
*/
void inicializar(tListaUsuarios &listaUsuarios);

/**
* Implementa la carga de la lista de usuarios desde el fichero de usuarios
* de nombre <NombreDominio>_usuarios.txt .
*/
bool cargar(tListaUsuarios& listaUsuarios, string dominio);

/**
* Implementa el guardado de la lista de usuarios en el fichero de usuarios
* de nombre <NombreDominio>_usuarios.txt .
*/
void guardar(const tListaUsuarios& listaUsuarios, string dominio);

/**
* A�ade un usuario en la posici�n de la lista que le corresponde, si hay sitio para ello.
* Adem�s devuelve un booleano indicando si la operaci�n tuvo �xito o no.
*/
bool aniadir(tListaUsuarios& listaUsuarios, const tUsuario& usuario);

/**
* Dado un identificador de usuario y la lista, devuelve, si dicho identificador existe en la lista, su posici�n y el valor true,
* y si no existe en la lista, la posici�n que le corresponder�a y el valor false.
*/
bool buscarUsuario(const tListaUsuarios& listaUsuarios, string id, int& posicion);

/**
* Dada una lista de usuarios, ordena los elementos alfabeticamente
*/
void ordenarUsuarios(tListaUsuarios& listaUsuarios);

/**
* Funcion que primero destrulle las listas de registro de un usuario y luego el usuario, de manera reiterada hasta destruir todos los punteros del
* array de usuarios.
*/
void destruir(tListaUsuarios& listaUsuarios);

#endif
