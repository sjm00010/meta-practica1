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

#include "Parametros.h"

using namespace std;

class CargarFichero {
public:
    
    /**
     * Función para cargar los parametros.
     * @param nombreArchivo Ruta del archivo con los parametros.
     */
    void cargaParametros(string nombreArchivo){
        ifstream fe(nombreArchivo); //Creo un flujo de entrada
        if(fe.good()){
            for(int i = 0; i < numParam; i++){
                // Quito el nombre de los parametros y el =
                fe >> ws;
                fe >> ws;

                switch(i){
                    case 0:
                        fe >> nombreCarpeta;
                        break;
                    case 1:
                        fe >> nombreArchivo;
                        break;
                    case 2:
                        fe >> DNI;
                        break;
                    case 3:
                        fe >> NUM_SOLU_LOCAL;
                        break;
                    case 4:
                        fe >> MAX_INTENTOS_LOCAL;
                        break;
                    case 5:
                        fe >> LIM_EVA_LOCAL;
                        break;
                }
            }
        }
        fe.close();   
    }
    
    /**
     * Función que carga los datos en las matrices.
     * @param archivo Ruta del archivo con los datos.
     * @param flu Matriz de flujos.
     * @param dis Matriz de distancias.
     * @param sim Variable que almacena si las matrices son simetricas.
     */
    void carga(string& archivo, vector<vector<int>>& flu, vector<vector<int>>& dis, bool& sim){
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
                    fe >> dis[i][j];
                }
            }

            fe >> ws; //getline(cin, ws);

            for(int i = 0; i < tam; i++){
                for(int j = 0; j< tam; j++){
                    fe >> flu[i][j];
                }
            }
        }
        fe.close();
        
        // Compruebo las matrices
        sim = comprueba(flu, dis);
        
        //Mostrar datos cargados
        //mostrarMatrices(flu, dis); 
    }
    
    /**
     * 
     * @param log
     * @param v
     * @param coste
     */
    void registraLogDatos(string log, vector<int>& v, int coste){
        // Crea un fichero de salida
        ofstream fs;
        fs.open(log, std::ios_base::app);
        fs << coste << " -->    ";
        for (int i = 0; i < v.size(); i++) {
            fs << "(" << i+1 <<")->" << v[i] << "   ";
            if( i % 9 == 0 && i > 0){
                fs << "\n           ";
            }
        }
        fs << "\n";
        fs.close();
    }
    
    void registraLogCadena(string cadena,string log){
        // Crea un fichero de salida
        ofstream fs;
        fs.open(log, std::ios_base::app);
        fs << cadena << "\n";
        fs.close();
    }

private:
    
    bool comprueba(vector<vector<int>>& flu, vector<vector<int>>& dis){
        bool cambio = false;
        bool sime = true;
        for(int i = 0; i < dis.size(); i++){
            for(int j = i+1; j < dis.size(); j++){
                if(dis[i][j] == 0 || dis[j][i] == 0){
                    cambio = true;
                }
                if(dis[i][j] != dis[j][i]){
                    sime = false;
                    // Finalizo el bucle
                    i = dis.size();
                    j = dis.size();
                }   
            }
        }
        
        if(cambio){
            //Cambio las matrices
            vector<vector<int>> temp(flu);
            flu = dis;
            dis = temp;
        }
        return sime;
    }
    
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
    
    void creaLog(string nombre){
        // Crea un fichero de salida
        //string nombre = nombreArchivo + "-" + alg + ".log";
        ofstream fs(nombre); 
        fs.close();
    }
};

#endif /* CARGARFICHERO_H */

