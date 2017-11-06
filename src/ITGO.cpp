#include <vector>
#include "ITGO.h"
#include <iostream>

using namespace std; 

vector<float> algoritmoITGO(/*double beta,*/ int dim, int tamPob, int max_fes){
    vector<int> gc;
    vector<float> best;

    int PCells=tamPob*0.2;  //vector con los id de las PCells
    int QCells=tamPob*0.6;  //vector con los id de las QCells
    int DCells=tamPob*0.2;  //vector con los id de las DCells

    int bestCell = 0, actualCell;   //guarda el id de la mejor celula
    int fes=0;
    int max_Gc=0.7*dim;

    
    
    //bestFitness.resize(tamPob);
    best.resize(dim+1);//valor donde guardamos la celula mejor
    gc.resize(tamPob,0);
    
    //generamos una poblacion de forma aleatoria dado un tam determinado
    generarPoblacion(tamPob, dim);//el fitness buscamos el minimo posible
    //cout << "no llega fijo" << endl;
    while(fes<max_fes){
        sort(nutrientes.begin(), nutrientes.end());  //ordenamos las celulas segun su nivel de nutrientes de menos a mayor
        sort(bestFitness.begin(), bestFitness.end());    //ordenamos las celulas segun su nivel de nutrientes de menos a mayor
        separarPoblacion(PCells, QCells, DCells, tamPob);//20/60/20
       // cout << "separa pobl" << endl;
        actualCell=bestFitness[0].first;//la primera vez establecemos la mejor celula como la 1 de mejor fitness
        bestCell=actualCell;

        // movimientoCelulas(cCells, hCells, nutrientes, gc, bestFitness);
        movePCells(PCells, gc, fes, max_Gc, max_fes);
        //cout << "pcell" << endl;
        moveQCells(PCells, QCells, gc, fes, max_Gc, max_fes);
        //cout << "qcell" << endl;
        moveDCells(PCells, QCells, DCells, gc, fes, max_Gc);
        //cout << "dcell" << endl;

        cellInvasivas(tamPob, fes);
      
        //establecemos la mejor celula
        actualCell=mejorCelula();
        if(fitness(hCells[actualCell]) <= bestFitness[0].second){
            bestCell=actualCell;
        }
        //actualizarPoblacion(PCells, QCells, DCells);//????
        fes++;
    }
    hCells[bestCell].swap(best);
    best.push_back(bestFitness[bestCell].second);
    return best;
}

/*A continuacion se pondran los metodos de los 4 tipos de celulas*/
void movePCells(int PCells, vector<int> &gc, int &fes, int max_Gc, int max_fes){
    float stp=0.0, move=0.0;
    bool walk=false;
    //pCell=nutrientes.size()*0.2;
    //vuelo.resize(nutrientes.first.size());
    vector<float> newCells;
    newCells.resize(cCells[0].size());

    for(int i=0; i<PCells; i++){
        for(unsigned int j=0; j<cCells[0].size(); j++){
            stp=step();
            move=levy(stp);
            newCells[j]= cCells[nutrientes[i].first][j]+alpha(fes, max_fes)*move;
        }
        walk=actualizarCelula(newCells, i, nutrientes[i].second, gc[i], fes, max_Gc);
        if(walk){
            randomWalk(i, gc[i]);
        }
        newCells.clear();
        newCells.resize(cCells[0].size());
    }
}

void moveQCells(int PCells, int QCells, vector<int> &gc, int &fes, int max_Gc, int max_fes){
    vector<Distancias> distancias;
    float stp=0.0, bta=0.0, mute=0.0;
    int randPCell, proxima1, proxima2;
    int begin, end;
    bool walk=false;
    vector<float> newCells;
    newCells.resize(cCells[0].size());
    distancias.resize(QCells);
    //qCell=nutrientes.size()*0.6+pCell;
    begin = PCells;
    end = begin+QCells-1;
    
    for(int i=0; i<QCells; i++){
        randPCell=Randint(0, (nutrientes.size()*0.2)-1);
        distanciaEuclidea(QCells, distancias, begin, end);
        //cout << "Distancia Euc" << endl;
        cellCercanas(QCells, proxima1, proxima2, distancias);
        //cout << "cell cercana" << endl;
        stp=(float)step();
        bta=(float)beta();
        //move=step();
        for(unsigned int j=0; j<cCells[0].size(); j++){
            mute=Randfloat(0, 1.8);
            //cout << "Mute:" << mute << endl;
            if(mute > exp(fes/max_fes-1)){
            //se produce la mutacion
                if(rand()<= 0.5){
                    newCells[j] = cCells[nutrientes[i+PCells].first][j]+(bta*stp*
                        (hCells[nutrientes[randPCell].first][j]-cCells[nutrientes[i].first][j]) )+
                        (bta*stp*(cCells[nutrientes[proxima1].first][j])-cCells[nutrientes[proxima2].first][j]) ;
                }else{
                    newCells[j] = cCells[nutrientes[i+PCells].first][j]+ (bta*stp*
                        ( cCells[nutrientes[randPCell].first][j] - cCells[nutrientes[i+PCells].first][j]) )+
                        (bta*stp*(cCells[nutrientes[proxima1].first][j]- cCells[nutrientes[proxima2].first][j]) );
                }
            }
        }
        walk=actualizarCelula(newCells, i+PCells, nutrientes[i+PCells].second, gc[i+PCells], fes, max_Gc);
        //cout<< "Actualiza cell" << endl;
        if(walk){
            randomWalk(i+PCells, gc[i+PCells]);
        }
        newCells.clear();
        newCells.resize(cCells[0].size());
    }
}

