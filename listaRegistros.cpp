#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

#include "listaRegistros.h"

void inicializar(tListaRegistros& listaRegistros, int capInicial){ //el 3er parametro se ajusta a el valor constante si no se le pasa dicho parametro
	listaRegistros.registros = new tRegistro[capInicial];
	listaRegistros.contador = 0;
	listaRegistros.capacidad = capInicial;
}


void cargar(tListaRegistros &listaRegistros, ifstream& archivo){
	float numElementos, numRedondeado;
	tRegistro registro;

	archivo >> numElementos;
	numRedondeado = (ceil(numElementos / 10)) * 10; //redondeos a la siguiente
	inicializar(listaRegistros, (int)numRedondeado);
	if(numElementos>0){
		for(int i = 0; i < numElementos; i++){
			cargarRegistro(registro, archivo);
			insertar(listaRegistros, registro);
		}
	}
}


void guardar(const tListaRegistros &listaRegistros, ofstream& archivo){
	for(int i= 0; i < listaRegistros.contador; i++){
		archivo << listaRegistros.registros[i].identificador << " " << listaRegistros.registros[i].leido << endl;
	}
}


void insertar(tListaRegistros &listaRegistros, tRegistro registro){
	if(listaRegistros.contador == listaRegistros.capacidad){
		redimensionar(listaRegistros);
	}
	listaRegistros.registros[listaRegistros.contador] = registro;
	listaRegistros.contador++;
}


bool borrar(tListaRegistros &listaRegistros, string id){
	bool borrado = false;
	int posicion = buscar(listaRegistros,id);

	if(posicion != -1){
			for (posicion; posicion < listaRegistros.contador; posicion++){
				listaRegistros.registros[posicion] = listaRegistros.registros[posicion+1];
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
		listaRegistros.registros[posicion].leido = true;
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

		if(id < listaRegistros.registros[mitad].identificador){
		fin = mitad - 1;
		}
		else if(listaRegistros.registros[mitad].identificador < id){
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


void redimensionar (tListaRegistros &listaRegistros){
	int i = 0;
	int nuevaCapacidad = (listaRegistros.capacidad * 3)/2+1;
	tListaRegistros nuevaLista; //crear nueva estructura con  array

	inicializar(nuevaLista, nuevaCapacidad);

	while ( i < listaRegistros.contador ){			//copiar viejo a nuevo
		insertar(nuevaLista, listaRegistros.registros[i++]);
	}
	listaRegistros = nuevaLista; //Se sobreescriben los punteros de la vieja lista
}


void destruir(tListaRegistros &listaRegistros){
	delete[] listaRegistros.registros;
}
