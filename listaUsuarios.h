#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

using namespace std;

#include "usuario.h"

const string ficheroUsuarios = "Usuarios.txt";
const int MAXUSUARIOS = 50;

typedef tUsuarioPtr tArrayUsuarioPtr[MAXUSUARIOS];//Array de punteros a un usuario

typedef struct{
//tUsuario usuarios[MAXUSUARIOS];
tArrayUsuarioPtr usuarios;
int contador;
}tListaUsuarios;

/**
* Inicializa la lista
*/
void inicializar(tListaUsuarios &usuarios);

/**
* Implementa la carga de la lista de usuarios desde el fichero de usuarios 
* de nombre <NombreDominio>_usuarios.txt .
*/
bool cargar(tListaUsuarios& usuarios, string dominio);

/**
* Implementa el guardado de la lista de usuarios en el fichero de usuarios 
* de nombre <NombreDominio>_usuarios.txt .
*/
void guardar(const tListaUsuarios& usuarios, string dominio);

/**
* A�ade un usuario en la posici�n de la lista que le corresponde, si hay sitio para ello.
* Adem�s devuelve un booleano indicando si la operaci�n tuvo �xito o no.
*/
bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario);

/**
* Dado un identificador de usuario y la lista, devuelve, si dicho identificador existe en la lista, su posici�n y el valor true, 
* y si no existe en la lista, la posici�n que le corresponder�a y el valor false.
*/
bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion);

/**
* Dada una lista de usuarios, ordena los elementos alfabeticamente
*/
void ordenarUsuarios(tListaUsuarios& usuarios);


#endif