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
#include "random.h"
#include "CargarFichero.h"

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
    
    vector<int> bLocalMejor(CargarFichero& log, vector<vector<int>>& flu, vector<vector<int>>& dis){
        // Creo la solución inicial de partida
        vector<int> solActual(flu.size());
        solActual = creaSolucion(flu.size());
        int costeAc = calculaCoste(solActual, flu, dis);
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
                log.registraLogCadena(" SOLUCION N. " + k);
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
                            flu[i][pos2]*dis[solInicial[i]][solInicial[pos2]];
            }
        }
        
        // Como lo paso por copia no se ve modificado fuera de la funcion
        swap(solInicial[pos1], solInicial[pos2]);
        
        for (int i = 0; i < solInicial.size(); i++){
                if(i != pos1 || i != pos2){
                    dif -= flu[i][pos1]*dis[solInicial[i]][solInicial[pos1]] + 
                            flu[i][pos2]*dis[solInicial[i]][solInicial[pos2]];
            }
        }
        return costeViejo - dif;
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
    
    vector<int> intercambia(vector<int> solInicial, int pos1, int pos2){
        swap(solInicial[pos1],solInicial[pos2]);
        return solInicial;
    }

};

#endif /* ALGORITMOS_H */

