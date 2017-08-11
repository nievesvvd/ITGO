#include <vector>
#include <iostream>
#include "ITGO.h"

using namespace std;

struct Celulas{
    char tipo;
    int nutrientes;
}

void algoritmoITGO(int tam){
    vector<Celulas> PCells;
    vector<Celulas> QCells,
    vector<Celulas> DCells;
    vector<Celulas> poblacionIni;
    Celulas bestCell;
    //fes=0
    //generamos una poblacion de forma aleatoria dado un tam determinado
    pobacionIni = generarPoblacion(int tam);

    while(/*fes<max_fes & iteraciones > max iter*/){
        //ordenamos la poblacion en funcion del valor de fitness(ascending)
        ordenarPoblacion(poblacionIni);
        separarPoblacion(PCells, QCells, DCells);
        //pasos de algoritmo
        crecimientoPCell(PCells, gc, fes, beta, max_gc);
        crecimientoQCell(QCells);
        crecimientoDCell(DCells);
        crecimientoInvasiveCell(PCells, DCells);
        //establecemos la mejor celula
    }
}

/*A continuacion se pondran los metodos de los 4 tipos de celulas*/
void crecimientoPCell(PCells, gc, fes, beta, max_gc){
    Celulas = bestPCell, newPCell;
    for(int i=0; i<PCells.size(); i++){
        for(int j=0; j<1000; j++){ 
            newPCells(i,j)=PCells(i,j)+alpha(fes, max_fes)*levy(lamda);

        }
        //calculamos la evaluacion de fitness de newpcell
        fes++;
        if (newPCell.nutrientes > bestPCell.nutrientes){
            bestPCell = newPCell;
        }else{
            hPCell = PCell(i);
            Gc(i) Gc(i)+1;
        }
        if (Gc(i) > max_gc){
            randomWalk(cPCell(i), Gc(i));
        }
    }
}
