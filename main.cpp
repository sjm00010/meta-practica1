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
#include "BLocalMejor.h"
#include "Timer.h"


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
    Aeropuerto a; // Estructura que almacena las soluciones
    Timer crono;
    
    // Cargar de datos
    CargarFichero carga;
    carga.cargaParametros();
    string ruta = carpetaDatos + nombreArchivo;
    cout << "\n-------------------------------------------------\n";
    cout << "       CARGA DE : "+ nombreArchivo +"\n";
    cout << "-------------------------------------------------\n";
    carga.carga(ruta, a.flujo, a.distancia, a.simetrica);
    cout << " Carga completada con exito.\n";
    
    
    Set_random(DNI);
   
    
    //cout << numDigitos(DNI);
    
    // Prueba greedy
    Greedy alg;
    cout << "\n-------------------------------------------------\n";
    cout << "   SOLUCION GREEDY PARA : "+ nombreArchivo +"\n";
    cout << "-------------------------------------------------\n";

    // Inicio del contador
    crono.start();

    a.sol = alg.greedy(a.flujo, a.distancia);

    // Fin del contador
    crono.stop();

    // Escribir soluciones en fichero .log
    //carga.registraLogDatos(a.sol, alg.calculaCoste(a.sol, a.flujo, a.distancia));

    //Mostrar datos
    mostrarResultado(a.sol, tiempo, a.flujo, a.distancia);
    
    // Prueba Local del mejor
    BLocalMejor blocal;
    cout << "-------------------------------------------------\n";
    cout << "   SOLUCION LOCAL MEJOR PARA : "+ nombreArchivo +"\n";
    cout << "-------------------------------------------------\n";
    a.sol = blocal.bLocalMejor(carga, a.flujo, a.distancia);
    
    //Mostrar datos
    mostrarResultado(a.sol, tiempo, a.flujo, a.distancia);
    
    return 0;
}

