/* 
 * File:   main.cpp
 * Author: sjm00010
 *
 * Created on 24 de septiembre de 2019, 22:26
 */

#include "CargarFichero.h"
#include "Greedy.h"
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
    Aeropuerto a; // Estructura que almacena las soluciones
    
    // Cargar de datos
    CargarFichero carga;
    string ruta = nombreCarpeta + nombreArchivo;
    cout << "\n-------------------------------------------------\n";
    cout << "       CARGA DE : "+ nombreArchivo +"\n";
    cout << "-------------------------------------------------\n";
    carga.carga(ruta, a.flujo, a.distancia, a.simetrica);
    cout << " Carga completada con exito.\n";
    
    Set_random(DNI);
    
    int opcion = 0;
    cout << "\n¿ Que algoritmo deseas aplicar?" << endl;
    cout << "1. Greedy" << endl;
    cout << "2. Busqueda Local del Mejor" << endl;
    cout << "3. Busqueda Tabu" << endl;
    cout << "4. Salir" << endl;
    cin >> opcion;
    
    switch(opcion){
        case 1:
            
    }
    
    // Prueba

    
    Greedy alg;
    
    // Prueba greedy
        cout << "\n-------------------------------------------------\n";
        cout << "   SOLUCION GREEDY PARA : "+ nombreArchivo +"\n";
        cout << "-------------------------------------------------\n";
        
        // Inicio del contador
        //start_timers();
        
        a.sol = alg.greedy(a.flujo, a.distancia);
        
        // Fin del contador
        //tiempo = elapsed_time();
        
        
        // Escribir soluciones en fichero .log
        //carga.registraLogDatos(a.sol, alg.calculaCoste(a.sol, a.flujo, a.distancia));
        
        //Mostrar datos
        alg.mostrarResultado(a.sol, tiempo, a.flujo, a.distancia);
    
    // Prueba Local del mejor
        cout << "-------------------------------------------------\n";
        cout << "   SOLUCION LOCAL MEJOR PARA : "+ nombreArchivo +"\n";
        cout << "-------------------------------------------------\n";
        //alg.bLocalMejor(carga, a.flujo, a.distancia);
    
    return 0;
}

