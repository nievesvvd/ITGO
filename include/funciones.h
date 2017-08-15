#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector.h>
#include "random_ppio.h"

using namespace std;

void generarPoblacion();
void ordenarPoblacion(vector<Celulas> &poblacionIni);
void separarPoblacion(vector<Celulas> &PCells, vector<Celulas> &QCells, vector<Celulas> &DCells);

double fitness();
double alpha(double fes, double max_fes);
double levy(double lamda);




#endif