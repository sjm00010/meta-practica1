/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BLocalMejor.h
 * Author: sjm00010
 *
 * Created on 3 de octubre de 2019, 12:22
 */

#ifndef BLOCALMEJOR_H
#define BLOCALMEJOR_H

#include <vector>
#include <sstream>

#include "Parametros.h"
#include "FuncionesComunes.h"
#include "CargarFichero.h"

using namespace std;

class BLocalMejor {
public:
    
    /**
     * Algoritmo de Busqueda Local del Mejor
     * @param log Archivo .log para guardar los resultados
     * @param prueba Número de la prueba, de las ejecuciones con distinta semilla
     * @param flu Matriz de flujos
     * @param dis Matriz de distancias
     * @param sim Indica si la matriz es simétrica
     * @return Devuelve el vector solución
     */
    vector<int> bLocalMejor(CargarFichero& log,int prueba, vector<vector<int>>& flu, vector<vector<int>>& dis, bool sim){
        // Creo la solución inicial de partida
        vector<int> solActual(flu.size());
        solActual = creaSolucion(flu.size());
        int costeAc = calculaCoste(solActual, flu, dis, sim);
        int numSolucionesLocales;
        creaLog(log, prueba);
        log.registraLogDatos(rutaLog ,solActual, costeAc);
                
        int k = 0; // Limite de 50000 evaluaciones
        int intentos = 0; // Limite de 100 intentos
        while( k < stoi(parametros[LIM_EVA_LOCAL], nullptr, 10)){
            // Busco 10 vecinos 
            if(generaCambios(log, costeAc, solActual, flu, dis)){
                k++;
                intentos = 0;
            }else{
                intentos++;
            }
            
            if(intentos == stoi(parametros[NUM_SOLU_LOCAL], nullptr, 10)){
                cout << "Iteracion : " << k << "\n\n";
                return solActual;
            }
        }
        cout << "Iteracion : " << k << "\n";
        return solActual;
    }
    
    /**
     * Función para registrar los datos de la solucion en un archivo .log
     * @param log Objeto para crear el fichero.
     * @param prueba Número de la prueba por la que va.
     *              (De las 5 que hay que realizar con el DNI)
     * @param sol Vector con la solución
     * @param coste Coste de la solución
     * @param tiempo Tiempo en calcularla
     */
    void regitroLog(CargarFichero log, int prueba, vector<int> sol, int coste, double tiempo, int semilla){
        log.registraLogDatos(rutaLog, sol, coste);
        log.registraTiempo(rutaLog, tiempo, semilla);
    }
    
private:
    string rutaLog; // Ruta del archivo log
    
    /**
     * Función para registrar los datos en un archivo .log
     * @param log Objeto para crear el fichero.
     * @param prueba Número de la prueba por la que va.
     *              (De las 5 que hay que realizar con el DNI)
     * @param sol Vector con la solución
     * @param coste Coste de la solución
     * @param tiempo Tiempo en calcularla
     */
    void creaLog(CargarFichero log, int prueba){
        rutaLog = parametros[CARPETA_LOG] + "LOCAL_MEJOR-" + to_string(prueba) + "_" + parametros[NOMBRE_ARCHIVO] + ".log";;
        log.creaLog(rutaLog, prueba);
    }
    
    /**
     * Función para generar los posibles vecinos
     * @param log Objeto para registrar los cambios que se van realizando
     * @param costeActual Coste de la solución actual
     * @param sol Vector solución actual, se modifica por el mejor vecino si se mejora el coste
     * @param flu Matriz de flujo
     * @param dis Matriz de distancia
     * @return Devuelve True si se ha movido a algun vecino, False si no lo hace
     */
    bool generaCambios(CargarFichero& log, int& costeActual, vector<int>& sol, vector<vector<int>>& flu, vector<vector<int>>& dis){
        int mejorCoste = std::numeric_limits<int>::max();
        int pos = -1;
        vector<pair<int,int>> vecinos; // vector con las permutaciones creadas
        
        // Creo los diez posibles vecinos de forma aleatoria
        while( vecinos.size() < stoi(parametros[NUM_SOLU_LOCAL], nullptr, 10)){
            int pos1 = Randint(0,sol.size()-1);
            int pos2 = Randint(0,sol.size()-1);
            if(pos1 != pos2){
                // Compruebo que la solución no esta ya creada
                bool esta = false;
                for(int j = 0; j < vecinos.size(); j++){
                    if(vecinos[j].first == pos1 && vecinos[j].second == pos2){
                        esta = true;
                    }else if(vecinos[j].first == pos2 && vecinos[j].second == pos1){
                        esta = true;
                    }
                }
                
                if(!esta){
                    vecinos.push_back(pair<int,int>(pos1, pos2));
                    
                    int coste = calculaCoste2(costeActual,pos1, pos2, sol, flu, dis);
                    if(  coste < mejorCoste){ // Voy seleccionando la mejor solucion hasta el momento.
                        mejorCoste = coste;
                        pos = vecinos.size()-1;
                    }
                }
            }
        }
        
        if(pos != -1 && mejorCoste < costeActual){
            costeActual = calculaCoste2(costeActual, vecinos[pos].first, vecinos[pos].second, sol,flu, dis);
            log.registraMov(rutaLog, costeActual, vecinos[pos].first, vecinos[pos].second);
            swap(sol[vecinos[pos].first], sol[vecinos[pos].second]);//Al estar pasado referencia se modifica el original
            return true;
        }
        
        return false;
    }
};

#endif /* BLOCALMEJOR_H */

