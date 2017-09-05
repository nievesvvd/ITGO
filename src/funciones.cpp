//en este fichero se van a dar todos aquellos metodos con funcionalidad, como puede ser generar la poblacion
//reemplazaar individuos, la funcion de optimizacion, etc
#include "funciones.h"


/**generamos una poblacion 
inicial con los nutrientes de cada celula de forma aleatoria entre 0 y 100 
* siendo 0 el valor de nutrientes mas bajo y 100 el mas alto (es un valor porcentual)
**/
void generarPoblacion(vector<vector<float> > &cCells, vector<vector<float> > &hCells, Celula &nutrientes, int tamPobl, int dim){
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

/**COlocamos las celulas de la poblacion inicial en torno a la posicion central dependiendo de la dimension D de forma que la pos 0 es la esquina 
* superior izquierda 
**/
vector<Celulas> establecerPoblacion(vector<Celulas> PCells, vector<Celulas> QCells, vector<Celulas> DCells, int D){
    int centro = D/2, capas=0, poblacion=0, p=0, q=0, d=0, cap=1;
    vector<Historico> cCells;
    poblacion=DCells.size()+QCells.size()+PCells.size();
    cCells.resize(poblacion);
    vector<Historico>Ppos,Qpos,Dpos;
    bool terminado=false;

    //ordenamos la celulas de forma aleatoria para que de esta forma sea mas facil repartirlas por la celcula
    random_shuffle(PCells.begin(), PCells.end());
    random_shuffle(QCells.begin(), QCells.end());
    random_shuffle(DCells.begin(), DCells.end());
    //establecemos cuantas capas vamos a necesitar para cada caso
    Dpos.resize(8);
    Qpos.resize(16);
    Ppos.resize(24);
    for(int i=centro-cap; i<3; i++){
        for(int j=centro-cap; j<3; j++){
            if(cap=1){//si estamos en la capa de dcell
                if(!centro(i,j,centro)){
                    Dpos.posX[d]=i;
                    Dpos.posY[d]=j;
                    Dpos.id[d]=-1;
                    d++;
                }
            }else if(cap=2){
                if(!centro(i,j,centro) && j>(centro-cap) && {
                    Qpos.posX[q]=i;
                    Qpos.posY[q]=j;
                    Qpos.id[q]=-2;
                    q++; 
                }
            }else if (cap=3){
                if(!centro(i,j,centro) && Ppos.id[p]!=-1 && Qpos.id[p]!=-2){
                    Qpos.posX[q]=i;
                    Qpos.posY[q]=j;
                    Qpos.id[q]=-1;
                    q++; 
                }
            }
        }
    }
    // if (poblacion==10){
    //     capas=3;//1-1-1
    //     for(int i=0; i<24; i++){
    //     }
    // }else if (poblacion==30){
    //     capas=4;//1-2-1
    // }else if (poblacion==50){
    //     capas=5;//2-2-1
    // }
}

void actualizarPoblacion(vector<Celulas> &poblacionIni, vector<Celulas> PCells, vector<Celulas> QCells, vector<Celulas> DCells){
    pobl=poblacionIni.size();
    for(int i=0; i<pobl; i++){
        poblacionIni.pop();
    }
    for(int i=0; i<PCells.size(); i++){
        poblacionIni.push_back(PCells[i]);
    }
    for(int i=0; i<QCells.size(); i++){
        poblacionIni.push_back(QCells[i]);
    }
    for(int i=0; i<DCells.size(); i++){
        poblacionIni.push_back(DCells[i]);
    }
}

//vector <Celulas> distanciaEuclidea(vector <Celulas> QCells, Celulas cell){}

double mediaFitness(vector <Celulas> DCells){
    double media=0.0;
    for (int i=0; i<DCells.size(); i++){
        media+=DCells[i].nutrientes;
    }
    return media/DCells.size();
}

double alpha(double fes, double max_fes){
    return (fes/max_fes);
}
double levy(double lamda){

}