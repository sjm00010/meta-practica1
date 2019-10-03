/* 
 * File:   Parametros.h
 * Author: PORTATIL
 *
 * Created on 27 de septiembre de 2019, 10:58
 */

#ifndef PARAMETROS_H
#define PARAMETROS_H

#include <string>
#include <vector>
#include <cmath>

using namespace std;
    
    string rutaParam = "parametros.txt";
    int numParam = 8; 

    int DNI;
    int NUM_SOLU_LOCAL;
    int MAX_INTENTOS_LOCAL;
    int LIM_EVA_LOCAL;
    int NUM_PRUEBAS;
    
    string carpetaDatos;
    string nombreArchivo;
    string carpetaLog;
    
// Funciones generales 
    
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
    
    unsigned numDigitos (unsigned i){
        return i > 0 ? (int) log10 ((double) i) + 1 : 1;
    }
#endif /* PARAMETROS_H */

