#ifndef GESTOR_H
#define GESTOR_H

using namespace std;

#include "listaCorreos.h"
#include "listaRegistros.h"
#include "listaUsuarios.h"

const string DOMINIO = "fdimail.com";

typedef struct{
	string dominio;
	int usuarioActivo;
	tListaCorreos correos;
	tListaUsuarios usuarios;
}tGestor;


/**
* Inicializa el gestor e intenta arrancarlo cargando la información del dominio que se le pasa como parámetro.
* Para ello inicializará y cargará la lista de usuarios y de correos de dicho dominio.
* Si tiene éxito en todas las operaciones devuelve true y si alguna falla devuelve false.
*/
bool arrancar(tGestor& gestor, string dominio);

/**
* Esta operación apaga el gestor y guarda para ello las listas de usuarios y de correos del dominio que se encontrase activo en ese momento.
*/
void apagar(const tGestor &gestor);

/**
*Lee los datos de usuario necesarios para crear una cuenta (id y contraseña) y si el id de usuario no existe y hay espacio en la lista de usuarios
* crea la cuenta del usuario y registra al nuevo usuario como usuario activo en el gestor. Devuelve un booleano indicando si la operación tuvo éxito.
*/
bool crearCuenta(tGestor &gestor);

/**
* Lee los datos de usuario necesarios para validar la cuenta (id y contraseña) y si el usuario existe y la contraseña coincide, 
* registra al usuario como usuario activo. Devuelve un booleano indicando si la operación tuvo éxito.
*/
bool iniciarSesion(tGestor &gestor);

/**
* Solicita el correo que el usuario quiere leer (será el número con el que el correo es mostrado por pantalla en la bandeja correspondiente),
* valida que existe y si es así, lo marca como correo leído. A continuación, busca el correo en la lista de correos y si lo encuentra 
* lo muestra en la pantalla de lectura del correo.
*/
void leerCorreo(tGestor& gestor, tListaRegistros& registros);


/**
* Este subprograma implementa el envío del correo en nuestra aplicación. Para ello el correo recibido como parámetro es insertado en la lista de correo.
* Si ha habido éxito, entonces se inserta el registro correspondiente en la lista de registros enviados del emisor y se intenta insertar igualmente un registro
* de dicho correo en la lista de registros recibidos del destinatario del correo. Si el destinatario no existe o si su bandeja de entrada está llena, 
* entonces se mostrará un mensaje de error.
*/
void enviarCorreo(tGestor& gestor, const tCorreo &correo);

/**
* Este subprograma implementa el borrado del correo de una bandeja de un determinado usuario (OJO: el correo no se borra de la lista de correos).
* Para ello, solicita el correo que el usuario quiere borrar (será el número con el que el correo es mostrado por pantalla en la bandeja correspondiente),
* valida que existe y si es así, procede a borrarlo.
*/
void borrarCorreo(tGestor& gestor, tListaRegistros& registros);

/**
* Este subprograma implementa la lectura rápida de correos sin leer. El resultado es que muestra en una pantalla todos los correos sin leer ordenados
* por asunto (ignorando todos los “Re: ”) y por fecha. Al finalizar su ejecución los correos sin leer quedarán marcados como leídos.
*/
void lecturaRapida(tGestor& gestor, tListaRegistros& registros);

/**
*	Esta funcion muestra la interfaz de usuario y toma una opcion a partir del menu de opciones de la sesion de usuario ya arrancada
*/
void gestionarSesion(tGestor& gestor);

/**
* Este subprograma muestra la interfaz basica del gestor, recibe un booleano que controla cual de las dos bandejas de mensajes (Entrada/Salida) debe mostrar
* en la vista rapida. 
*/
void mostrarInterfazUsuario(tGestor& gestor, bool bEntrada);

/**
* Procedimiento que muestra el contenido de una bandeja de registros de manera ordenada
* y con '*' para mensajes no leidos
*/
void mostarBandeja(const tGestor & gestor, bool bEntrada);

/**
* Muestra las disttintas opciones del usuario activo en el gestor, recibe un parametro booleano que controla si debe mostrar la la cabecera de bandeja entrada/salida,
* asi como modificar la opcion 4 del interfaz (ver bandeja entrada/salida).
*/
void mostrarMenu(bool bEntrada);

/**
*Muestra por pantalla el menu de opciones para la contestacion de un correo
*/
void mostrarMenuVerCorreo();


/**
* Genera una linea horizontal de "=" diseñada para ocupar la longitud por defecto de una consola de sistema de windows
*/
void lineaIntercalada();

#endif