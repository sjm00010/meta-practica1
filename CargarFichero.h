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
    void cargaParametros() {
        ifstream fe;
        try {
            fe.open(rutaParam);
            string linea;
            while (!fe.eof()) {
                fe.ignore(256, ' ');
                fe.ignore(256, ' ');
                fe >> linea;
                parametros.push_back(linea.c_str());
            }
        } catch (ifstream::failure e){
            std:cerr << "Error reading file. Perhaps route is incorrect?" << endl;
        }
    }

    /**
     * Función que carga los datos en las matrices.
     * @param archivo Ruta del archivo con los datos.
     * @param flu Matriz de flujos.
     * @param dis Matriz de distancias.
     * @param sim Variable que almacena si las matrices son simetricas.
     */
    void carga(string &archivo, vector<vector<int>> &flu, vector<vector<int>> &dis, bool &sim) {
        ifstream fe(archivo); //Creo un flujo de entrada

        if (fe.good()) {
            int tam;
            fe >> tam; // Recojo el tamaño de las matrices

            // Con el tamaño, redimensiono las matrices para adaptarlas al problema.
            flu.resize(tam);
            dis.resize(tam);
            for (int i = 0; i < tam; i++) {
                flu[i].resize(tam);
                dis[i].resize(tam);
            }

            // Leo los datos del fichero y los asigno a la matriz
            for (int i = 0; i < tam; i++) {
                for (int j = 0; j < tam; j++) {
                    fe >> dis[i][j];
                }
            }

            fe >> ws; //getline(cin, ws);

            for (int i = 0; i < tam; i++) {
                for (int j = 0; j < tam; j++) {
                    fe >> flu[i][j];
                }
            }
        }
        fe.close();

        // Compruebo las matrices
        sim = comprueba(flu, dis);
    }

    /**
     * Función para añadir una cadena de texto al log
     * @param elec Cadena a añadir
     */
    void registraCadena(string log, string elec){
        ofstream fs;
        fs.open(log, std::ios_base::app);
        fs << "\n" << elec << "\n";
    }
        
    /**
     * Función que registra la nueva solución de partida con su coste
     * @param log Nombre del archivo .log
     * @param v Vector solución
     * @param coste Coste de la solución
     */
    void registraLogSol(string log, vector<int> &v, int coste) {
        // Abre un fichero de salida
        ofstream fs;
        fs.open(log, std::ios_base::app);
        fs << "----------------------------------------------------\n";
        fs << " Solución inicial : \n ";
        for (int i = 0; i < v.size(); i++) {
            fs << "(" << i + 1 << ")->" << v[i]+1 << "   ";
            if (i % 9 == 0 && i > 0) {
                fs << "\n ";
            }
        }
        fs << "\n";
        fs << "\n Coste : " << coste << "\n";
        fs.close();
    }

    /**
     * Función que registra la solución con su coste
     * @param log Nombre del archivo .log
     * @param v Vector solución
     * @param coste Coste de la solución
     */
    void registraLogDatos(string log, vector<int> &v, int coste) {
        // Abre un fichero de salida
        ofstream fs;
        fs.open(log, std::ios_base::app);
        fs << "----------------------------------------------------\n";
        fs << " Mejor solución : \n ";
        for (int i = 0; i < v.size(); i++) {
            fs << "(" << i + 1 << ")->" << v[i]+1 << "   ";
            if (i % 9 == 0 && i > 0) {
                fs << "\n ";
            }
        }
        fs << "\n";
        fs << "\n Coste : " << coste << "\n";
        fs.close();
    }

    /**
     * Función para registrar el tiempo del algoritmo.
     * @param log Ruta del archivo .log
     * @param t Tiempo
     */
    void registraTiempo(string log, double t, int semilla) {
        ofstream fs;
        fs.open(log, std::ios_base::app);
        fs << "----------------------------------------------------\n";
        fs << "Tiempo :  " << t << " ms \n";
        fs << "Semilla : " << semilla << "\n";
    }

    /**
     * Función para registrar el tiempo del algoritmo tabú.
     * @param log Ruta del archivo .log
     * @param t Tiempo
     */
    void registraTiempoTabu(string log, double t, int semilla) {
        ofstream fs;
        fs.open(log, std::ios_base::app);
        fs << "----------------------------------------------------\n";
        fs << "Tiempo :  " << t << " s \n";
        fs << "Semilla : " << semilla << "\n";
    }

    /**
     * Funcion para registrar los movimientos realizados
     * @param log Ruta del .log
     * @param coste Coste de la solución actual
     * @param pos1 Posición 1
     * @param pos2 Posición 2
     * @param it N. de iteración
     */
    void registraMov(string log, int coste, int pos1, int pos2, int it) {
        ofstream fs;
        fs.open(log, std::ios_base::app);
        fs << "----------------------------------------------------\n";
        fs << " Movimiento : " << "[" << pos1 << ", " << pos2 << "]\n";
        fs << " Coste :      " << coste << "\n";
        fs << " Iteración :  " << it << "\n";
    }
        
    /**
     * Funcion para registrar los movimientos realizados en tabú
     * @param log Ruta del .log
     * @param coste Coste de la solución actual
     * @param pos1 Posición 1
     * @param pos2 Posición 2
     * @param it N. de iteración
     */
    void registraMovTabu(string log, int coste, int pos1, int pos2, int it, int ent) {
        ofstream fs;
        fs.open(log, std::ios_base::app);
        fs << "----------------------------------------------------\n";
        fs << " Movimiento : " << "[" << pos1 << ", " << pos2 << "]\n";
        fs << " Coste :      " << coste << "\n";
        fs << " Entorno :    " << ent << "\n";
        fs << " Iteración :  " << it << "\n";
    }

    /**
     * Función que crea el archivo .log
     * @param nombre Nombre del archivo
     */
    void creaLog(string nombreAr) {
        // Crea un fichero de salida
        ofstream fs(nombreAr);
        fs.close();
    }

private:

    /**
     * Función que comprueba tanto a simetria como la correcta atribución de las matrices
     * @param flu Matriz de flujos
     * @param dis Matriz de distancias
     * @return True si es simétrica, False si no lo es.
     */
    bool comprueba(vector<vector<int>> &flu, vector<vector<int>> &dis) {
        bool cambio = false;
        bool sime = true;
        for (int i = 0; i < dis.size(); i++) {
            for (int j = i + 1; j < dis.size(); j++) {
                if (dis[i][j] == 0 || dis[j][i] == 0) {
                    cambio = true;
                }
                if (dis[i][j] != dis[j][i]) {
                    sime = false;
                    // Finalizo el bucle
                    i = dis.size();
                    j = dis.size();
                }
            }
        }

        if (cambio) {
            //Cambio las matrices
            vector<vector<int>> temp(flu);
            flu = dis;
            dis = temp;
        }
        return sime;
    }
};

#endif /* CARGARFICHERO_H */

