#include <vector>
#include <iostream>
#include "ITGO.h"

using namespace std; 


vector<double> algoritmoITGO(double beta, int dim, int tamPob, int max_fes){
    Celula nutrientes;

    vector<vector<float> > cCells;
    vector<vector<float> > hCells;
    vector<float> bestFitness;
    vector<int> gc;

    int PCells=tamPob*0.2;  //vector con los id de las PCells
    int QCells=tamPob*0.6;  //vector con los id de las QCells
    int DCells=tamPob*0.2;  //vector con los id de las DCells

    int bestCell, actualCell;   //guarda el id de la mejor celula
    int fes=0;
    int max_Gc=0.7*dim;

    nutrientes.first.resize(tamPob);
    bestFitness.resize(tamPob);
    gc.resize(tamPob);
 
    //generamos una poblacion de forma aleatoria dado un tam determinado
    generarPoblacion(cCells, hCells, nutrientes, tamPob, dim);//el fitness buscamos el minimo posible
    while(fes<max_fes){
        nutrientes.sort();  //ordenamos las celulas segun su nivel de nutrientes de menos a mayor

        separarPoblacion(nutrientes, PCells, QCells, DCells);//20/60/20
      
        actualCell=nutrientes[tamPob-1];//la primera vez establecemos la mejor celula como la 1 de mejor fitness
        bestCell=actualCell;

        movimientoCelulas(cCells, hCells, nutrientes, gc, bestFitness);

        cellInvasivas(PCells, DCells);        
        //establecemos la mejor celula
        actualCell=mejorCelula(PCell);
        if(actualCell < bestCell){
            bestCell=actualCell;
        }
        actualizarPoblacion(poblacionIni, PCells, QCells, DCells);
        fes++;
    }
    return poblacionIni[bestCell[0]];
}

/*A continuacion se pondran los metodos de los 4 tipos de celulas*/

void movimientoCelulas(cCells, hCells, nutrientes, gc, bestFitness, max_Gc){
    pCell=nutrientes.first.size()*0.2;
    qCell=nutrientes.first.size()*0.6+pCell;
    vector<float> vuelo;
    vuelo.resize(nutrientes.first.size());

    for(int i=0; i<nutrientes.first.size(); i++){
        for(int j=0; j<poblacionIni[0].size(); j++){
            if(i < pCell){//pcells
                //levy fligh
                fit=fitness();
                if(fit<nutrientes.second[i]){
                    bestFitness[i] = fit;
                    vuelo.swap(hCells[nutrientes.first[i]]);//en hCell guardo el nuevo valor si es mejor
                }else{
                    vuelo.swap(cCells[nutrientes.first[i]]);//en cCell guardo el nuevo valor
                    gc[i]++;
                }
                if(gc[i]>max_Gc){
                    randomWalk(cCells[nutrientes.first[i]], gc[i]);
                }
            }else if(i>=pCell && i<=qCell){//qcells

            }else{//dcells

            }
        }
    }
}

/** InvasiveCells es el conjunto de las celulas invasivas
**  Gc es el valor del ciclo de crecimiento de las celulas
**  fes es el valor de fitness evalation consumido
**  beta parametro de levy
**  Max_Gc es el valor de crecimiento maximo de la celula
**/
void cellInvasivas(cPCells, prolCells, DCells, gc, fes, max_Gc){
    double valorMedio=0.0;
    int posDCell=0;
    Celulas iCell, newCell;
    valorMedio=mediaFitness(DCells);
    for(int i=0; i<DCell.size(); i++){
        posDCell= Randint(0, DCells.size()-1);
        newCell=Randint(0, D);
        if(DCells[i].nutrientes < valorMedio){
            for(int j=0; j<D; j++){
                iCell[i,j]=cPCells[i,j]+rand(newCell[1,j]-cPCells[i,j]);//formula 14
            }
            fitness(iCell[i], iCell[i].gc, iCell[i].nutrientes);
            fes++;
            if(iCell[i].nutrientes > x){
                DCell[i] = iCell[i]; //formula 15
            }
        }
    }
}

/*
* cell : cualquier celula de la poblacion
* gc   : su valor de crecimiento
* fes  : numero de nutrientes consumidos 
*/
void randomWalk(cell, fes){
    Celulas newCell, nowCell;
    int pos=0;
    pos = Randint(1,D);
    newCell=cell+a*nowCell/(nowCell*nowCellp);//form 16
    fitness(newCell);
    fes++;
    if(newCell.nutrientes > cell.nutrientes){
        cell=newCell;
        gc=0;
    }
}