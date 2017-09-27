//en este fichero se van a dar todos aquellos metodos con funcionalidad, como puede ser generar la poblacion
//reemplazaar individuos, la funcion de optimizacion, etc
#include "funciones.h"


/**generamos una poblacion 
inicial con los nutrientes de cada celula de forma aleatoria entre 0 y 1 
* siendo 0 el valor de nutrientes mas bajo y 1 el mas alto (es un valor porcentual)
*inicializaremos aqui las matrices cCells, hCells, los nutrientes de cada una y el mejor fitness
**/
void generarPoblacion(int tamPobl, int dim){
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
        nutrientes.first[i]=i;      //establecemos el id
        nutrientes.second[i]=fit;   // establecemos el fitness inicial
    }
}

/**devolvemos para cada variable el tamaño del subgrupo de cells**/
void separarPoblacion(int &PCells, int &QCells, int &DCells, int tamPobl){
    PCells = tamPobl*0.2;
    QCells = tamPobl*0.6;
    DCells = PCells;
}


/*metodo con el que actualizamos la celula de la posicion pasada
*teniendo en cuenta el contador de random walk (la parte final de los metodos)
*/
void actualizarCelula(vector<float>newCell, int id, float nutr, int &gc, int &fes){
    float fit;
    fes++;
    fit=fitness(cCells[id]);
    if(fit<nutr){
        bestFitness[id] = fit;
        hCells[id].swap(newCell);//en hCell guardo el nuevo valor si es mejor
    }else{
        cCells[id].swap(newCell);
        nutrientes.second[id]=fit;  //si no gurdamos el nuevo generado y actualizamos los valores
        gc++;                       //incrementamos el contador de randomwalk
    }
    if(gc[nutrientes.first[i]]>max_Gc){
        randomWalk(cCells[id], gc[id]);
        fes++;
    }
}

/*metodo con el que calcular el valor medio de los nutrientes de las DCells*/
float mediaNutrientes(int Dpos, int pobl){
    float resultado=0.0;
    for(int i=0; i<pobl; i++){
        resultado += nutrientes.second[Dpos+i];
    }
    resultado=resultado/pobl;
    return resultado;
}

/////////////////////////////TODO/////////////////////////////
/*metodo con el que calculamos la distancia euclidea entre las QCells*/
void distanciaEuclidea(int QCells, int &proxima1, int &porxima2){

}

/*funcion con la que calculamos el fitness de cada celula*/
double fitness(vector<double> cell){

}
/////////////////////////////TODO/////////////////////////////

vector<float> generarSolucion(int tamCell){
    vector<float> newCell;
    newCell.size(tamCell);
    float valor=0.0;

    for(int i=0; i<tamCell; i++){
        valor=Rand();
        newCell[i] = valor;
    }
    return newCell;
}

/*devuelve el indice de la primera cell de los nutrientes (ordenados de mejor a peor)*/
int mejorCelula(PCells){
    return cCells[nutrientes.first[0]];
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