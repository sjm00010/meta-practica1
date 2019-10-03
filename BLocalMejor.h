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

#include "Parametros.h"

using namespace std;

class BLocalMejor {
public:
    
    /**
     * Algoritmo de Busqueda Local del Mejor
     * @param log Archivo .log para guardar los resultados
     * @param flu Matriz de flujos
     * @param dis Matriz de distancias
     * @return Devuelve el vector solución
     */
    vector<int> bLocalMejor(CargarFichero& log, vector<vector<int>>& flu, vector<vector<int>>& dis){
        // Creo la solución inicial de partida
        vector<int> solActual(flu.size());
        solActual = creaSolucion(flu.size());
        int costeAc = calculaCoste(solActual, flu, dis);
        cout << costeAc << endl;
        //log.registraLogDatos(solActual, costeAc);
                
        int k = 0; // Limite de 50000 evaluaciones
        int intentos = 0; // Limite de 100 intentos
        while( k < LIM_EVA_LOCAL){
            // Busco 10 vecinos 
            if(generaCambios(costeAc, solActual, flu, dis)){
                k++;
                intentos = 0;
                
                // escribo en el flichero la solucion encontrada
                cout << costeAc << " -- " << calculaCoste(solActual, flu, dis) << endl;
                //log.registraLogDatos(solActual, costeAc);
            }else{
                intentos++;
            }
            
            if(intentos == NUM_SOLU_LOCAL){
                cout << "Iteracion : " << k << "\n\n";
                return solActual;
            }
        }
        cout << "Iteracion : " << k << "\n";
        return solActual;
    }
    
private:
    
    int calculaCoste2(int costeViejo, int pos1, int pos2 ,vector<int> sol, vector<vector<int>>& flu, vector<vector<int>>& dis){
        
        for(int i = 0; i < sol.size(); i++){
            if(i != pos1 && i != pos2){
                costeViejo += flu[pos1][i] * (dis[sol[pos2]][sol[i]] - dis[sol[pos1]][sol[i]])+
                        flu[pos2][i] * (dis[sol[pos1]][sol[i]] - dis[sol[pos2]][sol[i]])+
                        flu[i][pos1] * (dis[sol[i]][sol[pos2]] - dis[sol[i]][sol[pos1]])+
                        flu[i][pos2] * (dis[sol[i]][sol[pos1]] - dis[sol[i]][sol[pos2]]);
            }
        }
        
        return costeViejo;
    }
    
    vector<int> creaSolucion(int tam){
        vector<int> solucion(tam);
        for(int i = 0; i < tam; i++){
            solucion[i]=i;
        }  

        for(int i = 0; i < tam; i++){
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
    
    bool generaCambios(int& costeActual, vector<int>& sol, vector<vector<int>>& flu, vector<vector<int>>& dis){
        int mejorCoste = std::numeric_limits<int>::max();
        int pos = -1;
        vector<pair<int,int>> vecinos; // vector con las permutaciones creadas
        
        // Creo los diez posibles vecinos de forma aleatoria
        while( vecinos.size() < NUM_SOLU_LOCAL){
            int pos1 = Randint(0,sol.size()-1);
            int pos2 = Randint(0,sol.size()-1);
            if(pos1 != pos2){
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
            swap(sol[vecinos[pos].first], sol[vecinos[pos].second]);//Al estar pasado referencia se modifica el original
            return true;
        }
        
        return false;
    }
};

#endif /* BLOCALMEJOR_H */

