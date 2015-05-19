#ifndef FECHA_H
#define FECHA_H

typedef time_t tFecha;

/**
*  Dada una estrucutura de tipo fecha, devuelve un string completo de la fecha YY/MM/DD - HH/MM/SS
*/
string mostrarFecha(tFecha fecha);

/**
*  Dada una estrucutura de tipo fecha, devuelve un string completo de la fecha YY/MM/DD
*/
string mostrarSoloDia(tFecha fecha);

#endif