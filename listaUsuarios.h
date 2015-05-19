#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

using namespace std;

#include "usuario.h"

const string ficheroUsuarios = "Usuarios.txt";
const int MAXUSUARIOS = 100;

typedef struct{
tUsuario usuario[MAXUSUARIOS];
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
* Añade un usuario en la posición de la lista que le corresponde, si hay sitio para ello.
* Además devuelve un booleano indicando si la operación tuvo éxito o no.
*/
bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario);

/**
* Dado un identificador de usuario y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true, 
* y si no existe en la lista, la posición que le correspondería y el valor false.
*/
bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion);

/**
* Dada una lista de usuarios, ordena los elementos alfabeticamente
*/
void ordenarUsuarios(tListaUsuarios& usuarios);


#endif