#ifndef ITGO_H
#define ITGO_H

#include <vector>
#include "funciones.h"

using namespace std;


vector<int> algoritmoITGO(double beta, int Dist, int tam, double max_fes);

void movimientoCelulas(vector<vector<float> > cCells, vector<vector<float> > hCells, Celula nutrientes, vector<int> gc, vector<float> bestFitness, int max_Gc);

void cellInvasivas(vector<int> &cPCells, int tamPCells, vector<int> DCells, int gc, int &fes, int max_Gc);
void randomWalk(vector<float> &cell, int &gc);//return gc actualiza cell
#endif