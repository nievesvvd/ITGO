#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector.h>
#include <algorithm>    // std::random_shuffle
#include "random_ppio.h"

using namespace std;

/**Funcion con la que generamos una poblacion inicial aleatoria donde
// tam es el tamaño de la poblacion (longitud del vector)
// poblacion es el numero de individuos que vamos a crear
**/
vector <vector<int> > generarPoblacion(int tam, int poblacion, vector<vector<double> > &poblacionIni, vector<vector<double> > &mejorCell);
//ordenamos la poblacion de forma ascendente con respecto a la cantidad de nutrientes D/Q/P
void ordenarPoblacion(vector<vector<double> > &poblacionIni, vector<double> fitness, int tam, int pobl);
void separarPoblacion(vector<vector<double> > poblacionIni, vector<int> &PCells, vector<int> &QCells, vector<int> &DCells);
void actualizarPoblacion(vector<vector<double> > &poblacionIni, vector<int> PCells, vector<int> QCells, vector<int> DCells);
//vector <Celulas> distanciaEuclidea(vector <Celulas> QCells, Celulas cell); cogemos dos cell aleatorias mejor

double fitness(vector<double> cell);
double mediaFitness(vector<vector<double> > DCells);
double alpha(int fes, int max_fes);
double levy(double step);

#endif