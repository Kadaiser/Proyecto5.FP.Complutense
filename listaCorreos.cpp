#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "listaCorreos.h"

void inicializar(tListaCorreos &listaCorreos){
	listaCorreos.contador = 0;
}

bool cargar(tListaCorreos &listaCorreos, string dominio){
	bool ok;
	ifstream archivo;
	inicializar(listaCorreos);
	string nombreFichero = dominio + "_" + ficheroCorreos;
	
	archivo.open(nombreFichero);
	if(!archivo.is_open()){
	ok = false;
	}
	else{
		tCorreo correo;
		while (cargar(correo, archivo)){
		
		insertar(listaCorreos, correo);
		}
		archivo.close();
		ok = true;
	}
	return ok;
}

void guardar(const tListaCorreos &listaCorreos, string dominio){
	ofstream archivo;
	string nombreFichero = dominio + "_" + ficheroCorreos;
	
	archivo.open(nombreFichero);
	if(!archivo.is_open()){
	cout << "Error al guardar la lista de correos en el fichero" << endl;
	}
	else{
		for (int i= 0; i < listaCorreos.contador; i++){
		
		guardar(listaCorreos.correo[i], archivo);
		}
		archivo << "XXX" << endl;
		archivo.close();
	}
}

bool insertar(tListaCorreos &listaCorreos, const tCorreo &correo){
	bool ok = false;
	if(listaCorreos.contador < MAXCORREOS){
		listaCorreos.correo[listaCorreos.contador] = correo;
		listaCorreos.contador++;
		ok = true;
	}
	return ok;
}

bool borrar(tListaCorreos &listaCorreos, string id){
	bool borrado = false;
	int posicion;
	buscar(listaCorreos, id , posicion);
	if(posicion != -1){
				for (posicion; posicion < listaCorreos.contador; posicion++){
			listaCorreos.correo[posicion] = listaCorreos.correo[posicion+1];
		}
		listaCorreos.contador--;
		borrado = true;
	}
return borrado;
}

bool buscar(const tListaCorreos &listaCorreos, string id, int &pos){
	bool encontrado = false;

	pos = 0;
	while (pos < listaCorreos.contador && !encontrado){
		if (id == listaCorreos.correo[pos].identificador){
			encontrado = true;
		}
		else{
			pos++;
		}		
	}
	return encontrado;
}

void ordenar_AF(tListaCorreos &listaCorreos){
	bool intercambio = true;
	int i = 0;
	
	while((i<listaCorreos.contador) && intercambio){
		intercambio = false;
		for (int j = listaCorreos.contador-1; j > i; j--){
			if(listaCorreos.correo[j] < listaCorreos.correo[j-1]){
				tCorreo tmp;
				tmp = listaCorreos.correo[j];
				listaCorreos.correo[j] = listaCorreos.correo[j-1];
				listaCorreos.correo[j-1] = tmp;
				intercambio = true;
			}
		}
		if (intercambio) i++;
	}
}
