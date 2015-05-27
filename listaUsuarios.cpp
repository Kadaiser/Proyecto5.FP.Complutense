#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "listaUsuarios.h"


void inicializar(tListaUsuarios &listaUsuarios){
	listaUsuarios.contador=0;
	//hay que llenar a nullptr los elementos del array del MAXUSUARIOS
	for(int i = 0; i < MAXUSUARIOS; i++){
		listaUsuarios.usuarios[i] = nullptr;
	}
}


bool cargar(tListaUsuarios& listaUsuarios, string dominio){
	bool ok;
	ifstream archivo;
	inicializar(listaUsuarios);
	string nombreFichero = dominio + "_" + ficheroUsuarios;

	archivo.open(nombreFichero);
	if(!archivo.is_open()){
		ok = false;
	}
	else{
		tUsuario usuario;
		while (cargar(usuario,archivo)){
			aniadir(listaUsuarios, usuario);
		}
		archivo.close();
		ok = true;
	}
	return ok;
}

void guardar(const tListaUsuarios& listaUsuarios, string dominio){
	ofstream archivo;
	string nombreFichero = dominio + "_" + ficheroUsuarios;
	
	archivo.open(nombreFichero);
	if(!archivo.is_open()){
		cout << "Error al guardar la lista de correos en el fichero" << endl;
	}
	else{
		for (int i= 0; i < listaUsuarios.contador; i++){		
			guardar(*listaUsuarios.usuarios[i], archivo);
		}
		archivo << "XXX";
		archivo.close();
	}
}


bool aniadir(tListaUsuarios& listaUsuarios, const tUsuario& usuario){
	bool ok = false;
	
	if(listaUsuarios.contador < MAXUSUARIOS){
		listaUsuarios.usuarios[listaUsuarios.contador]= new tUsuario(usuario);
		listaUsuarios.contador++;

		ordenarUsuarios(listaUsuarios);
		ok = true;
	}
	return ok;
}

bool buscarUsuario(const tListaUsuarios& listaUsuarios, string id, int& posicion){

	int ini = 0, fin = listaUsuarios.contador-1, mitad;
	bool encontrado = false;			//Por defecto no se ha econtrado el elemento que se busca
	while(ini<=fin && !encontrado){		//Mientras que mi rango de busqueda exista y no haya encontrado el elemento
		mitad = (ini+fin) / 2;

		if(id < listaUsuarios.usuarios[mitad]->identificador){
		fin = mitad - 1;
		}
		else if(listaUsuarios.usuarios[mitad]->identificador < id){
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
void ordenarUsuarios(tListaUsuarios& listaUsuarios){
	int pos=0;
	tUsuarioPtr nuevo;
	
	nuevo = listaUsuarios.usuarios[listaUsuarios.contador-1];
	while ((pos < listaUsuarios.contador-1) && !(listaUsuarios.usuarios[pos]->identificador > nuevo->identificador)) {
		pos++;
	}
	for (int j = listaUsuarios.contador-1; j > pos; j--) {
		listaUsuarios.usuarios[j] = listaUsuarios.usuarios[j-1];
	}
	listaUsuarios.usuarios[pos] = nuevo;
		
}

void destruir(tListaUsuarios& listaUsuarios){
	for (int i = 0; i < listaUsuarios.contador; i++){
		destruir(listaUsuarios.usuarios[i]->bandejaEntrada);
		destruir(listaUsuarios.usuarios[i]->bandejaSalida);
		delete listaUsuarios.usuarios[i];
	}
}