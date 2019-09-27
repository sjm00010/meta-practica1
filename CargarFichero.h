/* 
 * File:   CargarFichero.h
 * Author: sjm00010
 *
 * Created on 25 de septiembre de 2019, 11:59
 */

#ifndef CARGARFICHERO_H
#define CARGARFICHERO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class CargarFichero {
public:
    
    void carga(string& archivo, vector<vector<int>>& flu, vector<vector<int>>& dis){
        ifstream fe(archivo); //Creo un flujo de entrada

        if(fe.good()){
            int tam;
            fe >> tam; // Recojo el tamaño de las matrices
            
            // Con el tamaño, redimensiono las matrices para adaptarlas al problema.
            flu.resize(tam);
            dis.resize(tam);
            for(int i = 0; i < tam; i++){
                flu[i].resize(tam);
                dis[i].resize(tam);
            }
            
            // Leo los datos del fichero y los asigno a la matriz
            for(int i = 0; i < tam; i++){
                for(int j = 0; j< tam; j++){
                    fe >> flu[i][j];
                }
            }
            
            fe >> ws; //getline(cin, ws);
            
            for(int i = 0; i < tam; i++){
                for(int j = 0; j< tam; j++){
                    fe >> dis[i][j];
                }
            } 
        }
        fe.close();
    }
    
    void mostrarMatrices( vector<vector<int>>& flu, vector<vector<int>>& dis, int& tam){
        cout << "--------- MATRIZ DE DISTANCIAS : ----------\n";
        for(int i = 0; i < tam; i++){
            for(int j = 0; j< tam; j++){
                printf(" %d",dis[i][j]);
            }
            cout << "\n";
        } 
        
        cout << "\n";
        
        cout << "--------- MATRIZ DE FLUJOS : ----------\n";
        for(int i = 0; i < tam; i++){
            for(int j = 0; j< tam; j++){
                printf(" %d",flu[i][j]);
            }
            cout << "\n";
        }
         
    }
};

#endif /* CARGARFICHERO_H */

