#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <algorithm>    // std::random_shuffle
#include <utility>      //Para el pair
#include <math.h>         //para el levy fight
#include "random_ppio.h"
//#include <random>

using namespace std;

#define PI 3.14159265

//**************************** Ayuda para el pair ****************************//
typedef std::pair <int, float> Celula;   //pos 1 del pair es el id, y la ps2 el valor de los nutrientes

class compararCelulas{ //Comparador de la PQ. Devuelve TRUE si coste de cell1 es mayor que coste de cell2
public:
    compararCelulas(){}
  bool operator()(const Celula cell1, const Celula cell2){
    return cell1.second < cell2.second;
  }
};

struct Distancias{
	int pto1;
	int pto2;
	double dist;
	//Distancias(int &p1, int &p2, float &dst) : pto1(p1), pto2(p2), dist(dst){}

	bool operator > (double distancia) const{
		return (dist > distancia);
	}
};

struct DistanciaMenor {
	bool operator() (Distancias i, Distancias j) {
		return i.dist < j.dist;
	}
}extern DistanciaMenorComparator;


extern vector<vector<float> >cCells;
extern vector<vector<float> >hCells;
extern vector<Celula> nutrientes;
extern vector<Celula> bestFitness; //vector en el que en cada posicion guardamos el valor del mejor fitness encontrado
//int Max_Gc=10;
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
bool actualizarCelula(vector<float>newCell, int id, float nutr, int &gc, int &fes, int max_Gc);
float mediaNutrientes(int cellPos, int numCells);

void distanciaEuclidea(int QCells, vector<Distancias> &distancia, int begin, int end);
void cellCercanas(int QCells, int &proxima1, int &proxima2, vector<Distancias> distancias);
float fitness(vector<float> cell);
int mejorCelula();

float alpha(int fes, int max_fes);
float levy(float step);
float step();
float sigma();
double beta();
double normalDisrt(double second);

#endif