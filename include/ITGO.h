#ifndef ITGO_H
#define ITGO_H

#include <vector>
#include "funciones.h"

using namespace std;


vector<float> algoritmoITGO(double beta, int dim, int tamPob, int max_fes);

void movePCells(int PCells, vector<int> &gc, int &fes);
void moveQCells(int PCells, int QCells, vector<int> &gc, int &fes);
void moveDCells(int PCells, int QCells, int DCells,  vector<int> &gc, int &fes);

void cellInvasivas(int tamPob);
void randomWalk(int cell, vector<int> &gc);
#endif