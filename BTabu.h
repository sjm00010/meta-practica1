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
#include <iostream>

#include "Parametros.h"
#include "FuncionesComunes.h"
#include "random.h"
#include "CargarFichero.h"

using namespace std;

class BTabu {
public:
    /*
     * Dudas
     * ¿Todos los vecinos se meten en la lista tabu?
     * ¿Cojo el mejor de los 10 vecinos generados?¿O el mejor de los 1000? Mejor de las 1000
     * ¿Cuando reinicializo, a los 1000 vecinos? NO, si 100 veces empeoras la mejor solucion, entonces reinicializas
     * En caso afirmativo,¿Como cojo el mejor de los 1000 y reinizializo a la vez, es imposible?
     * En caso negativo,¿Cada cuanto reinicializo?
     * La lista tabu es del mismo tamaño de la tenencia, ¿misma lista de movimientos y tabu o mejor listas separadas? Mirar si se puede hacer todo en una lista
     * Estancamiento mejora con el mejor del momento no con el mejor de mejores
     */
    
    
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
        
        // Creo la los vectores que van a ir conteniendo las soluciones
        vector<int> mejorSolucion(flu.size()); // Mejor de mejores
        vector<int> mejorParcial(flu.size()); // Mejor del momento
        vector<int> mejorPeor(flu.size()); // Mejor solucion de todas las peores
        vector<int> solParcial(flu.size()); // Solucion actual
        
        // Creo la solución de partida
        mejorSolucion = creaSolucion(flu.size());
        mejorParcial = mejorSolucion;
        mejorPeor = mejorSolucion;
        solParcial = mejorSolucion;
        
        // Calculo el coste de la solución generada
        int mejorCoste = calculaCoste(mejorParcial, flu, dis, sim);
        int costeMejorParcial = mejorCoste;
        int costeMejorPeor = std::numeric_limits<int>::max(); // Para asi irme a la mejor solucion, aunque ninguna de las generadas sea mejor que la de partida
        int costeSol = mejorCoste;
        
        // Registro la solución de partida
        creaLog(log, prueba);
        log.registraLogSol(rutaLog ,mejorParcial, mejorCoste);
        
        int k = 0; // Limite de 50000 evaluaciones
        int intentos = 0; // Limite de 100 intentos
        int estancamiento = 0; // Limite del estancamiento, 100 entornos
        
        while( k <= stoi(parametros[LIM_EVA_LOCAL])){
            
            // Busco 10 vecinos, cada iteración se calcula con el vecino anterior
            generaCambios(log, costeSol, solParcial, k, intentos, flu, dis, sim);
            if(costeMejorParcial > costeSol){
                k++;  
                if(k == 25462)
                    cout << "ya" << endl;
                intentos = 0;
                estancamiento = 0;
                guardaMov(solParcial);
                mejorParcial = solParcial;
                costeMejorParcial = costeSol;
                
                // Compruebo la solución
                if( mejorCoste > costeMejorParcial){
                    mejorSolucion = mejorParcial;
                    mejorCoste = costeMejorParcial;
                }
                
            }else{
                intentos++;
                if( costeMejorPeor > costeSol){
                    mejorPeor = solParcial;
                    costeMejorPeor = costeSol;
                }
                solParcial = mejorParcial;
                costeSol = costeMejorParcial;
            }
            
            if(intentos == stoi(parametros[MAX_INTENTOS_LOCAL])){              
                k++;
                estancamiento++;
                intentos = 0;
                
                if(estancamiento == stoi(parametros[ESTANCAMIENTO])){
                    // Limpio la memoria
                    movRecientes.clear();
                    posLista = 0;
                    estancamiento = 0;
                    
                    log.registraElec(rutaLog,"Estancamiento");
                    
                    // Creo la nueva solucion, diversificando o intensificando
                    solParcial = nuevaSol(log);
                    mejorParcial = solParcial;
                    costeSol = calculaCoste(mejorParcial, flu, dis, sim);
                    costeMejorParcial = costeSol;
                    
                    // Resgistro la nueva solucion
                    log.registraLogSol(rutaLog ,mejorParcial, costeMejorParcial);
                }else{
                    // Cambio la solucion actual por la mejor de los 100 entornos
                    solParcial = mejorPeor;
                    costeSol = costeMejorPeor;                    
                }
                
                // Para asi irme a la mejor solucion, aunque ninguna de las generadas sea mejor que la de partida
                costeMejorPeor = std::numeric_limits<int>::max();
            }
        }
        

