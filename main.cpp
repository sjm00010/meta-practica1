/* 
 * File:   main.cpp
 * Author: sjm00010
 *
 * Created on 24 de septiembre de 2019, 22:26
 */

#include "CargarFichero.h"
#include "Algoritmos.h"
#include "timer.h"


#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * 
 */
struct Aeropuerto{
    string nombre;
    vector<vector<int>> flujo;
    vector<vector<int>> distancia;
    bool simetrica;
    vector<int> sol;
};

int main(int argc, char** argv) {
    // Variables de archivos
    string nombreCarpeta = "./_data/";
    vector<string> archivos = {
        "madrid01.dat", "madrid02.dat", "madrid03.dat", "madrid04.dat",
        "malaga01.dat", "malaga02.dat", "malaga03.dat", "malaga04.dat",
    };
    Set_random(DNI);
    
    vector<Aeropuerto> a(archivos.size());
    
    // Prueba
    CargarFichero carga;
    for(int i = 0; i < archivos.size(); i++){
        string ruta = nombreCarpeta + archivos[i];
        a[i].nombre = archivos[i];
        cout << "-------------------------------------------------\n";
        cout << "       CARGA DE : "+ a[i].nombre +"\n";
        cout << "-------------------------------------------------\n";
        carga.carga(ruta, a[i].flujo, a[i].distancia);
        //Mostrar datos
        //carga.mostrarMatrices(a[i].flujo,a[i].distancia,a[i].tama);
        a[i].simetrica = (i<4);
        cout << "\n";
    }
    
    Algoritmos alg;
    
    // Prueba greedy
    for(int i = 0; i < archivos.size(); i++){
        cout << "-------------------------------------------------\n";
        cout << "   SOLUCION GREEDY PARA : "+ a[i].nombre +"\n";
        cout << "-------------------------------------------------\n";
        
        a[i].sol = alg.greedy(a[i].flujo, a[i].distancia);
        //Mostrar datos
        //alg.mostrarGreedy(a[i].sol);
    }
    
    // Prueba Local del mejor
    for(int i=0; i < archivos.size(); i++){
        cout << "-------------------------------------------------\n";
        cout << "   SOLUCION LOCAL MEJOR PARA : "+ a[i].nombre +"\n";
        cout << "-------------------------------------------------\n";
        alg.localMejor(a[i].flujo, a[i].distancia);
    }
    
    return 0;
}

