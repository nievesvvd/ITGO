#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <algorithm>    // std::random_shuffle
#include <utility>      //Para el pair
#include "random_ppio.h"

using namespace std;

//**************************** Ayuda para el pair ****************************//
typedef std::pair <std::vector <int>, double> Celula;   //pos 1 del pais es el id, y la ps2 el valor de los nutrientes

class compararCelulas{ //Comparador de la PQ. Devuelve TRUE si coste de cell1 es mayor que coste de cell2
public:
    compararCelulas(){}
  bool operator()(const Celula cell1, const Celula cell2){
    return individuo1.second < individuo2.second;
  }
};
//**************************** Ayuda para el pair ****************************//

/**Funcion con la que generamos una poblacion inicial aleatoria donde
// tam es el tamaño de la poblacion (longitud del vector)
// poblacion es el numero de individuos que vamos a crear
**/
void generarPoblacion(vector<vector<float> > &cCells, vector<vector<float> > &hCells, Celula &nutrientes, int tamPobl, int dim);
void separarPoblacion(Celula nutrientes, vector<int> &PCells, vector<int> &QCells, vector<int> &DCells);
void actualizarPoblacion(vector<vector<double> > &poblacionIni, vector<int> PCells, vector<int> QCells, vector<int> DCells);
//vector <Celulas> distanciaEuclidea(vector <Celulas> QCells, Celulas cell); cogemos dos cell aleatorias mejor

double fitness(vector<double> cell);
double mediaFitness(vector<vector<double> > DCells);
double alpha(int fes, int max_fes);
double levy(double step);

#endif