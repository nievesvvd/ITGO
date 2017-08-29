#include <vector>
#include <iostream>
#include "ITGO.h"

using namespace std;


Celulas algoritmoITGO(double beta, int dim, int tamPob, int max_fes){
    vector<int> PCells;         //vector con los id de las PCells
    vector<int> QCells,         //vector con los id de las QCells
    vector<int> DCells;         //vector con los id de las DCells
    vector<vector<int> > poblacionIni;   //vector con la poblacion inicial
    vector<vector<int> > besPost;
    vector<vector<Historico> > hCells;  //matriz que guarda el historico de cada celula donde la primera columna tiene a la poblacion y las filas las mejores pos de cada celula
    int bestCell;//guarda el id de la mejor celula
    int fes=0;
    int max_Gc=0.7*dim;
    //generamos una poblacion de forma aleatoria dado un tam determinado
    
    //pobacionIni = generarPoblacion(tam);
    //fes+=poblacionIni.size();
    



    while(fes<max_fes /*& iter_act > iteraciones*/){
        //ordenamos la poblacion en funcion del valor de fitness(ascending)
        ordenarPoblacion(poblacionIni);
        separarPoblacion(poblacionIni, PCells, QCells, DCells);
        //pasos de algoritmo
        cPCells = crecimientoPCell(hCells, PCells, gc, fes, beta, max_Gc);//20%
        crecimientoQCell(hPcells, cPCells, QCells, prolCells, gc, fes, beta, max_Gc);//60%
        crecimientoDCell(cPCells, prolCells, QCells, DCells, gc, fes, max_Gc); //20%
        cellInvasivas(PCells, DCells);        
        //establecemos la mejor celula
        actualizarPoblacion(poblacionIni, PCells, QCells, DCells);
    }
    //return the global best cell in population
}

/*A continuacion se pondran los metodos de los 4 tipos de celulas*/


/** PCells es el conjunto de las celulas proliferativas
**  Gc es el valor del ciclo de crecimiento de las celulas
**  fes es el valor de fitness evalation consumido
**  beta parametro de levy
**  Max_Gc es el valor de crecimiento maximo de la celula
**/
vector<Celulas> crecimientoPCell(hCells, PCells, gc, fes, beta, max_Gc){
    Celulas = bestPCell;
    vector<vector<Celulas> > posProliferativas;
    vector<Celulas> hPCells, cPCells;
    vector<Celulas> newPCells;
    for(int i=0; i<PCells.size(); i++){
        for(int j=0; j<dim; j++){ 
            newPCells[i,j]=PCells[i,j]+alpha(fes, max_fes)*levy(beta);
        }
        //calculamos la evaluacion de fitness de newpcell
        fitness(newPCells[i]);
        fes++;
        //si el valor de fitness de la nueva cell es mejor, lo guardamos en el vector de sub prof cell popul
        if (newPCells.nutrientes[i] > bestPCell.nutrientes){
            cPCells[i] = newPCells[i];
        }else{
        //si no, lo guardamos en el historico
            hPCells[i] = PCells[i];
            PCells.gc[i] = PCells.gc[i]+1;
        }
        if (PCells.gc[i] > max_gc){
            randomWalk(cPCells[i], cPCells.gc[i]);
        }
    } 
    return hPCell;//devolver tambien cPCells
}


/** QCells es el conjunto de las celulas semi activas
**  Gc es el valor del ciclo de crecimiento de las celulas
**  fes es el valor de fitness evalation consumido
**  beta parametro de levy
**  Max_Gc es el valor de crecimiento maximo de la celula
**/
void crecimientoQCell(hPcells, cPCells, QCells, prolCells, gc, fes, beta, max_Gc){
    int posCell;
    double value;
    double bestFitness;
    vector<Celulas> cercanas;
    Celula proxima1, proxima2, newQCell;
    for(int i=0; i<QCells.size(), i++){
        posCell= Randint(0, QCells.size()-1);
        //seleccionar x celula de donde sea
        cercanas = disstanciaEuclidea(QCells, QCells[i]);//devolver posicion o celula????
        proxima1 = cercanas[0];
        proxima2 = cercanas[1];
        //levy flight 
        //step size

        //movimiento de la celula, ira a pcell o qcell teniendo en cuenta que x e y son las vecinas
        //formulae 9 and 11 para el movimiento y Beta vvvv
        for(j=0; j<dim; j++){
            value = Rand();
            if (value < 0.5){
                newQCell = QCells[i,j]+b*step*(hPCells[p,j]-QCells[i,j])+b*step*(QCells[x,j]-QCells[y,j]);
                bestFitness = fitness(newQCell);
            }else{
                newQCell = QCells[i,j]+b*step*(cPCells[p,j]-QCells[i,j])+b*step*(QCells[x,j]-QCells[y,j]);
                bestFitness = fitness(newQCell);
            }
        }

        //vemos si la celula mutara o no
        for(int k=0; k<dim; k++){
            value=Rand();
            if(value < exp(fes/max_fes -1)){
                newQCell[i,k]=QCells[i,k];
            }
        }
        fitness(newQCell[i]);
        fes++;
        if(newQCells.nutrientes[i]>bestFitness){
            //QCells[i] = actualizamos el valor de qcells
        }else{
            gc(Psize+i) = gc(prolCells+i)+1;
        }
        if(gc(Psize+i)>max_Gc){
            randomWalk(QCells[i], QCells.gc[prolCells+1]);
        }
    }
}

/** DCells es el conjunto de las celulas semi muertas
**  Gc es el valor del ciclo de crecimiento de las celulas
**  fes es el valor de fitness evalation consumido
**  beta parametro de levy
**  Max_Gc es el valor de crecimiento maximo de la celula
**/

void crecimientoDCell(cPCells, prolCells, QCells, DCells, gc, fes, max_Gc){
    int posQCell, posPCell;
    double bestFitness;
    Celulas newDCells;
    for(int i=0; i<DCells.size(); i++){
        posQCell= Randint(0, QCells.size()-1);
        posPCell= Randint(0, PCells.size()-1);
        for(int j=0; j<D; j++){
            newDCells[i,j] = DCells[i,j]+y*(cPCells[posPCell,j]-DCells[i,j])+y*(QCells[posQCell, j]-DCells[i,j]);//nutrientes?? form12
        }
        fitness(newDCells[i]);
        fes++;
        if(newDCells[i].nutrientes>x){
            //actualizamos el valor
        }else{
            Gc(Psize+Qsize+i)= Gc(Psize+Qsize+i)+1;
        }
        if(Gc(Psize+Qsize+i)>max_Gc){
            randomWalk(DCells[i], Gc(Psize+Qsize+i));
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