void moveDCells(int PCells, int QCells, int DCells, vector<int> &gc, int &fes, int max_Gc){
    int randPCell, randQCell;
    vector<float> newCells;
    bool walk=false;
    float y;
    y = Randfloat(-1, 1.1);
    newCells.resize(cCells[0].size());

    for(int i=0; i<DCells; i++){
        randPCell=Randint(0, (nutrientes.size()*0.2)-1);
        randQCell=Randint((nutrientes.size()*0.2)-1, (nutrientes.size()*0.6)-1);
        for(unsigned int j=0; j<cCells[0].size(); j++){
            newCells[j]=cCells[nutrientes[PCells+QCells+i].first][j] + 
            y * (cCells[nutrientes[randPCell].first][j] - cCells[nutrientes[PCells+QCells+i].first][j] ) +
            y * (cCells[nutrientes[randQCell].first][j] - cCells[nutrientes[PCells+QCells+i].first][j] );
        }
        walk=actualizarCelula(newCells, i+PCells+QCells, nutrientes[i+PCells+QCells].second, gc[i+PCells+QCells], fes, max_Gc);
        if(walk){
            randomWalk(i+PCells+QCells, gc[i+PCells+QCells]);
        }
        newCells.clear();
        newCells.resize(cCells[0].size());
    }
}

/** InvasiveCells es el conjunto de las celulas invasivas
**  Gc es el valor del ciclo de crecimiento de las celulas
**  fes es el valor de fitness evalation consumido
**  beta parametro de levy
**  Max_Gc es el valor de crecimiento maximo de la celula
**/
void cellInvasivas(int tamPob, int &fes){
    int randPCell, Dpos;
    float med=0.0, fit=0.0;
    Dpos = tamPob - tamPob*0.2;//pos de la primera cell del conjunto DCell
    vector<float> newCells, ICells;
    newCells.resize(nutrientes.size());
    ICells.resize(nutrientes.size());
    for(int i=0; i<tamPob*0.2; i++){ //TODO modificar este for pra que recorr el conjunto de cel apropiado para poder sumar pcell +i
        randPCell=Randint(0, (nutrientes.size()*0.2)-1);
        med=mediaNutrientes(Dpos, tamPob*0.2);
        if(nutrientes[Dpos+i].second<med){
            newCells=generarSolucion(nutrientes.size());//generamos un vector del tam de las cells
            for(int j=0; j<nutrientes[0].first; j++){
                ICells[j] = cCells[nutrientes[randPCell].first][j] +
                rand()*( newCells[j]-cCells[nutrientes[randPCell].first][j] ); ///!!!!
            }

            //actualizarCelula(newCells, i+Dpos, nutrientes.second[i+Dpos] );
            fit=fitness(ICells);
            fes++;
            if(fit<bestFitness[i+Dpos].second){
                hCells[i+Dpos].swap(ICells);
                cCells[i+Dpos].swap(ICells);
                nutrientes[i+Dpos].second = fit;
                bestFitness[i+Dpos].second = fit;
            }else{
                cCells[i+Dpos].swap(ICells);
                nutrientes[i+Dpos].second = fit;
            }
        }
    }
}

/*
* cell : cualquier celula de la poblacion
* gc   : su valor de crecimiento
* fes  : numero de nutrientes consumidos 
*/
void randomWalk(int cell, int &gc){
    vector<float> newCell, movedCell;
    float alpha=0.0, fit;
    alpha = Randfloat(-1, 1.1);

    newCell.resize(nutrientes.size());
    movedCell.resize(nutrientes.size());

    newCell=generarSolucion(nutrientes.size());

    for(unsigned int i=0; i<nutrientes.size(); i++){
        movedCell[i]=cCells[cell][i]+alpha*newCell[i]/(newCell[i]*newCell[i]);//form 16
    }
    fit=fitness(movedCell);
    if(fit < bestFitness[cell].second){
        cCells[cell].swap(movedCell);
        hCells[cell].swap(movedCell);
        nutrientes[cell].second = fitness(movedCell);
        bestFitness[cell].second = fitness(movedCell);
        gc = 0;
    }
}