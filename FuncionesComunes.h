/* 
 * File:   FuncionesComunes.h
 * Author: sjm00010
 *
 * Created on 9 de octubre de 2019, 12:58
 */

#ifndef FUNCIONESCOMUNES_H
#define FUNCIONESCOMUNES_H

#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Funciones comunes 
    
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
        for(int i = 0; i < v.size(); i++){
            printf(" (%2d) -%3d  ",i+1, v[i]+1);
            if (i % 5 == 0 && i > 0 && i != v.size()-1){
                cout << "\n";
            }
        } 
        cout << "\n\n";
        cout << "   El coste de la solucion es : " << coste << "\n";
        cout << "   Tiempo empleado : " << t << " ms\n";
    }
    
    /**
     * Función que muestra por consola la solción calculada.
     * @param v Vector con la solución.
     * @param t Tiempo que tarda el algoritmo.
     * @param flu Matriz de flujos
     * @param dis Matriz de distancias
     */
    void mostrarResultadoTabu( vector<int>& v, double t, vector<vector<int>>& flu, vector<vector<int>>& dis, int coste){
        for(int i = 0; i < v.size(); i++){
            printf(" (%2d) -%3d  ",i+1, v[i]+1);
            if (i % 5 == 0 && i > 0 && i != v.size()-1){
                cout << "\n";
            }
        } 
        cout << "\n\n";
        cout << "   El coste de la solucion es : " << coste << "\n";
        cout << "   Tiempo empleado : " << t << " s\n";
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
    
    /**
     * Función que cambia la semilla automaticamente
     * @param prueba Numero de las 5 pruebas por el se se esta ejecutando
     * @return Nueva semilla
     */
    int calculaSemilla(int prueba){
        int dni = stoi(parametros[DNI], nullptr, 10);
        int d = numDigitos(dni) - --prueba;
        d = pow(10,d);
        return (int)(dni%d*pow(10,prueba)+(int)dni/d);
    }
    
    /**
     * Función que calcula el coste para el intercambio de dos posiciones del vector solcución.
     * @param costeViejo Coste de la solucion actual
     * @param pos1 Posicion a inntercambiar
     * @param pos2 La otra posición a intercambiar
     * @param sol Vector solución
     * @param flu Matriz de flujo
     * @param dis Matriz de distancia
     * @return  Devuelve el coste de esa solución.
     */
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
    
    /**
     * Función para crear una solución aleatoria de partida
     * @param tam Tamaño del vector solución
     * @return Devuelve el vector solucion creado.
     */
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
        
        return solucion;
    }
    
    

#endif /* FUNCIONESCOMUNES_H */

