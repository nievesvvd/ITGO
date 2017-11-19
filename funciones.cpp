//en este fichero se van a dar todos aquellos metodos con funcionalidad, como puede ser generar la poblacion
//reemplazaar individuos, la funcion de optimizacion, etc
#include "funciones.h"
#include <vector>
#include <algorithm>
//desde aqui llamamos a las funciones de realea

using namespace realea;

vector<vector<float> >cCells;
vector<vector<float> >hCells;
vector<Celula> nutrientes;
vector<Celula> bestFitness;	//vector en el que en cada posicion guardamos el valor del mejor fitness encontrado
int funcion;
unsigned long seed;

/**generamos una poblacion 
inicial con los nutrientes de cada celula de forma aleatoria entre 0 y 1 
* siendo 0 el valor de nutrientes mas bajo y 1 el mas alto (es un valor porcentual)
*inicializaremos aqui las matrices cCells, hCells, los nutrientes de cada una y el mejor fitness
**/
void generarPoblacion(int tamPobl, int dim, int fun){    
    vector<float> filas;
    cCells.resize(tamPobl);
    hCells.resize(tamPobl);
    nutrientes.resize(tamPobl);
    bestFitness.resize(tamPobl);
    funcion=fun;//seteamos directamente el numero de funcion a usar
    seed=Get_random();
    // cout << "El valor de seed vale: " << seed << endl;
    for(int i=0; i<tamPobl; i++){
        for(int j=0; j<dim; j++){
            filas.push_back(Rand());
        }
        cCells[i].resize(dim);
        hCells[i].resize(dim);
        cCells[i] = filas;
        hCells[i] = filas;

        nutrientes[i].first=i;      //establecemos el id
        nutrientes[i].second=fitness(filas);   // establecemos el fitness inicial
        bestFitness[i].first=i;      //establecemos el id
        bestFitness[i].second=nutrientes[i].second;   //establecemos el mejor fitness de base 
        filas.clear();
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
bool actualizarCelula(vector<float>newCell, int id, float nutr, int &gc, int &fes, int max_Gc){
    float fit;
    fes++;
    bool walk=false;
    fit = fitness(newCell);
    if(fit<nutr){//si el fitness de la mejor cell es mejor que el actual de dicha cell
        bestFitness[id].second = fit;
        nutrientes[id].second=fit;
        hCells[id].swap(newCell);//en hCell guardo el nuevo valor si es mejor
        cCells[id].swap(newCell);
    }else{
        cCells[id].swap(newCell);
        nutrientes[id].second=fit;  //si no gurdamos el nuevo generado y actualizamos los valores
        gc++;                       //incrementamos el contador de randomwalk
    }
    if(gc>max_Gc){
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
    /*---------version 1.0---------*/
    // float valor=0.0;
    // for(unsigned int i=0; i<cell.size(); i++){
    //     valor+=pow(cell[i],2);
    // }
    // return valor;
    /*---------version 1.0---------*/

    /*---------version daniel---------*/
    int dim = cell.size();
    tChromosomeReal newCell(dim);
    
    for(int i=0; i<dim; i++){//pasamos de nuestra cell a la de la libreria (tipo)
        newCell[i]=(double)cell[i];
    }
    Random random(new SRandom(seed) );
    ProblemCEC2005 cec2005(&random, dim);
    ProblemPtr problem = cec2005.get(funcion);
    tFitness fit = problem->eval(newCell);
    return (float)fit;
    /*---------version daniel---------*/
}
/*y las cosas de euler, steps longitud y tal de PCells y de invasive cella*/
float normalEuclidea(vector<float> cell){
    float total=0;
    for(unsigned int i=0; i<cell.size(); i++){
        total+=pow(cell[i],2);
    }
    return sqrt(total);
}

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
    sort(bestFitness.begin(), bestFitness.end());
    return bestFitness[0].first;
}

float alpha(int fes, int max_fes){
    float valor=0.0, rnd;
    rnd=Rand();
    valor=rnd*(fes/max_fes);
    return valor;
}

float levy(float s){
    float valor=0.0, w;
    w=Randfloat(0,2);
    valor=pow(s, -1-w);
    return valor;
}

float step(){
    float valor, v, aux;
    
    aux=sgma();
    v=pow(normalDisrt(aux),2);
    
    valor=normalDisrt(1.0)/pow(v,1/Randfloat(0.3,1.99));
    return valor;
}

float sgma(){//step de las Pcells
    float w=1.5, valor;

    valor= pow((tgammaf(1+w)*sin((PI*w)/2) ) / 
            ( tgammaf((1+w)/2)*w*pow(2,(w-1)/2) ),1/w);

    return valor;
}
double beta(){//qCells, para el step size cuando se mueven
    double normal; 
    double randi, beta;
    
    normal = normalDisrt(1.0); //Generate numbers;
    randi=Rand();
    beta=normal*randi;

    return beta;
}

double normalDisrt(double second){
    double valor;   
    std::default_random_engine de(time(0)); //seed
    std::normal_distribution<double> nd(0, second); //mean followed by stdiv
    valor = nd(de); //Generate numbers;
    //std::default_random_engine generator;

    return valor;
}