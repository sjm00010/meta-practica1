/* 
 * File:   Algoritmos.h
 * Author: sjm00010
 *
 * Created on 26 de septiembre de 2019, 19:09
 */

#ifndef GREEDY_H
#define GREEDY_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "random.h"
#include "CargarFichero.h"

using namespace std;

class Greedy {
public:
    
    /**
     * Algoritmo Greedy
     * @param flu Matriz de flujos
     * @param dis MAtriz de distancias
     * @return Devuelve un vector con las soluciones.
     */
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
    
    /**
     * Función que calcula el coste de una solción.
     * @param sol Vector con la solución.
     * @param flu Matriz de flujos.
     * @param dis Matriz de distancias.
     * @return Devuelve el coste calculado.
     */
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
    
    /**
     * Función que muestra por consola la solción calculada.
     * @param v Vector con la solución.
     * @param t Tiempo que tarda el algoritmo.
     * @param flu Matriz de flujos
     * @param dis Matriz de distancias
     */
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
    /**
     * Función que busca el menor de un vector y devuelve su posición.
     * @param v Vector de busqueda
     * @return  Posición del dato menor
     */
    int menor(vector<int>& v){
        int pos = 0;
        for(int i = 0; i < v.size(); i++){
            if(v[i] < v[pos]){
                pos = i;
            }
        }
        //cout << "Distancia menor : " << v[pos] << " ("<< pos <<")" <<"\n";
        v[pos] = std::numeric_limits<int>::max(); // Marco la posicion como seleccionada
        return pos;
        
    }
    
    /**
     * Función que busca el mayor de un vector y devuelve su posición.
     * @param v Vector de busqueda
     * @return Posición del mayor
     */
    int mayor(vector<int>& v){
        int pos = 0;
        for(int i = 1; i < v.size(); i++){
            if(v[i] > v[pos] && v[i] != -1){
                pos = i;
            }
        }
        //cout << "Flujo mayor : " << v[pos] <<" ("<< pos <<")"<< "     " ;
        v[pos] = -1; // Marco la posicion como seleccionada
        return pos;
    }

};

#endif /* GREEDY_H */

