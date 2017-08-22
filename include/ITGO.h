#ifndef ITGO_H
#define ITGO_H

#include <vector.h>
#include "funciones.h"

using namespace std;

struct Celulas{
    char tipo;
    int nutrientes;
    double gc;
};

Celulas algoritmoITGO(double beta, int Dist, int tam, double max_fes);
vector<Celulas> crecimientoPCell(vector<Celulas> &hCells, vector<Celulas> PCells, double gc, double &fes, double beta, double max_Gc);
void crecimientoQCell(vector<Celulas> hPcells, vector<Celulas> cPCells, vector<Celulas> &QCells, int prolCells, double gc, double &fes, double beta, double max_Gc);
void crecimientoDCell(vector<Celulas> cPCells, int tamPCells, vector<Celulas> QCells, vector<Celulas> &DCells, double gc, double &fes, double max_Gc);
void cellInvasivas(vector<Celulas> &cPCells, int tamPCells, vector<Celulas> DCells, double gc, double &fes, double max_Gc);
void randomWalk(Celulas &cell, double fes);//return gc actualiza cell
#endif