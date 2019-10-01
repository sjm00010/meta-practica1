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
    
    void carga(string& archivo, vector<vector<int>>& flu, vector<vector<int>>& dis, bool sim){
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
            
            if(sim){
                // Leo los datos del fichero y los asigno a la matriz
                for(int i = 0; i < tam; i++){
                    for(int j = 0; j< tam; j++){
                        fe >> dis[i][j];
                    }
                }

                fe >> ws; //getline(cin, ws);

                for(int i = 0; i < tam; i++){
                    for(int j = 0; j< tam; j++){
                        fe >> flu[i][j];
                    }
                }
            }else{
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

        }
        fe.close();
        
        //Mostrar datos
        //mostrarMatrices(flu, dis); 
    }

private:
    void mostrarMatrices( vector<vector<int>>& flu, vector<vector<int>>& dis){
        cout << "--------- MATRIZ DE DISTANCIAS : ----------\n";
        for(int i = 0; i < dis.size(); i++){
            for(int j = 0; j< dis.size(); j++){
                printf(" %2d",dis[i][j]);
            }
            cout << "\n";
        } 
        
        cout << "\n";
        
        cout << "--------- MATRIZ DE FLUJOS : ----------\n";
        for(int i = 0; i < flu.size(); i++){
            for(int j = 0; j< flu.size(); j++){
                printf(" %2d",flu[i][j]);
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

#endif /* CARGARFICHERO_H */

