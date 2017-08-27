//en este fichero se van a dar todos aquellos metodos con funcionalidad, como puede ser generar la poblacion
//reemplazaar individuos, la funcion de optimizacion, etc
#include "funciones.h"


/**generamos una poblacion i
nicial con los nutrientes de cada celula de forma aleatoria entre 0 y 100 
* siendo 0 el valor de nutrientes mas bajo y 100 el mas alto (es un valor porcentual)
**/
vector <Celulas> generarPoblacion(int tam){
    vector <Celulas> poblacion;
    Celulas newCell;
    int nutrients;
    for(int i=0; i<tam; i++){
        newCell.id=-1;
        newCell.tipo = 'N';
        newCell.nutrientes = Randint(0,101);
        newCell.gc=0.0;
        poblacion.push(newCell);
    }
    return poblacion;
}

/**ordenamos la pobacion en funcion de su valor de fitness o nutrientes y le asignamos una id a cada celula
*el orden de ordenacion es ascendente  (D/Q/P)
**/
void ordenarPoblacion(vector<Celulas> &poblacionIni){
    poblacionIni.sort(poblacionIni.begin(), poblacionIni.end());
    for(int i=0; i<poblacionIni.size(); i++){
        poblacionIni.id=i;
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
* superior izquierda y se rellena de forma horaria
**/
vector<Celulas> setearPoblacion(vector<Celulas> poblacionIni, int D){
    int centro = (D*D)/2;
    int pos, tam1=poblacionIni.size()*0.2,tam2=poblacionIni.size()*0.6;
    vector<bool>posQ, posPD;
    posQ.resize(tam2,False);
    posPD.resize(tam1,False);
    for(int i=0; i<poblacionIni.size(); i++){
        pos=Randint(0,6);

    }
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