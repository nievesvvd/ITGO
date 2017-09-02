//en este fichero se van a dar todos aquellos metodos con funcionalidad, como puede ser generar la poblacion
//reemplazaar individuos, la funcion de optimizacion, etc
#include "funciones.h"


/**generamos una poblacion 
inicial con los nutrientes de cada celula de forma aleatoria entre 0 y 100 
* siendo 0 el valor de nutrientes mas bajo y 100 el mas alto (es un valor porcentual)
**/
vector <vector<int> > generarPoblacion(int tam, int poblacion, vector<vector<double> > &poblacionIni, vector<vector<double> > &mejorCell){
    vector <vector<int> > resumen;
    double fit=0.0;
    for(int i=0; i<poblacion; i++){//tamanio poblacion
        for(int j=0; j<tam; j++){//tamanio de cell
            poblacionIni[i][j]=Rand();
            mejorCell[i][j]= poblacionIni[i][j];
        }//falta calcular el valor de fitness de cada vector de la primera parte
        resumen[i][0]=i;                        //almacenamos el id de la cell (posicion)
        resumen[i][1]=fitness(poblacion[i]);    //almacenamos el fitness de la cell
        resumen[i][2]=resumen[i][1];            //almacenamos el mejor fitness (actual en este caso)
        resumen[i][5]=0;                        //ponemos el valor inicial de GC a 0
    }
    return resumen;
}

/**ordenamos la pobacion en funcion de su valor de fitness o nutrientes y le asignamos una id a cada celula
*el orden de ordenacion es ascendente  (D/Q/P)
**/
void ordenarPoblacion(vector<vector<double> > &poblacionIni, vector<double> fitness, int tam, int pobl){
    fitness.sort(fitness.begin(), fitness.end());
    for(int i=0; i<pobl; i++){//intercambiamos las posiciones de la matriz en funcion del fitness
        //poblacionIni swap pos actual con la pos [i] fitness
    }
}
/**Separamos la poblacion en tres subvectores diferentes PCells, QCells, DCells y le establecemos el tipo a cada celula para su posterior identificacion
**/
void separarPoblacion(vector<Celulas> poblacionIni, vector<Celulas> &PCells, vector<Celulas> &QCells, vector<Celulas> &DCells){
    int pos1, pos2, pos3;
    pos1=poblacionIni.size()*0.2;
    pos2=poblacionIni.size()*0.6;
    pos3=pos1;
    for(int i=0; i<poblacionIni.size(); i++){
        if(i<pos1){
            poblacionIni.tipo='D';
            DCells.push_back(poblacionIni[i]);
        }else if(i>=pos1 && i<pos2){
            poblacionIni.tipo='Q';
            QCells.push_back(poblacionIni[i]);
        }else{
            poblacionIni.tipo='P';
            PCells.push_back(poblacionIni[i]);
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