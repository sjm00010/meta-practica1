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
#include "Parametros.h"
#include "random.h"

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
    
    void mostrarResultado(vector<int>& v, double t, vector<vector<int>>& flu, vector<vector<int>>& dis){
        for(int i = 1; i < v.size(); i++){
            printf(" (%2d) -%3d  ",i, v[i-1]+1);
            if (i % 5 == 0 && i > 0 && i != v.size()-1){
                cout << "\n";
            }
        } 
        cout << "\n\n";
        cout << "   El coste de la solucion es : " << coste(v, flu, dis) << "\n";
        cout << "   Tiempo empleado : " << t << "\n";
    }
    
    vector<int> localMejor(vector<vector<int>>& flu, vector<vector<int>>& dis){
        vector<int> solInicial(flu.size());
        solInicial = creaSolucion(flu.size());
        
        vector< vector<int>> solCandidatas(NUM_MOV_LOCAL);
        //Creo posibles movimientos
        int intentos = 0;
        int pos = 0;
        vector<int> cambios(flu.size()); 
        cambios = generaCambios(solInicial.size());
        for(int i = 0; i < cambios.size(); i++){
            if(cambios[i] != -1){
                solCandidatas[pos] = intercambia(solInicial, i, cambios[i]);
                pos++;
            }    
        }
        
        return solInicial;
        
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
    
    vector<int> creaSolucion(int tam){
        vector<int> solucion(tam);
        for(int i = 0; i < tam; i++){
            solucion[i]=i;
        }  

        for(int i = 0; i < tam/2; i++){
            // La primera generacion de numeros aleatorios sale generan el mismo
            // número, por eso se deben de ejecutar un minimo de 2 veces el swap
            swap(solucion[Randint(0,tam-1)],solucion[Randint(0,tam-1)]);
        } 
        
        // Lectura de la solucion
//        for(int i = 0; i < tam; i++){
//            cout << solucion[i] << "    ";
//        } 
        return solucion;
    }
    
    vector<int> generaCambios(int tam){
        vector<int> cambios(tam,-1);
        vector<pair<int,int>> solCreadas(NUM_MOV_LOCAL,pair<int,int>(-1,-1));
        int i = 0;
        while( i < NUM_MOV_LOCAL){
            int pos1 = Randint(0,tam-1);
            int pos2 = Randint(0,tam-1);
            if(pos1 != pos2){
                bool esta = false;
                for(int j = 0; j < solCreadas.size(); j++){
                    if(solCreadas[j].first != -1){
                        if(solCreadas[j].first == pos1 && solCreadas[j].second == pos2){
                            esta = true;
                        }else if(solCreadas[j].first == pos2 && solCreadas[j].second == pos1){
                            esta = true;
                        }
                    }else{
                        j = solCreadas.size();
                    }
                }
                if(!esta){
                    solCreadas.push_back(pair<int,int>(pos1, pos2));
                    cambios[pos1] = pos2;
                    i++;
                }
            }
        }
        return cambios;
    }
    
    vector<int> intercambia(vector<int> solInicial, int pos1, int pos2){
        swap(solInicial[pos1],solInicial[pos2]);
        return solInicial;
    }
    
    int coste (vector<int> sol, vector<vector<int>>& flu, vector<vector<int>>& dis){
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
};

#endif /* ALGORITMOS_H */

