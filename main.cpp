#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

#include "gestor.h"


int menu();
void menuEntrada();


/**
*	PROGRAMA PRINCIPAL
*/

int main(){

tGestor gestor;
int opcion;


	if(!arrancar(gestor,DOMINIO)){
		cout << "No se ha podido acceder a los ficheros. Se arranca con listas vacias" << endl;
		system("pause");
	}
		do{
			opcion = menu();
			system("cls");
			switch(opcion){
				case 1:
				if(iniciarSesion(gestor))
					gestionarSesion(gestor);
					break;
				case 2:
				if(crearCuenta(gestor))
					gestionarSesion(gestor);
				break;
			}	
		}while(opcion != 0);
		apagar(gestor);
	system("pause");
	return 0;
}




int menu(){
	system("cls");
	int opcion;
		menuEntrada();
		cin >> opcion;
		cin.sync();
		while(opcion <0 || opcion >2){		
			cin >> opcion;
			cin.sync();
		}
	return opcion;
}

void menuEntrada(){
	
		cout << "Elija la opcion deseada:" << endl;
		cout << "1- Acceder a mi cuenta de correo" << endl;
		cout << "2- Crear cuenta de correo" << endl << endl;
		cout << "0- Salir" << endl;
		cout << "Opcion: ";
	
}