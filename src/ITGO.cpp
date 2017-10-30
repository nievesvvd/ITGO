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

    
    
    bestFitness.resize(tamPob);
    best.resize(tamPob+1);
    gc.resize(tamPob);
    
    //generamos una poblacion de forma aleatoria dado un tam determinado
    generarPoblacion(tamPob, dim);//el fitness buscamos el minimo posible
    while(fes<max_fes){
        sort(nutrientes.begin(), nutrientes.end());  //ordenamos las celulas segun su nivel de nutrientes de menos a mayor
        separarPoblacion(PCells, QCells, DCells, tamPob);//20/60/20
        actualCell=nutrientes[0].first;//la primera vez establecemos la mejor celula como la 1 de mejor fitness
        bestCell=actualCell;

        // movimientoCelulas(cCells, hCells, nutrientes, gc, bestFitness);
        movePCells(PCells, gc, fes, max_Gc, max_fes);
        moveQCells(PCells, QCells, gc, fes, max_Gc, max_fes);
        moveDCells(PCells, QCells, DCells, gc, fes, max_Gc);

        cout << "--------------------hasta aqui-----------------" << endl;

        cellInvasivas(tamPob, fes);
        cout << "--------------------INVASIVAS-----------------" << endl;
      
        //establecemos la mejor celula
        actualCell=mejorCelula();
        if(actualCell < bestCell){
            bestCell=actualCell;
        }
        //actualizarPoblacion(PCells, QCells, DCells);//????
        fes++;
    }
    hCells[bestCell].swap(best);
    best.push_back(nutrientes[bestCell].second);
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
    newCells.resize(nutrientes.size());
    distancias.resize(QCells);
    //qCell=nutrientes.size()*0.6+pCell;
    begin = PCells;
    end = begin+QCells-1;
    
    for(int i=0; i<QCells; i++){
        randPCell=Randint(0, (nutrientes.size()*0.2)-1);
        distanciaEuclidea(QCells, distancias, begin, end);
        cellCercanas(QCells, proxima1, proxima2, distancias);
        stp=(float)step();
        bta=(float)beta();
        //move=step();
        for(unsigned int j=0; j<cCells[0].size(); j++){
            mute=Randfloat(0, 1.8);
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
    newCells.resize(nutrientes.size());

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
    cout << "pre for" << endl;
    for(int i=0; i<tamPob; i++){ //TODO modificar este for pra que recorr el conjunto de cel apropiado para poder sumar pcell +i
        randPCell=Randint(0, (nutrientes.size()*0.2)-1);
        med=mediaNutrientes(Dpos, tamPob*0.2);
        cout << "calculamos la media con i= " << i << endl;
        if(nutrientes[Dpos+i].second<med){
            newCells=generarSolucion(nutrientes.size());//generamos un vector del tam de las cells
            cout << "generamos la solucioncon i= " << i << endl;
            for(int j=0; j<nutrientes[0].first; j++){
                ICells[j] = cCells[nutrientes[randPCell].first][j] +
                rand()*( newCells[j]-cCells[nutrientes[randPCell].first][j] ); ///!!!!
                cout << "ICells[j]=" << ICells[j] << endl;
            }

            //actualizarCelula(newCells, i+Dpos, nutrientes.second[i+Dpos] );
            fit=fitness(ICells);
            cout << "actualizamos fitness" << endl;
            fes++;
            cout << "[i+Dpos]=" << i+Dpos << endl;
            if(fit<nutrientes[i+Dpos].second){
                cout << "[i+Dpos]=" << i+Dpos << endl;
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
    if(fit < nutrientes[cell].second){
        cCells[cell]=movedCell;
        gc=0;
    }
}