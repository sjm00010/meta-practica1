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
    int coste (vector<vector<int>>& flu, vector<vector<int>>& dis){
        int sol = 0;
        for (int i = 0; i < flu.size(); i++){
            for(int j = 0; j < flu.size(); j++){
                sol = flu[i][j]*dis[i][j] + flu[j][i]*dis[j][i];
            }
        }
        return sol;
    }
    
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
        
        // Comprobaciones
//        for(int i = 0; i < solDis.size() ; i++){
//            cout <<"("<<i+1<<")"<< solDis[i] << "  ";
//        }
//        cout << "\n";
//        for(int i = 0; i < solFlu.size() ; i++){
//            cout << "("<<i+1<<")"<< solFlu[i] << "  ";
//        }
//        cout << "\n";
        // fin de las comprobaciones
        
        vector<int> solucion(flu.size());
        for(int i = 0; i < solucion.size(); i++){
            solucion[mayor(solFlu)] = menor(solDis);
        }
        return solucion;
    }
    
    void mostrarGreedy(vector<int>& v){
        for(int i = 0; i < v.size(); i++){
            cout << "   La puerta " << (i+1) << " con " << v[i]+1 << "\n";
        } 
    }
    
    vector<int> localMejor(vector<vector<int>>& flu, vector<vector<int>>& dis){
        vector<int> solInicial(flu.size());
        solInicial = creaSolucion(flu.size());
        
        vector< vector<int>> solCandidatas(NUM_MOV_LOCAL);
        //Creo posibles movimientos
        int evaluaciones = 0;
        int intentos = 0;
        for(int i = 0; i < NUM_MOV_LOCAL; i++){
            vector<int> sol(flu.size());
            sol = generaSol(solInicial);
            solCandidatas[i] = sol;
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
        for(int i = 0; i < tam; i++){
            cout << solucion[i] << "    ";
        } 
        return solucion;
    }
    
    vector<int> generaSol(vector<int> solInicial){
        swap(solInicial[Randint(0,solInicial.size()-1)],
                solInicial[Randint(0,solInicial.size()-1)]);
        return solInicial;
    }
    
};

#endif /* ALGORITMOS_H */

