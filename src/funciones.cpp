//en este fichero se van a dar todos aquellos metodos con funcionalidad, como puede ser generar la poblacion
//reemplazaar individuos, la funcion de optimizacion, etc
#include "funciones.h"

vector <Celulas> generarPoblacion(int tam){
    vector <Celulas> poblacion;
    int nutrients;
    for(int i=0; i<tam; i++){
        poblacion[i].tipo = 'N';
        poblacion[i].nutrientes = Randint(0,101);
        poblacion[i].gc=0.0;
    }
    return poblacion;
}
void ordenarPoblacion(vector<Celulas> &poblacionIni){
    poblacionIni.sort(poblacionIni.begin(), poblacionIni.end());
}

void separarPoblacion(vector<Celulas> poblacionIni, vector<Celulas> &PCells, vector<Celulas> &QCells, vector<Celulas> &DCells){
    int pos1, pos2, pos3;
    pos1=poblacionIni.size()*0.2;
    pos2=poblacionIni.size()*0.6;
    pos3=pos1;
    for(int i=0; i<poblacionIni.size(); i++){
        if(i<pos1){
            DCells.push_back(poblacionIni[i]);
        }else if(i>=pos1 && i<pos2){
            QCells.push_back(poblacionIni[i]);
        }else{
            PCells.push_back(poblacionIni[i]);
        }
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


double alpha(double fes, double max_fes){
    return (fes/max_fes);
}
double levy(double lamda){

}