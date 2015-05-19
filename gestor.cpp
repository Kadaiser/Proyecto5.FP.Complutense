#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#include "fecha.h"
#include "gestor.h"


void inicializar(tGestor& gestor, string dominio){
	gestor.dominio = dominio;
}

bool arrancar(tGestor& gestor, string dominio){
	inicializar(gestor, DOMINIO);
	return (cargar(gestor.usuarios, dominio) && cargar(gestor.correos, dominio));
}


void apagar(const tGestor &gestor){
	system("cls");
	cout << "Cerrando gestor de correo " << gestor.dominio << endl;
	guardar(gestor.usuarios, gestor.dominio);
	guardar(gestor.correos, gestor.dominio);
	
}


bool crearCuenta(tGestor &gestor){
	bool ok = false;
	tUsuario usuario;
	string identificador, contrasenia;
	int posUsuario;
		
		cout << "Elija un identificador de cuenta: ";
		cin >> identificador;
		cin.sync();
		identificador = identificador + "@"+ gestor.dominio;
			while(buscarUsuario(gestor.usuarios, identificador, posUsuario)){
				cout << "Usuario no disponible, por favor, escoja otro identificador: " << endl;
				cin >> identificador;
				cin.sync();
				identificador = identificador + "@"+ gestor.dominio;
			}
		cout << "Elija una contrasenia: ";
		cin >> contrasenia;
		cin.sync();
	
		inicializar(usuario, identificador, contrasenia);
			if(aniadir(gestor.usuarios, usuario)) ok = true;
			else cout << "No pudo incluirse el usuario en la lista de usuarios";

		cout << "Se genero su cuenta correctamente." << endl << "Va a iniciar su primera sesion en " << gestor.dominio << endl;
		buscarUsuario(gestor.usuarios, identificador, gestor.usuarioActivo); //Otra forma de reutilzar la funcion de busqueda de uusuarios es para cargar el usuario activo en base al identificador recien creado
		system("pause");
return ok;
}


bool iniciarSesion(tGestor &gestor){
	bool ok = false;
	int posUsuario;
	string identificador;
	string contrasenia;
	
		cout << "Bienvenido al correo de " << gestor.dominio <<endl;
		cout << "Introduzca su direccion de correo: ";
		cin >> identificador;
		cin.sync();
		if(buscarUsuario(gestor.usuarios, identificador, posUsuario)){
			cout << "Introduzca su contrasenia: ";
			cin >> contrasenia;
			cin.sync();
			if(validarContrasenia(gestor.usuarios.usuario[posUsuario], contrasenia)){
				gestor.usuarioActivo = posUsuario;
				ok = true;
				cout << "Iniciando sesion..." << endl;
			}
			else{
				cout << "Contrasenia incorrecta, regresando a menu principal" << endl;
			}
		}
		else{
			cout << "Cuenta no existe, regresando a menu principal"<< endl;
		}
	system("pause");
return ok;
}



void leerCorreo(tGestor& gestor, tListaRegistros& registros){
	int numCorreo, pos, opcion;
	string cabecera, cadena;
	tCorreo correoRespondido;

	cout << "Introduzca el numero correo a leer: ";
	cin >> numCorreo;
	system("cls");
	
	if (numCorreo > 0 && numCorreo <= registros.contador){
		correoLeido(registros, registros.registro[numCorreo-1].identificador); //Al acceder a un correo siempre en la posicion n-1 respecto de lo que el usuario ve en la lista, se marca como leid
		buscar(gestor.correos, registros.registro[numCorreo-1].identificador, pos);	//Buscar correo en la lista de correos
		cout << aCadena(gestor.correos.correo[pos]); //Se muestra el contenido del correo
		mostrarMenuVerCorreo();	//Se muestra el menu de opciones d ela lectura de correos
		cin >> opcion;
		
		if (opcion == 1){
			correoContestacion (gestor.correos.correo[pos], correoRespondido, gestor.correos.correo[pos].destinatario);	//Se puede enviar una respuesta (Re:) al emisor; 
			enviarCorreo(gestor, correoRespondido);
		}
	}
}



void enviarCorreo(tGestor& gestor, const tCorreo &correo){	
	tRegistro registro;
	int pos;

	if (buscarUsuario(gestor.usuarios, correo.destinatario, pos)){
		if(insertar(gestor.correos, correo)){
			registro.leido = true;
			registro.identificador = correo.identificador;	
			if (insertar(gestor.usuarios.usuario[gestor.usuarioActivo].bandejaSalida, registro)){
				registro.leido = false;
				if (insertar(gestor.usuarios.usuario[pos].bandejaEntrada, registro)){
					cout << "Correo enviado correctamente." << endl;
				}
				else{
					cout << "Bandeja de correo de destinatario llena!!!" << endl;
				}
			}
		}
		else
			cout << "Bandeja de salida de emisor llena!!" << endl;
	}
	else
		cout << "Destinatario no encontrado" << endl;
}



void borrarCorreo(tGestor& gestor, tListaRegistros& registros){
	int numCorreo;
	int i = 0;
	string id;
	bool existe = false;
	cout << "Introduzca el numero correo a borrar: ";
	cin >> numCorreo;

	if (numCorreo > 0 && numCorreo <= registros.contador){
		id = registros.registro[numCorreo - 1].identificador;
		if(borrar(registros, registros.registro[numCorreo - 1].identificador)){
			cout << "El mensaje se elimino de tu bandeja correctamente." << endl;
		
		while(i < gestor.usuarios.contador && !existe){
				if((buscar(gestor.usuarios.usuario[i].bandejaEntrada, id) != -1) || (buscar(gestor.usuarios.usuario[i].bandejaSalida, id) != -1))//si no existe el identificador en ninguna lista de registros de ningun usuario, entonces borramos el correo de la lista de correos
					existe = true;
					i++;
			}
			if(!existe && borrar(gestor.correos, id))
			cout << "Tambien ha sido elmininado de la base de datos" << endl;
		}
	}
		else
			cout << "Correo inexistente." << endl;
	system("pause");
}


