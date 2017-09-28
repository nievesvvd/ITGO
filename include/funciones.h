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

struct Distancias{
	int pto1;
	int pto2;
	double dist;
	Distancias(int &p1, int &p2, float &dst) : pto1(p1), pto2(p2), dist(dst){}

	bool operator > (float distancia) const{
		return (dist > distancia.dist);
	}
};


vector<vector<float> >cCells;
vector<vector<float> >hCells;
vector<Celula> nutrientes;
vector<float> bestFitness;	//vector en el que en cada posicion guardamos el valor del mejor fitness encontrado 
int Max_Gc=10;
//**************************** Ayuda para el pair ****************************//

/**Funcion con la que generamos una poblacion inicial aleatoria donde
// tam es el tamaño de la poblacion (longitud del vector)
// poblacion es el numero de individuos que vamos a crear
**/
void generarPoblacion(int tamPob, int dim);
void separarPoblacion(int &PCells, int &QCells, int &DCells, int tamPob);
vector<float> generarSolucion(int tamCell);
//void actualizarPoblacion(vector<int> PCells, vector<int> QCells, vector<int> DCells);
//vector <Celulas> distanciaEuclidea(vector <Celulas> QCells, Celulas cell); cogemos dos cell aleatorias mejor
void actualizarCelula(vector<float>newCell, int id, float nutr, int &gc, int &fes);
float mediaNutrientes(int cellPos, int numCells);

void distanciaEuclidea(int QCells, int &proxima1, int &porxima2);
double fitness(vector<double> cell);
int mejorCelula(PCells);

float alpha();
float levy(float step);
float step();
float sigma();
float beta();

#endif