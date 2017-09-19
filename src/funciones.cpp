//en este fichero se van a dar todos aquellos metodos con funcionalidad, como puede ser generar la poblacion
//reemplazaar individuos, la funcion de optimizacion, etc
#include "funciones.h"


/**generamos una poblacion 
inicial con los nutrientes de cada celula de forma aleatoria entre 0 y 100 
* siendo 0 el valor de nutrientes mas bajo y 100 el mas alto (es un valor porcentual)
**/
void generarPoblacion(Celula &nutrientes, int tamPobl, int dim){
    double fit=0.0;
    float valor=0.0;
    vector<float> filas;
    filas.resize(dim, 0);

    for(int i=0; i<tamPobl; i++){
        for(int j=0; j<tamPobl; j++){
            valor=Rand();
            filas.push_back(valor);
        }
        cCell[i].push_back(filas);
        hCell[i].push_back(filas);
        fit=fitness(filas);
        nutrientes.first[i]=i;
        nutrientes.second[i]=fit;
    }
}

/**Separamos los indices de la poblacion una vez ordenada de forma ascendente**/
void separarPoblacion(Celula nutrientes, vector<Celulas> &PCells, vector<Celulas> &QCells, vector<Celulas> &DCells){
    int dCells=nutrientes.first.size()*0.2;
    int qCells=(nutrientes.first.size()*0.6)+dCells;

    for(int i=0; i<nutrientes.first.size(); i++){
        if(i<=dCells){
            PCells.push_back(nutrientes.fisrt[i]);
        }else if(i>dCells && i<=qCells){
            QCells.push_back(nutrientes.first[i]);
        }else{
            DCells.push_back(nutrientes.first[i]);
        }
    }
}

void actualizarCelula(vector<float>newCell, int id, float nutr, int &gc){
    float fit;
    fit=fitness(cCells[id]);
    fes++;
    if(fit<nutr){
        bestFitness[id] = fit;
        hCells[id]= newCell;//en hCell guardo el nuevo valor si es mejor
    }else{
        cCells[id] = newCell;
        nutrientes.second[id]=fit;
        gc++;
    }
    if(gc[nutrientes.first[i]]>max_Gc){
        randomWalk(cCells[id], gc);
    }
}

float mediaNutrientes(int Dpos, int pobl){
    float resultado=0.0;
    for(int i=0; i<pobl; i++){
        resultado=( resultado+(nutrientes.second[Dpos+i]) )/pobl;
    }
    return resultado;
}

float alpha(int fes, int max_fes){
    float valor=0.0, rnd=0.0;
    rnd=Rand();
    valor=rnd*(fes/max_fes);
    return valor;
}

float levy(float s){
    float valor=0.0, w=0.0;
    w=rand(0,2);
    valor=pow(s, -1-w);
    return valor;

}

float step(){
    float valor=0.0, u=0.0, v=0.0, w=0.0;
    w=Rand();
    v=pow(sigma(),2);
    valor=u/pow(v,1/w);
    return valor;
}

float sigma(){
    return 0.0;
}
float beta(){
    return 0.0;
}