        string sol = " Diversificaciones : " + to_string(numDiv) + " | Intensificaciones : " + to_string(numInt) + "\n";
        log.registraElec(rutaLog, sol);
        return mejorSolucion;
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
        log.registraTiempoTabu(rutaLog, tiempo, semilla);
    }
    
private:
    // Matriz para guardar los resultados generados por la busqueda tabú
    vector<vector<int>> frecuencias;
    list<vector<int>> movRecientes;
    int posLista = 0;
    int numDiv = 0;
    int numInt = 0;
    
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
        rutaLog = parametros[CARPETA_LOG] + parametros[NOMBRE_ARCHIVO] + "-TABU_" + to_string(prueba) + ".log";;
        log.creaLog(rutaLog);
    }
    
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
    
    /**
     * Función que registra la frecuencia con la que aparece una solución
     * @param pos1 Posición 1
     * @param pos2 Posición 2
     */
    void registraMov(int pos1, int pos2, bool sim){
        if(sim){
            frecuencias[pos2][pos1]++;
            frecuencias[pos1][pos2]++;
        }else{
            frecuencias[pos1][pos2]++;
        }
        
    }
    
    /**
     * Función para diversificar
     * @return Solcuioón
     */
    vector<int> diversificar(){
        vector<int> sol(frecuencias.size(), -1);
        for(int i = 0; i < frecuencias.size();i++){
            int pos;
            int menor = std::numeric_limits<int>::max();
            for(int j = 0; j < frecuencias.size(); j++){// Cuidado con asimetricos
                bool esta = false;
                for(int k = 0; k < sol.size(); k++){
                    if(sol[k] == j){
                        esta = true;
                    }
                }
                if(frecuencias[i][j] <= menor && !esta){
                    pos = j;
                    menor = frecuencias[i][j];
                }
            }
            sol[i] = pos;
        }
        return sol;
    }
    
    /**
     * Función para intensificar
     * @return Solución
     */
    vector<int> intensificar(){
        vector<int> sol(frecuencias.size(), -1);
        for(int i = 0; i < frecuencias.size();i++){
            int pos;
            int mayor = -1;
            for(int j = 0; j < frecuencias.size(); j++){// Cuidado con asimetricos
                bool esta = false;
                for(int k = 0; k < sol.size(); k++){
                    if(sol[k] == j){
                        esta = true;
                    }
                }
                if(frecuencias[i][j] >= mayor && !esta){
                    pos = j;
                    mayor = frecuencias[i][j];
                }
            }
            sol[i] = pos;
        }
        return sol;
    }
    
    /**
     * Función que decide si se diversifica o se intensifica y devuelve la 
     * solución correspondiente
     * @return Solución de partida
     */
    vector<int> nuevaSol(CargarFichero& log){ 
        if( Randfloat(0,1) > 0.5 ){
            numDiv++;
            log.registraElec(rutaLog, "Diversificación");
            return diversificar();
        }else{
            log.registraElec(rutaLog, "Intensificación");
            numInt++;
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
        if(posLista > 0){
            for (list<vector<int>>::iterator it = movRecientes.begin(); it != movRecientes.end(); it++){
                if(*it == sol){
                    return false;
                }
            }
        }
        return true;
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
    
    /**
     * Función para generar los posibles vecinos adaptada al tabú
     * @param log Objeto para registrar los cambios que se van realizando
     * @param costeActual Coste de la solución actual
     * @param sol Vector solución actual, se modifica por el mejor vecino si se mejora el coste
     * @param flu Matriz de flujo
     * @param dis Matriz de distancia
     * @return Devuelve True si se ha movido a algun vecino, False si no lo hace
     */
    void generaCambios(CargarFichero& log, int& costeActual, vector<int>& sol,
            int it, int ent, vector<vector<int>>& flu, vector<vector<int>>& dis, bool sim){
        int mejorCoste = std::numeric_limits<int>::max();
        int pos = -1;
        vector<pair<int,int>> vecinos; // vector con las permutaciones creadas
        
        // Creo los diez posibles vecinos de forma aleatoria
        while( vecinos.size() < stoi(parametros[NUM_SOLU_LOCAL])){
            int pos1 = Randint(0,flu.size()-1);
            int pos2 = Randint(0,flu.size()-1);
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
        
        if(pos != -1){
            if(costeActual > mejorCoste){
                registraMov(vecinos[pos].first, vecinos[pos].second, sim);
                log.registraMovTabu(rutaLog, mejorCoste, vecinos[pos].first, vecinos[pos].second, it, ent);
                guardaMov(sol);
            }

            costeActual = mejorCoste;
            swap(sol[vecinos[pos].first], sol[vecinos[pos].second]);//Al estar pasado referencia se modifica el original
        }
    }
};

#endif /* BTABU_H */