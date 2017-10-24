//en este fichero se van a dar todos aquellos metodos con funcionalidad, como puede ser generar la poblacion
//reemplazaar individuos, la funcion de optimizacion, etc
#include "funciones.h"
#include <vector>
#include <algorithm>


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
    Celula cell;

    for(int i=0; i<tamPobl; i++){
        for(int j=0; j<tamPobl; j++){
            valor=Rand();
            filas.push_back(valor);
            cCells[i].push_back(valor);
            hCells[i].push_back(valor);
        }
        fit=fitness(filas);
        nutrientes[i].first=i;      //establecemos el id
        nutrientes[i].second=fit;   // establecemos el fitness inicial
        // nutrientes[i].push_back(cell);
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
bool actualizarCelula(vector<float>newCell, int id, float nutr, int &gc, int &fes){
    float fit;
    fes++;
    bool walk=false;
    fit=fitness(cCells[id]);
    if(fit<nutr){
        bestFitness[id] = fit;
        hCells[id].swap(newCell);//en hCell guardo el nuevo valor si es mejor
    }else{
        cCells[id].swap(newCell);
        nutrientes[id].second=fit;  //si no gurdamos el nuevo generado y actualizamos los valores
        gc++;                       //incrementamos el contador de randomwalk
    }
    if(gc>Max_Gc){
        // randomWalk(cCells[id], gc[id]);
        walk=true;
        fes++;
    }
    return walk;
}

/*metodo con el que calcular el valor medio de los nutrientes de las DCells*/
float mediaNutrientes(int Dpos, int pobl){
    float resultado=0.0;
    for(int i=0; i<pobl; i++){
        resultado += nutrientes[Dpos+i].second;
    }
    resultado=resultado/pobl;
    return resultado;
}

/*metodo con el que calculamos la distancia euclidea entre las QCells*/
void distanciaEuclidea(int QCells, vector<Distancias> &distancia, int begin, int end){
    Distancias resultado;
    double suma=0.0;
    
    //sort de menos distancia a mas
    for(int i=begin; i<end-1; i++){//recorremos la pobacion de 1º vez
        for(int j=i+1; j<end; j++){//para cada cell recorremos las demas sin contar a ella misma ( eso el +1)
            for(unsigned int k=0; k<cCells[0].size(); k++){//calculamos la distancia entre las 2 celulas
                suma= suma + pow(cCells[i][k]-cCells[j][k], 2);
            }
            resultado.pto1=i;
            resultado.pto2=j;
            resultado.dist=sqrt(suma);
            distancia.push_back(resultado);
            suma=0.0;
        }
    }
//    distancia.sort();
    std::sort(distancia.begin(), distancia.end(), DistanciaMenorComparator);
}



//actualizamos las dos celulas más cercana a QCell si que sea ella
void cellCercanas(int QCells, int &proxima1, int &proxima2, vector<Distancias> distancias){
    if(distancias[0].pto1==QCells){
        proxima1=distancias[0].pto1;
    }else{
        proxima1=distancias[0].pto2;
    }
    if(distancias[1].pto1==QCells){
        proxima2=distancias[1].pto1;
    }else{
        proxima2=distancias[1].pto2;
    }
}
/////////////////////////////TODO/////////////////////////////
/*funcion con la que calculamos el fitness de cada celula*/
float fitness(vector<float> cell){
    //mientras veo como meto el modulo de dani
    float valor=0.0;
    for(unsigned int i=0; i<cell.size(); i++){
        valor+=pow(cell[i],2);
    }
    return valor;
}
/*y las cosas de euler, steps longitud y tal de PCells y de invasive cella*/
/////////////////////////////TODO/////////////////////////////

vector<float> generarSolucion(int tamCell){
    vector<float> newCell;
    newCell.resize(tamCell);
    float valor=0.0;

    for(int i=0; i<tamCell; i++){
        valor=Rand();
        newCell[i] = valor;
    }
    return newCell;
}

/*devuelve el indice de la primera cell de los nutrientes (ordenados de mejor a peor)*/
int mejorCelula(){
    return nutrientes[0].first;
}

float alpha(int fes, int max_fes){
    float valor=0.0, rnd=0.0;
    rnd=Rand();
    valor=rnd*(fes/max_fes);
    return valor;
}

float levy(float s){
    float valor=0.0, w=0.0;
    w=Randfloat(0,2);
    valor=pow(s, -1-w);
    return valor;
}

float step(){
    float valor=0.0, u=0.0, v=0.0, w=0.0, aux=0.0;
    
    aux=sigma();
    w=Randfloat(0.3,1.99);
    u=normalDisrt(1.0);
    v=pow(normalDisrt(aux),2);
    
    valor=u/pow(v,1/w);
    return valor;
}

float sigma(){//step de las Pcells
    float w=1.5, valor=0.0;

    valor= pow((tgammaf(1+w)*sin((PI*w)/2) ) / 
            ( tgammaf((1+w)/2)*w*pow(2,(w-1)/2) ),1/w);

    return valor;
}
double beta(){//qCells, para el step size cuando se mueven
    double normal=0.0; 
    double rand=0.0, beta=0.0;
    
    normal = normalDisrt(1.0); //Generate numbers;
    rand=Rand();
    beta=normal*rand;

    return beta;
}

double normalDisrt(double second){
    double valor=0.0;   
    std::default_random_engine de(time(0)); //seed
    std::normal_distribution<double> nd(0, second); //mean followed by stdiv
    valor = nd(de); //Generate numbers;
    //std::default_random_engine generator;

    return valor;
}