#ifndef _DATOS_H_
#define _DATOS_H_

#include <vector>
#include "random-ppio.h"

class Datos{
private:
    int poblacion;
    int dimension;
    vector<vector<double> > cCells; //matriz que contiene los datos actuales de la matriz de celulas   
    vector<vector<double> > hCells; //matriz que contiene los datos con las mejores celulas encontradas para cada una de las anteriores
public:
    Datos(){
        vector<double> init;
        init.resize(0, 0.0);  //es de dim ya que en la ultima posicion pondremos fitness en hCell y GC en cCell
        cCells.push_back(init);
        hCells.push_back(init);
        poblacion=0;
        dimension=0;
        
    }
    Datos(int tam, int dim){
        vector<double> aux;
        double valor;
        for(int i=0; i<tam; i++){
            for(int j=0; j<dim; j++){
                valor=ran
            }
        }
    }
    ~Datos();

    /*void setTamPoblacion(int tamPobl){
        poblacion = tamPobl;
    }
    void setDimension(int dim){
        dimension = dim;
    }*/
    void setGC(int gc, int cell){
        cCells[cell][dimension]= gc;
    }
    void setFitness(double fitness, int cell){
        hcells[cell][dimension]=fitness;
    }


    vector<double> getcCell(int posx){
        return cCells[posx];
    }
    vector<double> gethCell(int posx){
        return hCells[posx];       
    }
    double getcFitness(int cell){
        return cCells[cell][dimension];
    }
    double getGc(int cell){
        return hCell[cell][dimension];
    }
    int getPoblacion(){
        return poblacion;
    }
    int getDimension(){
        return dimension;
    }
    void generarPoblacion();

};



#endif