#ifndef _DATOS_H_
#define _DATOS_H_

#include <vector>

class Datos{
private:
    int poblacion;
    int dimension;
    vector<vector<double> > cCells; //matriz que contiene los datos actuales de la matriz de celulas   
    vector<vector<double> > hCells; //matriz que contiene los datos con las mejores celulas encontradas para cada una de las anteriores
public:
    Datos(int tamPobl, int dim){
        vector<double> init;
        for(int i=0; i<tamPobl; i++){
            init.resize(dim, 0.0);
            cCells.push_back(init);
            hCells.push_back(init);
        }
    }
    ~Datos();

    void setTamPoblacion(int tamPobl){
        poblacion = tamPobl;
    }
    void setDimension(int dim){
        dimension = dim;
    }



    double getcCell(int posx, int posy){
        return cCells[posx][posy];
    }
    double gethCell(int celula){
        return hCells[posx][posy];       
    }
    double getcFitness(int cell){
        return cCells[cell][tamPobl];
    }
    double gethFitness(){

    }

};



#endif