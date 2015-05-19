#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "listaUsuarios.h"


void inicializar(tListaUsuarios &usuarios){
	usuarios.contador=0;
}


bool cargar(tListaUsuarios& usuarios, string dominio){
	bool ok;
	ifstream archivo;
	inicializar(usuarios);
	string nombreFichero = dominio + "_" + ficheroUsuarios;

	archivo.open(nombreFichero);
	if(!archivo.is_open()){
	ok = false;
	}
	else{
		tUsuario usuario;
		while (cargar(usuario,archivo)){
		aniadir(usuarios, usuario);
		}
		archivo.close();
		ok = true;
	}
	return ok;
}

void guardar(const tListaUsuarios& usuarios, string dominio){
	ofstream archivo;
	string nombreFichero = dominio + "_" + ficheroUsuarios;
	
	archivo.open(nombreFichero);
	if(!archivo.is_open()){
	cout << "Error al guardar la lista de correos en el fichero" << endl;
	}
	else{
		for (int i= 0; i < usuarios.contador; i++){
		
		guardar(usuarios.usuario[i], archivo);
		}
		archivo << "XXX";
		archivo.close();
	}
}


bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario){
	bool ok = false;
	
	if(usuarios.contador < MAXUSUARIOS){
		usuarios.usuario[usuarios.contador]= usuario;
		usuarios.contador++;
		ordenarUsuarios(usuarios);
		ok = true;
	}
	return ok;
}

bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion){

	int ini = 0, fin = usuarios.contador-1, mitad;
	bool encontrado = false;			//Por defecto no se ha econtrado el elemento que se busca
	while(ini<=fin && !encontrado){		//Mientras que mi rango de busqueda exista y no haya encontrado el elemento
		mitad = (ini+fin) / 2;

		if(id < usuarios.usuario[mitad].identificador){
		fin = mitad - 1;
		}
		else if(usuarios.usuario[mitad].identificador < id){
		ini = mitad + 1;
		}
		else{
		encontrado = true;
		}
	}
	if(encontrado) posicion = mitad;
	else posicion = ini;
	
	return encontrado;
}

/* Variante de ordenacion por insercion */
void ordenarUsuarios(tListaUsuarios& usuarios){
	int pos=0;
	tUsuario nuevo;
	
	nuevo = usuarios.usuario[usuarios.contador-1];
	while ((pos < usuarios.contador-1) && !(usuarios.usuario[pos].identificador > nuevo.identificador)) {
		pos++;
	}
	for (int j = usuarios.contador-1; j > pos; j--) {
		usuarios.usuario[j] = usuarios.usuario[j-1];
	}
	usuarios.usuario[pos] = nuevo;
		
}