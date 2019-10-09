/* 
 * File:   BTabu.h
 * Author: sjm00010
 *
 * Created on 9 de octubre de 2019, 12:40
 */

#ifndef BTABU_H
#define BTABU_H

#include <vector>

using namespace std;

class BTabu {
public:
    vector<int> busquedaTabu(CargarFichero& log,int prueba, vector<vector<int>>& flu,
            vector<vector<int>>& dis, bool sim){
        
        // inicializo la matriz
        iniciaMatriz(flu.size());
        
        
    }
private:
    // Matriz para guardar los resultados generados por la busqueda tabu
    vector<vector<int>> tabu;
    
    /**
     * Función para inicializar la matriz tabu
     * @param tam Tamaño de la matriz
     */
    void iniciaMatriz(int tam){
        tabu.resize(tam);
        for(int i = 0; i < tam; i++){
            tabu[i].resize(tam);
            for(int j = 0; j < tam; j++){
                tabu[i][j] = 0;
            }
        }
    }
};

#endif /* BTABU_H */

