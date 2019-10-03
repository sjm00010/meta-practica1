/* 
 * File:   Algoritmos.h
 * Author: sjm00010
 *
 * Created on 26 de septiembre de 2019, 19:09
 */

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "random.h"
#include "CargarFichero.h"

using namespace std;

class Algoritmos {
public:
   
    vector<int> greedy(vector<vector<int>>& flu, vector<vector<int>>& dis){
        vector<int> solFlu(flu.size());
        vector<int> solDis(dis.size());
        
        for(int i = 0; i < flu.size(); i++){
            solFlu[i] = 0; 
            solDis[i] = 0;
            for(int j = 0; j < flu.size(); j++){
                if(i != j){
                    solFlu[i] += flu[i][j];
                    solDis[i] += dis[i][j];
                }  
            }
        }
        
        vector<int> solucion(flu.size());
        for(int i = 0; i < solucion.size(); i++){
            solucion[mayor(solFlu)] = menor(solDis);
        }
        return solucion;
    }
    
    int calculaCoste (vector<int> sol, vector<vector<int>>& flu, vector<vector<int>>& dis){
        int coste = 0;
        for (int i = 0; i < flu.size(); i++){
            for(int j = 0; j < flu.size(); j++){
                if(i != j){
                    coste += flu[i][j]*dis[sol[i]][sol[j]];
                }
            }
        }
        return coste;
    }
    
    void mostrarResultado( vector<int>& v, double t, vector<vector<int>>& flu, vector<vector<int>>& dis){
        for(int i = 1; i < v.size(); i++){
            printf(" (%2d) -%3d  ",i, v[i-1]+1);
            if (i % 5 == 0 && i > 0 && i != v.size()-1){
                cout << "\n";
            }
        } 
        cout << "\n\n";
        cout << "   El coste de la solucion es : " << calculaCoste(v, flu, dis) << "\n";
        cout << "   Tiempo empleado : " << t << "\n";
    }
    
    
    
    
private:
    int menor(vector<int>& v){
        int pos = 0;
        for(int i = 0; i < v.size(); i++){
            if(v[i] < v[pos]){
                pos = i;
            }
        }
        //cout << "Distancia menor : " << v[pos] << " ("<< pos <<")" <<"\n";
        v[pos] = INT_MAX; // Marco la posicion como seleccionada
        return pos;
        
    }
    
    int mayor(vector<int>& v){
        int pos = 0;
        for(int i = 1; i < v.size(); i++){
            if(v[i] > v[pos] && v[i] != INT_MIN){
                pos = i;
            }
        }
        //cout << "Flujo mayor : " << v[pos] <<" ("<< pos <<")"<< "     " ;
        v[pos] = INT_MIN; // Marco la posicion como seleccionada
        return pos;
    }
    
    vector<int> intercambia(vector<int> solInicial, int pos1, int pos2){
        swap(solInicial[pos1],solInicial[pos2]);
        return solInicial;
    }

};

#endif /* ALGORITMOS_H */

