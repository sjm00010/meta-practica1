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
    
    // Parametros necesarios que se necesitan
    string rutaParam = "parametros.txt";
    int numParam = 8; 

    // Parametros a cargar del archivo parametros.txt
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
    int calculaCoste (vector<int> sol, vector<vector<int>>& flu, vector<vector<int>>& dis, bool sim){
        int coste = 0;
        if(sim){
            for (int i = 0; i < flu.size(); i++){
                for(int j = i+1; j < flu.size(); j++){
                    if(i != j){
                        coste += flu[i][j]*dis[sol[i]][sol[j]];
                    }
                }
            }
            coste *= 2;
        }else{
            for (int i = 0; i < flu.size(); i++){
                for(int j = 0; j < flu.size(); j++){
                    if(i != j){
                        coste += flu[i][j]*dis[sol[i]][sol[j]];
                    }
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
    void mostrarResultado( vector<int>& v, double t, vector<vector<int>>& flu, vector<vector<int>>& dis, int coste){
        for(int i = 1; i < v.size(); i++){
            printf(" (%2d) -%3d  ",i, v[i-1]+1);
            if (i % 5 == 0 && i > 0 && i != v.size()-1){
                cout << "\n";
            }
        } 
        cout << "\n\n";
        cout << "   El coste de la solucion es : " << coste << "\n";
        cout << "   Tiempo empleado : " << t << " ms\n";
    }
    
    /**
     * Función que te dice la cantidad de digitos de un número. 
     * Auxiliar para rotar los numeros del DNI.
     * @param i Numero a analizar.
     * @return Número de digitos.
     */
    unsigned numDigitos (unsigned i){
        return i > 0 ? (int) log10 ((double) i) + 1 : 1;
    }
#endif /* PARAMETROS_H */

