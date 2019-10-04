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
     * Función para registrar los datos en un archivo .log
     * @param log Objeto para crear el fichero.
     * @param prueba Número de la prueba por la que va.
     *              (De las 5 que hay que realizar con el DNI)
     * @param sol Vector con la solución
     * @param coste Coste de la solución
     * @param tiempo Tiempo en calcularla
     */
    void regitroLog(CargarFichero log, int prueba, vector<int> sol, int coste, double tiempo){
        string nombreAr = carpetaLog + "GREEDY-" + to_string(prueba) + "_" + nombreArchivo + ".log";;
        log.creaLog(nombreAr, prueba);
        log.registraLogDatos(nombreAr, sol, coste);
        log.registraTiempo(nombreAr, tiempo, DNI);
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
        v[pos] = -1; // Marco la posicion como seleccionada
        return pos;
    }

};

#endif /* GREEDY_H */

