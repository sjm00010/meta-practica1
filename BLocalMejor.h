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

using namespace std;

class BLocalMejor {
public:
    vector<int> bLocalMejor(CargarFichero& log, vector<vector<int>>& flu, vector<vector<int>>& dis){
        // Creo la solución inicial de partida
        vector<int> solActual(flu.size());
        solActual = creaSolucion(flu.size());
        int costeAc = calculaCoste(solActual, flu, dis);
        cout << costeAc << endl;
        log.registraLogCadena(" SOLUCION INICIAL ");
        log.registraLogDatos(solActual, costeAc);
                
        int k = 0; // Limite de 50000 evaluaciones
        int intentos = 0; // Limite de 100 intentos
        while( k < LIM_EVA_LOCAL){
            // Busco 10 vecinos 
            if(generaCambios(costeAc, solActual, flu, dis)){
                k++;
                intentos = 0;
                
                // escribo en el flichero la solucion encontrada
                log.registraLogCadena(" SOLUCION N. " + to_string(k));
                cout << costeAc << " -- " << calculaCoste(solActual, flu, dis) << endl;
                log.registraLogDatos(solActual, costeAc);
            }else{
                intentos++;
            }
            
            if(intentos == 10){
                cout << k << "\n";
                return solActual;
            }
        }
        cout << k << "\n";
        return solActual;
    }
private:

    int calculaDifCoste (int pos1, int pos2 ,vector<int> solInicial, vector<vector<int>>& flu, vector<vector<int>>& dis){
        int dif = 0;
        
        for (int i = 0; i < solInicial.size(); i++){
                if(i != pos1 || i != pos2){
                    dif -= flu[i][pos1]*dis[solInicial[i]][solInicial[pos1]] + 
                            flu[i][pos2]*dis[solInicial[i]][solInicial[pos2]];
            }
        }
        
        // Como lo paso por copia no se ve modificado fuera de la funcion
        swap(solInicial[pos1], solInicial[pos2]);
        
        for (int i = 0; i < solInicial.size(); i++){
                if(i != pos1 || i != pos2){
                    dif += flu[i][pos1]*dis[solInicial[i]][solInicial[pos1]] + 
                            flu[i][pos2]*dis[solInicial[i]][solInicial[pos2]];
            }
        }
        return dif;
    }
    
    int calculaCoste2(int costeViejo, int pos1, int pos2 ,vector<int> solInicial, vector<vector<int>>& flu, vector<vector<int>>& dis){
        int dif = 0;
        
        for (int i = 0; i < solInicial.size(); i++){
                if(i != pos1 || i != pos2){
                    dif += flu[i][pos1]*dis[solInicial[i]][solInicial[pos1]] + 
                            flu[i][pos2]*dis[solInicial[i]][solInicial[pos2]]+
                            flu[pos1][i]*dis[solInicial[pos1]][solInicial[i]] + 
                            flu[pos2][i]*dis[solInicial[pos2]][solInicial[i]];
            }
        }
        
        //dif *= 2;
        
        // Como lo paso por copia no se ve modificado fuera de la funcion
        swap(solInicial[pos1], solInicial[pos2]);
        int suma = 0;
        for (int i = 0; i < solInicial.size(); i++){
                if(i != pos1 || i != pos2){
                    suma += flu[i][pos1]*dis[solInicial[i]][solInicial[pos1]] + 
                            flu[i][pos2]*dis[solInicial[i]][solInicial[pos2]]+
                            flu[pos1][i]*dis[solInicial[pos1]][solInicial[i]] + 
                            flu[pos2][i]*dis[solInicial[pos2]][solInicial[i]];
            }
        }
        
        //suma *= 2;
        
        return costeViejo - dif + suma;
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
        int mejorCoste = 0;
        int pos = -1;
        vector<pair<int,int>> vecinos; // vector con las permutaciones creadas
        
        // Creo los diez posibles vecinos de forma aleatoria
        while( vecinos.size() < NUM_MOV_LOCAL){
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
                    int coste = calculaDifCoste(pos1, pos2, sol, flu, dis);
                    if(  coste < mejorCoste){ // Voy seleccionando la mejor solucion hasta el momento.
                        mejorCoste = coste;
                        pos = vecinos.size()-1;
                    }
                }
            }
        }
        
        if(pos != -1){
            swap(sol[vecinos[pos].first], sol[vecinos[pos].second]);//Al estar pasado referencia se modifica el original
            costeActual = calculaCoste2(costeActual, vecinos[pos].first, vecinos[pos].second, sol,flu, dis);
            return true;
        }
        
        return false;
    }
};

#endif /* BLOCALMEJOR_H */

