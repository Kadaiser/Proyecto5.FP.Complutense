#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "listaRegistros.h"

void inicializar(tListaRegistros& listaRegistros){
//void inicializar(tListaRegistros *tRegistroPtr){
	listaRegistros.contador = 0;
}

void cargar(tListaRegistros &listaRegistros, ifstream& archivo){
	int elementos;
	tRegistro registro; 
	
	
	inicializar(listaRegistros);
	archivo >> elementos;
	if(elementos>0){
		for(int i = 0; i < elementos; i++){
			cargarRegistro(registro, archivo);
			insertar(listaRegistros, registro);
		}
	}
}

void guardar(const tListaRegistros &listaRegistros, ofstream& archivo){
	for(int i= 0; i < listaRegistros.contador; i++){
		archivo << listaRegistros.registro[i].identificador << " " << listaRegistros.registro[i].leido << endl;
	}
}

bool insertar(tListaRegistros &listaRegistros, tRegistro registro){
	bool ok = false;
	if(listaRegistros.contador < MAXREGISTROS){
		listaRegistros.registro[listaRegistros.contador] = registro;
		listaRegistros.contador++;
		ok = true;
	}
	return ok;
}

bool borrar(tListaRegistros &listaRegistros, string id){
	bool borrado = false;
	int posicion = buscar(listaRegistros,id);
	if(posicion != -1){
			for (posicion; posicion < listaRegistros.contador; posicion++){
				listaRegistros.registro[posicion] = listaRegistros.registro[posicion+1];
		}
		listaRegistros.contador--;
		borrado = true;
	}
return borrado;
}

bool correoLeido(tListaRegistros &listaRegistros, string id){
	bool check = false;
	int posicion = buscar(listaRegistros,id);

	if(posicion != -1){
		listaRegistros.registro[posicion].leido = true;
		check = true;
	}	
	return check;
}

int buscar(const tListaRegistros &listaRegistros, string id){
	int posicion;
	int ini = 0, fin = listaRegistros.contador-1, mitad;
	
	bool encontrado = false;			//Por defecto no se ha econtrado el elemento que se busca
	
	while(ini<=fin && !encontrado){		//Mientras que mi rango de busqueda exista y no haya encontrado el elemento
		mitad = (ini+fin) / 2;

		if(id < listaRegistros.registro[mitad].identificador){
		fin = mitad - 1;
		}
		else if(listaRegistros.registro[mitad].identificador < id){
		ini = mitad + 1;
		}
		else{
		encontrado = true;
		}
	}
	if(encontrado) posicion = mitad;
	else posicion = -1;
	
	return posicion;
}


void cargarRegistro(tRegistro& registro, ifstream& archivo){
		archivo >>registro.identificador;
		archivo >>registro.leido;
}
