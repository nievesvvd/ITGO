//fichero en el que tenemos la ejecución del algoritmo ITGO
//#include "funciones.h"
#include <time.h>
#include <vector>
#include <iostream>
#include "ITGO.h"
#include "random_ppio.h"

using namespace std;

//dimension tampob, iter, seed
int main (int argc, char *argv[]) { 
    // if(argc !=10){
    //     cout << "Número de parámetros incorrecto."
    // }

    vector<float> solucionITGO;
    int seed, tam;
    clock_t start;
    double timeITGO;

    //programa, fun, dimension, tam poblacion, iter max, seed
    if(argc==6){
        seed=atoi(argv[5]);
        Set_random(seed);
    }else{
        cout << "Introduzca en orden: Num funcion, dimension, tamaño pobl, max iter, seed" << endl;
        return -1;
    }

    solucionITGO.resize(atoi(argv[2]));
    start = clock();
    solucionITGO = algoritmoITGO(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    timeITGO = ((double)clock() - start) / CLOCKS_PER_SEC;
    tam=solucionITGO.size();

    // cout << "La mejor celula encontrada es" << endl;
    // for(int i=0; i<tam-1; i++){
    //     cout << solucionITGO[i] << " ";
    // }
    // cout << endl;
    cout << "Su fitness es de: " << solucionITGO[tam-1] << endl;
    //cout << "Y tarda: " << timeITGO << endl;
}
