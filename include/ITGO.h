#ifndef ITGO_H
#define ITGO_H

#include <vector.h>
#include "funciones.h"

using namespace std;
/**
*Struct que guarda la informacion que tiene cada una de las celculas:
* el tipo (P,Q,D,I)
* el numero de nutrientes (0-100)porcentual 
* el tamaño de la celula, gc
**/
struct Celulas{
    int id;
    char tipo;
    int nutrientes;
    double gc;

    Celulas(int n, char type, int nutr, double gc) : id(n), tipo(type, nutrientes(nutr), gc(gc)){}

    bool operator < (const Celulas& cell) const{
        return(nutrientes < cell.nutrientes);
    }
};

/**Struct que guarda la informacion de las posciones guardadas en el historico de la celulas
* posX de la celula
* posY de la celula
* nutrientes restantes que tienen actualmente
**/
struct Historico{
    int posX;
    int posY;
    int nutrients;
    int id;
}

Celulas algoritmoITGO(double beta, int Dist, int tam, double max_fes);
vector<Celulas> crecimientoPCell(vector<Celulas> &hCells, vector<Celulas> PCells, double gc, double &fes, double beta, double max_Gc);
void crecimientoQCell(vector<Celulas> hPcells, vector<Celulas> cPCells, vector<Celulas> &QCells, int prolCells, double gc, double &fes, double beta, double max_Gc);
void crecimientoDCell(vector<Celulas> cPCells, int tamPCells, vector<Celulas> QCells, vector<Celulas> &DCells, double gc, double &fes, double max_Gc);
void cellInvasivas(vector<Celulas> &cPCells, int tamPCells, vector<Celulas> DCells, double gc, double &fes, double max_Gc);
void randomWalk(Celulas &cell, double fes);//return gc actualiza cell
#endif