#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "listaCorreos.h"

void inicializar(tListaCorreos &correos){
	correos.contador = 0;
}

bool cargar(tListaCorreos &correos, string dominio){
	bool ok;
	ifstream archivo;
	inicializar(correos);
	string nombreFichero = dominio + "_" + ficheroCorreos;
	
	archivo.open(nombreFichero);
	if(!archivo.is_open()){
	ok = false;
	}
	else{
		tCorreo correo;
		while (cargar(correo, archivo)){
		
		insertar(correos, correo);
		}
		archivo.close();
		ok = true;
	}
	return ok;
}

void guardar(const tListaCorreos &correos, string dominio){
	ofstream archivo;
	string nombreFichero = dominio + "_" + ficheroCorreos;
	
	archivo.open(nombreFichero);
	if(!archivo.is_open()){
	cout << "Error al guardar la lista de correos en el fichero" << endl;
	}
	else{
		for (int i= 0; i < correos.contador; i++){
		
		guardar(correos.correo[i], archivo);
		}
		archivo << "XXX" << endl;
		archivo.close();
	}
}

bool insertar(tListaCorreos &correos, const tCorreo &correo){
	bool ok = false;
	if(correos.contador < MAXCORREOS){
		correos.correo[correos.contador] = correo;
		correos.contador++;
		ok = true;
	}
	return ok;
}

bool borrar(tListaCorreos &correos, string id){
	bool borrado = false;
	int posicion;
	buscar(correos, id , posicion);
	if(posicion != -1){
				for (posicion; posicion < correos.contador; posicion++){
			correos.correo[posicion] = correos.correo[posicion+1];
		}
		correos.contador--;
		borrado = true;
	}
return borrado;
}

bool buscar(const tListaCorreos &correos, string id, int &pos){
	bool encontrado = false;

	pos = 0;
	while (pos < correos.contador && !encontrado){
		if (id == correos.correo[pos].identificador){
			encontrado = true;
		}
		else{
			pos++;
		}		
	}
	return encontrado;
}

void ordenar_AF(tListaCorreos &correos){
	bool intercambio = true;
	int i = 0;
	
	while((i<correos.contador) && intercambio){
		intercambio = false;
		for (int j = correos.contador-1; j > i; j--){
			if(correos.correo[j] < correos.correo[j-1]){
				tCorreo tmp;
				tmp = correos.correo[j];
				correos.correo[j] = correos.correo[j-1];
				correos.correo[j-1] = tmp;
				intercambio = true;
			}
		}
		if (intercambio) i++;
	}
}
