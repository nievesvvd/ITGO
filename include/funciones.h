#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <algorithm>    // std::random_shuffle
#include <utility>      //Para el pair
#include <math>         //para el levy fight
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
vector<vector<float> >cCells;
vector<vector<float> >hCells;
vector<Celula> nutrientes;
vector<float> bestFitness;
int Max_Gc=10;
//**************************** Ayuda para el pair ****************************//

/**Funcion con la que generamos una poblacion inicial aleatoria donde
// tam es el tamaño de la poblacion (longitud del vector)
// poblacion es el numero de individuos que vamos a crear
**/
void generarPoblacion(int tamPob, int dim);
void separarPoblacion(int PCells, int QCells, int DCells);
//void actualizarPoblacion(vector<int> PCells, vector<int> QCells, vector<int> DCells);
//vector <Celulas> distanciaEuclidea(vector <Celulas> QCells, Celulas cell); cogemos dos cell aleatorias mejor
distanciaEuclidea(int QCells, int &proxima1, int &porxima2);
float mediaNutrientes(int cellPos, int numCells);
vector<float> generarSolucion(int tamCell);
double fitness(vector<double> cell);
void actualizarCelula(/*params*/);
int mejorCelula(PCells);

float step();
float levy(float step);
float alpha();
float beta();

#endif