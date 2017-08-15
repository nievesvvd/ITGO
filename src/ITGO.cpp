#include <vector>
#include <iostream>
#include "ITGO.h"

using namespace std;

#define Dist=1000;

Celulas algoritmoITGO(int tam, double max_fes){
    vector<Celulas> PCells;
    vector<Celulas> QCells,
    vector<Celulas> DCells;
    vector<Celulas> poblacionIni;
    vector<Celulas> hCells, cPCells;
    Celulas bestCell, actualCell;
    int iter_act=0, iteraciones=30000;
    double fes=0.0;
    //generamos una poblacion de forma aleatoria dado un tam determinado
    pobacionIni = generarPoblacion(int tam);
    fes+=poblacionIni.size();

    while(fes<max_fes & iter_act > iteraciones){
        //ordenamos la poblacion en funcion del valor de fitness(ascending)
        ordenarPoblacion(poblacionIni);
        separarPoblacion(PCells, QCells, DCells);
        //pasos de algoritmo
        cPCells = crecimientoPCell(&hCells, PCells, gc, fes, beta, max_gc);                    //20%
        crecimientoQCell(hPcells, cPCells, QCells, prolCells, gc, fes, beta, max_Gc);//60%
        crecimientoDCell(DCells);                                                    //20%
        crecimientoInvasiveCell(PCells, DCells);        
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
vector<Celulas> crecimientoPCell(PCells, gc, fes, beta, max_Gc){
    Celulas = bestPCell;
    vector<vector<Celulas> > posProliferativas;
    vector<Celulas> hPCells, cPCells;
    vector<Celulas> newPCells;
    for(int i=0; i<PCells.size(); i++){
        for(int j=0; j<Dist; j++){ 
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



void crecimientoQCell(hPcells, cPCells, QCells, prolCells, gc, fes, beta, max_Gc){
    int posCell;
    double value;
    vector<Celulas> cercanas;
    Celula proxima1, proxima2, newQCell;
    for(int i=0; i<QCells.size(), i++){
        posCell= Randint(0, QCells.size()-1);
        //seleccionar x celula de donde sea
        cercanas = distanciaEuclidea(QCells, QCells[i]);//devolver posicion o celula????
        proxima1 = cercanas[0];
        proxima2 = cercanas[0];
        //levy flight 
        //step size
        for(j=0; j<Dist; j++){
            value = Rand();
            if (value < 0.5){
                newQCell = QCells[i,j]+b*step(hPCells[p,j]-QCells[i,j])+b*step(QCells[x,j]-QCells[y,j]);
            }else{
                newQCell = QCells[i,j]+b*step(cPCells[p,j]-QCells[i,j])+b*step(QCells[x,j]-QCells[y,j]);
            }
            //formulae 9 and 11
        }
        for(int k=0; k<Dist; k++){
            value=Rand();
            if(value < exp(fes/max_fes -1)){
                newQCell[i,k]=QCells[i,k];
            }
        }
        fitness(newQCell[i]);
        fes++;
        if(newQCells.nutrientes[i]>x){
            //QCells[i] = actualizamos el valor de qcells
        }else{
            gc(Psize+i) = gc(prolCells+i)+1;
        }
        if(gc(Psize+i)>max_Gc){
            randomWalk(QCells[i], QCells.gc[prolCells+1]);
        }
    }
}