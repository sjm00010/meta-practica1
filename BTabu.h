/* 
 * File:   BTabu.h
 * Author: sjm00010
 *
 * Created on 9 de octubre de 2019, 12:40
 */

#ifndef BTABU_H
#define BTABU_H

#include <vector>
#include <limits>
#include <list>

#include "Parametros.h"
#include "FuncionesComunes.h"
#include "random.h"

using namespace std;

class BTabu {
public:
    
    /**
     * Función que realiza la busqueda tabú
     * @param log Archivo .log para guardar los resultados
     * @param prueba Número de la prueba, de las ejecuciones con distinta semilla
     * @param flu Matriz de flujos
     * @param dis Matriz de distancias
     * @param sim Indica si la matriz es simétrica
     * @return Devuelve la solución de la busqueda tabú
     */
    vector<int> busquedaTabu(CargarFichero& log,int prueba, vector<vector<int>>& flu,
            vector<vector<int>>& dis, bool sim){
        
        // inicializo la matriz
        iniciaMatriz(flu.size());
        
        // Creo la solución inicial de partida
        vector<int> solActual(flu.size());
        vector<int> mejorSolucion(flu.size());
        solActual = creaSolucion(flu.size());
        mejorSolucion = solActual;
        int costeAc = calculaCoste(solActual, flu, dis, sim);
        int mejorCoste = costeAc;
        //creaLog(log, prueba);
        //log.registraLogDatos(rutaLog ,solActual, costeAc);
        
        int k = 0; // Limite de 50000 evaluaciones
        int intentos = 0; // Limite de 100 intentos
        while( k < stoi(parametros[LIM_EVA_LOCAL])){
            // Busco 10 vecinos 
            if(generaCambios(log, costeAc, solActual, flu, dis)){
                k++;
                intentos = 0;
                guardaMov(solActual);
            }else{
                intentos++;
            }
            
            if(intentos == stoi(parametros[NUM_SOLU_LOCAL])){              
                //Almaceno la mejor solución hasta el momento
                if(costeAc < mejorCoste){
                    mejorSolucion = solActual;
                    mejorCoste = costeAc;
                }
                
                solActual = nuevaSol();
                costeAc = calculaCoste(solActual, flu, dis, sim);
                
                //Generar nueva solución
                //Dudas :
                // -Las soluciones anteriores desde cuando se tienen en cuenta?? sol en rojo de teoria
                // -Como creo las soluciones nuevas al llegar a 100 intentos
                //soluciones, largo plazo, corto plazo
                //todas las memorias se reinician
            }
        }
        cout << "Iteracion : " << k << "\n";
        return solActual;
    }
    
private:
    // Matriz para guardar los resultados generados por la busqueda tabú
    vector<vector<int>> frecuencias;
    list<vector<int>> movRecientes;
    int posLista = 0;
    
    /**
     * Función para inicializar la matriz tabú
     * @param tam Tamaño de la matriz
     */
    void iniciaMatriz(int tam){
        frecuencias.resize(tam);
        movRecientes.resize(tam);
        for(int i = 0; i < tam; i++){
            frecuencias[i].resize(tam);
            for(int j = 0; j < tam; j++){
                frecuencias[i][j] = 0;
            }
        }
    }
    
//    /**
//     * Función para reinicializar la tenencia tabú cuando se llega al máximo
//     * de intentos.
//     * @param tam Tamaño de la matriz
//     */
//    void reiniciaMatriz(int tam){
//        for(int i = 0; i < tam; i++){
//            for(int j = 0; j < tam; j++){
//                frecuencias[i][j] = 0;
//            }
//        }
//    }
    
    /**
     * Función que registra la frecuencia con la que aparece una solución
     * @param pos1 Posición 1
     * @param pos2 Posición 2
     */
    void registraMov(int pos1, int pos2){
        // Cuidado con las asimetricas, esto solo va con las simetricas
        if(true){// cambiar por sim
            frecuencias[pos2][pos1]++;
            frecuencias[pos1][pos2]++;
        }else{
            
        }
        
    }
    
    /**
     * Función que guarda el movimiento generado
     * @param sol Movimiento generado
     */
    void guardaMov(vector<int> sol){
        list<vector<int>>::iterator it = movRecientes.begin();
        for(int i = 0; i < posLista; i++)
            it++;
        posLista++;
        movRecientes.insert(it, sol);
    }
    
    vector<int> diversificar(){
        vector<int> sol(frecuencias.size(), -1);
        for(int i = 0; i < frecuencias.size();i++){
            int pos;
            int menor = std::numeric_limits<int>::max();
            for(int j = i; j < frecuencias.size(); j++){
                if(frecuencias[i][j] < menor){
                    pos = j;
                    menor = frecuencias[i][j];
                }
            }
            sol[i] = pos;
        }
        return sol;
    }
    
    vector<int> intensificar(){
        vector<int> sol(frecuencias.size(), -1);
        for(int i = 0; i < frecuencias.size();i++){
            int pos;
            int mayor = -1;
            for(int j = 0; j < frecuencias.size(); j++){// Cuidado con asimetricos
                if(frecuencias[i][j] > mayor){
                    bool esta = false;
                    for(int k = 0; k < i; k++){
                        if(sol[k] == j){
                            esta = true;
                        }
                    } 
                    if(!esta){
                        pos = j;
                        mayor = frecuencias[i][j];
                    }
                }
            }
            sol[i] = pos;
        }
        return sol;
    }
    
    vector<int> nuevaSol(){
        float pro = Randfloat(0,1);
        if(pro > 0.5){
            return diversificar();
        }else{
            return intensificar();
        }
    }
    
    /**
     * Función que comprueba si la solución esta en la lista de movimientos tabú
     * @param sol Solución orignal
     * @param pos1 Posición 1
     * @param pos2 Posición 2
     * @return True si no esta, False en caso contrario
     */
    bool compruebaSol(vector<int> sol, int pos1, int pos2){
        swap(sol[pos1], sol[pos2]);//Al estar pasado por copia no se modifica el original
        
        for (list<vector<int>>::iterator it = movRecientes.begin(); it != movRecientes.end(); it++){
            if(*it == sol){
                return false;
            }
        }
        return true;
    }
    
    void reinicializacion(int tam){
        movRecientes.clear();
    }
    
    /**
     * Función para generar los posibles vecinos adaptada al tabú
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
        while( vecinos.size() < stoi(parametros[NUM_SOLU_LOCAL])){
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
                    
                    if(compruebaSol(sol, pos1, pos2)){ //Comprueba que no este en la lista de movimientos
                        int coste = calculaCoste2(costeActual,pos1, pos2, sol, flu, dis);
                        // Voy seleccionando la mejor solucion hasta el momento.
                        // Y que no sea una solución tabú
                        if(coste < mejorCoste){ 
                            mejorCoste = coste;
                            pos = vecinos.size()-1;
                        }
                    }

                }
            }
        }
        
        if(pos != -1 && mejorCoste < costeActual){
            costeActual = calculaCoste2(costeActual, vecinos[pos].first, vecinos[pos].second, sol,flu, dis);
            registraMov(vecinos[pos].first, vecinos[pos].second);
            
            //log.registraMov(rutaLog, costeActual, vecinos[pos].first, vecinos[pos].second);
            swap(sol[vecinos[pos].first], sol[vecinos[pos].second]);//Al estar pasado referencia se modifica el original
            guardaMov(sol);
            return true;
        }
        
        return false;
    }
};

#endif /* BTABU_H */