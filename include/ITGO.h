#ifndef ITGO_H
#define ITGO_H

#include "funciones.h"

vector<float> algoritmoITGO(/*double beta,*/ int dim, int tamPob, int max_fes);

void movePCells(int PCells, vector<int> &gc, int &fes, int max_Gc, int max_fes);
void moveQCells(int PCells, int QCells, vector<int> &gc, int &fes, int max_Gc, int max_fes);
void moveDCells(int PCells, int QCells, int DCells,  vector<int> &gc, int &fes, int max_Gc);

void cellInvasivas(int tamPob, int &fes);
void randomWalk(int cell, int &gc);
#endif