void lecturaRapida(tGestor& gestor, tListaRegistros& registros){
	int pos;
	system("cls");

	ordenar_AF(gestor.correos);

	for (int i = 0; i<registros.contador; i++){

		if (!registros.registro[i].leido){
			buscar(gestor.correos, registros.registro[i].identificador, pos);	
			cout << aCadena(gestor.correos.correo[pos]);
			correoLeido(gestor.usuarios.usuario[gestor.usuarioActivo].bandejaEntrada, registros.registro[i].identificador);
			lineaIntercalada();
		}
	}
	system("pause");
}



void gestionarSesion(tGestor& gestor){
	int opcion;
	bool bEntrada= true;
	tCorreo nuevoCorreo;

	do{
		mostrarInterfazUsuario(gestor, bEntrada);
		cin >> opcion;
		if(opcion ==1){
			if (bEntrada){
				leerCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo].bandejaEntrada);		
			}
			else{
				leerCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo].bandejaSalida);		
			}
		}
		else if(opcion == 2){
			system("cls");
			correoNuevo(nuevoCorreo, gestor.usuarios.usuario[gestor.usuarioActivo].identificador);
			enviarCorreo(gestor, nuevoCorreo);
			system("pause");
		}
		else if(opcion == 3){
			if (bEntrada){
				borrarCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo].bandejaEntrada);		
			}
			else{
				borrarCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo].bandejaSalida);		
			}
		}
		else if(opcion == 4){
			bEntrada = !bEntrada;
		}
		else if(opcion == 5){
			lecturaRapida(gestor, gestor.usuarios.usuario[gestor.usuarioActivo].bandejaEntrada);
		}
	}while(opcion != 0);
	system("cls");
}

void mostrarInterfazUsuario(tGestor& gestor, bool bEntrada){
	system("cls");
	cout << "correo de " << gestor.usuarios.usuario[gestor.usuarioActivo].identificador << endl;
	for(int i=0; i<30;i++) cout << "=";
	cout << "Bandeja de ";
		if(bEntrada) cout << "entrada";
		else cout << "salida=";
	for(int i=0; i<32;i++) cout << "=";
	
	lineaIntercalada();
	if(bEntrada){
		cout <<"L" << setw(2) << "N" << setw(10) << "EMISOR" << setw(30) << "ASUNTO" << setw(35) << "FECHA" << endl;
	}
	else
		cout <<"L" << setw(2) << "N" << setw(15) << "DESTINATARIO" << setw(25) << "ASUNTO" << setw(35) << "FECHA" << endl;
	lineaIntercalada();

	mostarBandeja(gestor, bEntrada);

	lineaIntercalada();
	mostrarMenu(bEntrada);
	
}

void mostarBandeja(const tGestor & gestor, bool bEntrada){
	int pos;
	tUsuario usuario = gestor.usuarios.usuario[gestor.usuarioActivo];

	if(bEntrada){
		for(int i =  0; i< usuario.bandejaEntrada.contador; i++){
			if(usuario.bandejaEntrada.registro[i].leido) cout << " ";
			else cout << "*";
			if (buscar(gestor.correos, usuario.bandejaEntrada.registro[i].identificador, pos)){
				cout << setw(2) << i+1 << " "  << gestor.correos.correo[pos].emisor << setw(25) << gestor.correos.correo[pos].asunto << setw(25) << mostrarSoloDia(gestor.correos.correo[pos].fecha) << endl;
			}
		}
	}
	else{
		for(int i =0; i < usuario.bandejaSalida.contador; i++){
			if (buscar(gestor.correos, usuario.bandejaSalida.registro[i].identificador, pos)){
				cout << " " << setw(2) << i+1 << " "  << gestor.correos.correo[pos].destinatario << setw(25) << gestor.correos.correo[pos].asunto << setw(25) << mostrarSoloDia(gestor.correos.correo[pos].fecha) << endl;
			}
		}
	}
}

void mostrarMenu(bool bEntrada){
	cout << "Elija una opcion:" << endl;
	cout << setw(3) << "1- Leer correo" << endl;
	cout << setw(3) << "2- Enviar correo" << endl;
	cout << setw(3) << "3- Borrar correo" << endl;
	cout << setw(3) << "4- Ver bandeja de ";
	if(bEntrada) cout << "salida" << endl;
	else cout << "entrada" << endl;
	cout << setw(3) << "5- Lectua rapida de correos sin leer" << endl;
	cout << setw(3) << "0- Cerrar sesion" << endl;
	lineaIntercalada();
	cout << "Introduzca un opcion:";
}

void mostrarMenuVerCorreo(){
	lineaIntercalada();
	cout << "Elija una opcion:" << endl;
	cout << setw(3) << "1- Contestar correo" << endl;
	cout << setw(3) << "0- Volver a la bandeja" << endl;
	lineaIntercalada();
	cout << "Introduzca un opcion:";	
}

void lineaIntercalada(){
	for(int i=0; i<80;i++) cout << "=";
}
