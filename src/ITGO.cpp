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

        // movimientoCelulas(cCells, hCells, nutrientes, gc, bestFitness);
        movePCells();
        moveQCells();
        moveDCells();

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
movePCells(){
    float stp=0.0, move=0.0, fit=0.0;
    for(int i=0; i<PCells; i++){
        for(int j=0; j<poblacionIni[0].size(); j++){
            stp=step();
            move=levy(stp);
            cCells[nutrientes.first[i]][j]= cCells[nutrientes.first[i]][j]+alpha()*move;
            fit=fitness(cCells[i]);
        }
        if(fit<nutrientes.second[i]){
            bestFitness[nutrientes.first[i]] = fit;
            hCells[nutrientes.first[i]][j]= cCells[nutrientes.first[i]][j];//en hCell guardo el nuevo valor si es mejor
        }else{
            gc[nutrientes.first[i]]++;
        }
        if(gc[nutrientes.first[i]]>max_Gc){
            randomWalk(cCells[nutrientes.first[i]], gc[nutrientes.first[i]]);
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