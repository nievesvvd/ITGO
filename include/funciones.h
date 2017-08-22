#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector.h>
#include "random_ppio.h"

using namespace std;

vector <Celulas> generarPoblacion(int tam);
void ordenarPoblacion(vector<Celulas> &poblacionIni);
void separarPoblacion(vector<Celulas> poblacionIni, vector<Celulas> &PCells, vector<Celulas> &QCells, vector<Celulas> &DCells);
void actualizarPoblacion(vector<Celulas> &poblacionIni, vector<Celulas> PCells, vector<Celulas> QCells, vector<Celulas> DCells);
vector <Celulas> distanciaEuclidea(vector <Celulas> QCells, Celulas cell);

double fitness(Celula cell);
double mediaFitness(vector <Celulas> DCells);
double alpha(double fes, double max_fes);
double levy(double beta);




#endif