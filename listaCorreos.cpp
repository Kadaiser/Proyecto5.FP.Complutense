#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

#include "listaCorreos.h"

void inicializar(tListaCorreos &listaCorreos, int capacidad){
	listaCorreos.correos = new tCorreo [capacidad];
	listaCorreos.contador = 0;
	listaCorreos.capacidad = capacidad;
}


bool cargar(tListaCorreos &listaCorreos, string dominio){
	bool ok;
	ifstream archivo;
	string nombreFichero = dominio + "_" + ficheroCorreos;
	float numElementos, numRedondeado;
	tCorreo correo;

	archivo.open(nombreFichero);
	if(!archivo.is_open()){
		inicializar(listaCorreos, CORREOS_INICIAL);
		ok = false;
	}
	else{
		archivo >> numElementos;
		numRedondeado = (ceil(numElementos / 10)) * 10;
		inicializar(listaCorreos, (int)numRedondeado);

		for(int i = 0; i < numElementos; i++){

			cargar(correo, archivo);
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
		archivo << listaCorreos.contador << endl;
		for (int i= 0; i < listaCorreos.contador; i++){
			guardar(listaCorreos.correos[i], archivo);
		}
		archivo.close();
	}
}

void insertar(tListaCorreos &listaCorreos, const tCorreo &correo){

	if(listaCorreos.contador == listaCorreos.capacidad){
		redimensionar(listaCorreos);
	}
	listaCorreos.correos[listaCorreos.contador] = correo;
	listaCorreos.contador++;

}


bool borrar(tListaCorreos &listaCorreos, string id){
	bool borrado = false;
	int posicion;
	buscar(listaCorreos, id , posicion);
	if(posicion != -1){
				for (posicion; posicion < listaCorreos.contador; posicion++){
			listaCorreos.correos[posicion] = listaCorreos.correos[posicion+1];
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
		if (id == listaCorreos.correos[pos].identificador){
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
			if(listaCorreos.correos[j] < listaCorreos.correos[j-1]){
				tCorreo tmp;
				tmp = listaCorreos.correos[j];
				listaCorreos.correos[j] = listaCorreos.correos[j-1];
				listaCorreos.correos[j-1] = tmp;
				intercambio = true;
			}
		}
		if (intercambio) i++;
	}
}


void redimensionar(tListaCorreos & listaCorreos){
	int i = 0;
	int nuevaCapacidad = (listaCorreos.capacidad * 3)/2+1;
	tListaCorreos nuevaLista; //crear nuevo array

	inicializar(nuevaLista, nuevaCapacidad);

	//copiar viejo a nuevo
	while ( i < listaCorreos.contador ){
		insertar(nuevaLista, listaCorreos.correos[i++]);
	}
	listaCorreos = nuevaLista;
}


void destruir(tListaCorreos& listaCorreos){
	delete[] listaCorreos.correos;
}
