#ifndef ITGO_H
#define ITGO_H

#include <vector.h>
#include "funciones.h"

using namespace std;


vector<int> algoritmoITGO(double beta, int Dist, int tam, double max_fes);
void crecimientoPCell(vector<int> &hCells, vector<int> PCells, int gc, int &fes, double beta, int max_Gc);
void crecimientoQCell(vector<int> hPcells, vector<int> cPCells, vector<int> &QCells, int prolCells, int gc, int &fes, double beta, int max_Gc);
void crecimientoDCell(vector<int> cPCells, int tamPCells, vector<int> QCells, vector<int> &DCells, int gc, int &fes, int max_Gc);
void cellInvasivas(vector<int> &cPCells, int tamPCells, vector<int> DCells, int gc, int &fes, int max_Gc);
void randomWalk(Celulas &cell, int fes);//return gc actualiza cell
#endif