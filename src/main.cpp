//fichero en el que tenemos la ejecución del algoritmo ITGO
#include "ITGO.h"
//#include "funciones.h"
#include <time.h>
#include <vector>
#include <iostream>
#include "random_ppio.h"

using namespace std;

//dimension tampob, iter
int main (int argc, char *argv[]) { 
    // if(argc !=10){
    //     cout << "Número de parámetros incorrecto."
    // }

    vector<float> solucionITGO;
    int seed, tam;
    clock_t start;
    double timeITGO;

    //programa, dimension, tam poblacion, iter max, seed
    if(argc==5){
        seed=atoi(argv[4]);
        Set_random(seed);
    }

    solucionITGO.resize(atoi(argv[1]));
    start = clock();
    cout<<"llamamos al metodo" << endl;
    solucionITGO = algoritmoITGO(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    timeITGO = ((double)clock() - start) / CLOCKS_PER_SEC;
    tam=solucionITGO.size();

    cout << "La mejor celula encontrada es" << endl;
    for(int i=0; i<tam-1; i++){
        cout << solucionITGO[i] << " ";
    }
    cout << endl;
    cout << "Su fitness es de: " << solucionITGO[tam-1] << endl;
    cout << "Y tarda: " << timeITGO << endl;
}
