/* 
 * File:   main.cpp
 * Author: sjm00010
 *
 * Created on 24 de septiembre de 2019, 22:26
 */

#include "CargarFichero.h"
#include "Algoritmos.h"
#include "random.h"
#include "Parametros.h"


#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * 
 */
struct Aeropuerto{
    vector<vector<int>> flujo;
    vector<vector<int>> distancia;
    bool simetrica;
    vector<int> sol;
};

int main(int argc, char** argv) {
    // Variables locales
    double tiempo = 0;

    Set_random(DNI);
    
    Aeropuerto a;
    
    // Prueba
    CargarFichero carga;
    string ruta = nombreCarpeta + nombreArchivo;
    cout << "\n-------------------------------------------------\n";
    cout << "       CARGA DE : "+ nombreArchivo +"\n";
    cout << "-------------------------------------------------\n";
    carga.carga(ruta, a.flujo, a.distancia, a.simetrica);
    cout << " Carga completada con exito.\n";
    
    Algoritmos alg;
    
    // Prueba greedy
    for(int i = 0; i < archivos.size(); i++){
        cout << "\n-------------------------------------------------\n";
        cout << "   SOLUCION GREEDY PARA : "+ a[i].nombre +"\n";
        cout << "-------------------------------------------------\n";
        
        // Inicio del contador
        //start_timers();
        
        a[i].sol = alg.greedy(a[i].flujo, a[i].distancia);
        
        // Fin del contador
        //tiempo = elapsed_time();
        
        
        // Escribir soluciones en fichero .log
        carga.registraLogAlg("GREEDY", a[i].nombre);
        carga.registraLogDatos(a[i].sol, alg.calculaCoste(a[i].sol, a[i].flujo, a[i].distancia));
        
        //Mostrar datos
        alg.mostrarResultado(a[i].sol, tiempo, a[i].flujo, a[i].distancia);
    }
    
    // Prueba Local del mejor
    for(int i=0; i < archivos.size(); i++){
        cout << "-------------------------------------------------\n";
        cout << "   SOLUCION LOCAL MEJOR PARA : "+ a[i].nombre +"\n";
        cout << "-------------------------------------------------\n";
        carga.registraLogAlg("LOCAL MEJOR", a[i].nombre);
        alg.bLocalMejor(carga, a[i].flujo, a[i].distancia);
    }
    
    return 0;
}

