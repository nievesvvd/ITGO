#include <vector>
#include <iostream>
#include "ITGO.h"

using namespace std; 

vector<float> algoritmoITGO(double beta, int dim, int tamPob, int max_fes){
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
    generarPoblacion(tamPob, dim);//el fitness buscamos el minimo posible
    while(fes<max_fes){
        nutrientes.sort();  //ordenamos las celulas segun su nivel de nutrientes de menos a mayor

        separarPoblacion(PCells, QCells, DCells);//20/60/20
      
        actualCell=nutrientes[0];//la primera vez establecemos la mejor celula como la 1 de mejor fitness
        bestCell=actualCell;

        // movimientoCelulas(cCells, hCells, nutrientes, gc, bestFitness);
        movePCells(PCells, gc, fes);
        moveQCells(PCells, QCells, gc, fes);
        moveDCells(PCells, QCells, DCells, gc, fes);
        
        cellInvasivas(tamPob);
      
        //establecemos la mejor celula
        actualCell=mejorCelula(PCell);
        if(actualCell < bestCell){
            bestCell=actualCell;
        }
        //actualizarPoblacion(PCells, QCells, DCells);//????
        fes++;
    }
    return poblacionIni[bestCell];
}

/*A continuacion se pondran los metodos de los 4 tipos de celulas*/
void movePCells(int PCells, vector<int> &gc, int &fes){
    float stp=0.0, move=0.0, fit=0.0;
    pCell=nutrientes.first.size()*0.2;
    vuelo
    vuelo.resize(nutrientes.first.size());
    newCells.resize(poblacionIni[0].size());

    for(int i=0; i<PCells; i++){
        for(int j=0; j<poblacionIni[0].size(); j++){
            stp=step();
            move=levy(stp);
            newCells[j]= cCells[nutrientes.first[i]][j]+alpha()*move;
        }
        actualizarCelula(newCells, i, nutrientes.second[i], gc[i], fes);
        newCells.clear();
        newCells.resize(poblacionIni[0].size());
    }
}

void moveQCells(int PCells, int QCells, vector<int> &gc, int &fes){
    float stp=0.0, move=0.0, fit=0.0, beta=0.0;
    int randPCell, proxima1, proxima2;
    vector<float> newCells;
    newCells.resize(nutrientes.first.size());
    qCell=nutrientes.first.size()*0.6+pCell;
    
    for(int i=0; i<QCells; i++){
        randPCell=Randint(0, (nutrientes.first.size()*0.2)-1);
        distanciaEuclidea(QCells, poblacionIni, proxima1, proxima2);
        //faltan los pasos
        beta=beta();
        move=step(beta);
        for(int j=0; j<poblacionIni[0].size(); j++){
            mute=Randfloat(0, 1.8);
            if(mute > exp(fes/Max_fes-1)){
            //se produce la mutacion
                if(rand()<= 0.5){
                    newCells[j] = cCells[nutrientes.first[i+PCells]][j]+(beta*stp*
                        (hCells[nutrientes.first[randPCell]][j]-cCells[nutrientes.first[i]][j]) )+
                        (beta*stp*(cCells[nutrientes.first[proxima1]][j])-cCells[nutrientes.first[proxima2]][j]) ) );
                }else{
                    newCells[j] = cCells[nutrientes.first[i+PCells]][j]+ (beta*stp*
                        ( cCells[nutrientes.first[randPCell]][j] - cCells[nutrientes.first[i+PCells]][j]) )+
                        (beta*stp*(cCells[nutrientes.first[proxima1]][j]- cCells[nutrientes.first[proxima2]][j]) );
                }
            }
        }
        actualizarCelula(newCells, i+PCells, nutrientes.second[i+PCells], gc[i+PCells], fes);
        newCells.clear();
        newCells.resize(poblacionIni[0].size());
    }
}

void moveDCells(int PCells, int QCells, int DCells, vector<int> &gc, int &fes){
    int randPCell, randQCell;
    vector<float> newCells;
    float y;
    y = Randfloat(-1, 1.1);
    newCells.resize(nutrientes.first.size());

    for(int i=0; i<DCells; i++){
        ranPCell=Randint(0, (nutrientes.first.size()*0.2)-1);
        ranQCell=Randint((nutrientes.first.size()*0.2)-1, (nutrientes.first.size()*0.6)-1);
        for(int j=0; j<poblacionIni[0].size(); j++){
            newCells[j]=cCells[nutrientes.first[PCells+QCells+i]][j] + 
            y * (cCells[nutrientes.first[randPCell]][j] - cCells[nutrientes.first[PCells+QCells+i]][j] ) +
            y * (cCells[nutrientes.first[randQCell]][j] - cCells[nutrientes.first[PCells+QCells+i]][j] );
        }
        actualizarCelula(newCells, i+PQCells+QCells, nutrientes.second[i+PQCells+QCells], gc[i+PCells+QCells]);
        newCells.clear();
        newCells.resize(poblacionIni[0].size());
    }
}

/** InvasiveCells es el conjunto de las celulas invasivas
**  Gc es el valor del ciclo de crecimiento de las celulas
**  fes es el valor de fitness evalation consumido
**  beta parametro de levy
**  Max_Gc es el valor de crecimiento maximo de la celula
**/
void cellInvasivas(int tamPob){
    int randPCell, Dpos, pos=0;
    float med=0.0, fit=0.0;
    Dpos = tamPob - tamPob*0.2;//pos de la primera cell del conjunto DCell
    vector<float> newCells, ICells;
    newCells.resize(nutrientes.first.size());
    ICells.resize(nutrientes.first.size());

    for(int i=0; i<tamPob; i++){
        ranPCell=Randint(0, (nutrientes.first.size()*0.2)-1);
        med=mediaNutrientes(Dpos, tamPob*0.2);
        if(nutrientes.second[Dpos+i]<med){
            newCells=generarSolucion(nutrientes.first.size());//generamos un vector del tam de las cells
            for(int j=0; j<nutrientes.first[0]; j++){
                ICells[i][j] = cCells[nutrientes.first[randPCell]][j] + 
                rand()*( newCells[i]][j]-cCells[nutrientes.first[randPCell]][j] ); ///!!!!
            }

            //actualizarCelula(newCells, i+Dpos, nutrientes.second[i+Dpos] );
            fit=fitness(ICells);
            fes++;
            if(fit<nutrientes.second[i+Dpos]){
                cCells.first[i+Dpos] = ICells;
                cCells.second[i+Dpos] = fit;
            }
        }
    }
}

/*
* cell : cualquier celula de la poblacion
* gc   : su valor de crecimiento
* fes  : numero de nutrientes consumidos 
*/
void randomWalk(cell, gc){
    vector<float> newCell, movedCell;
    float alpha=0.0, fit;
    alpha = randFloat(-1, 1.1);

    newCell.resize(nutrientes.first.size());
    movedCell.resize(nutrientes.first.size());

    newCell=generarSolucion(nutrientes.first.size());

    for(int i=0; i<nutrientes.fisrt.size(); i++){
        movedCell[i]=cCells[cell][i]+alpha*newCell[i]/(newCell[i]*newCell[i]);//form 16
    }
    fit=fitness(movedCell);
    if(fit < nutrientes.second[cell]){
        cCells[cell]=movedCell;
        gc[cell]=0;
    }
}