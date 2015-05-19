#include <string>
#include <sstream>
#include <ctime>

using namespace std;

#include "fecha.h"

string mostrarFecha(tFecha fecha){     
	stringstream resultado;     
	tm ltm;     
	localtime_s(&ltm, &fecha);     
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon <<"/"<< ltm.tm_mday;     
	resultado<<" ("<<ltm.tm_hour<< ":" <<ltm.tm_min<< ":" << ltm.tm_sec << ")";  
	return resultado.str();   
} 


string mostrarSoloDia(tFecha fecha){    
	stringstream resultado;     
	tm ltm;     
	localtime_s(&ltm, &fecha);     
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon <<"/"<< ltm.tm_mday;     
	return resultado.str();   
}