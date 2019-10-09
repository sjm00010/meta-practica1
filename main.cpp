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
#include "FuncionesComunes.h"
#include "BLocalMejor.h"
#include "Timer.h"

//This is a commen//This is a commentt
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * Estructura de apoyo que representa el aeropuerto
 */
struct Aeropuerto{
    vector<vector<int>> flujo;
    vector<vector<int>> distancia;
    bool simetrica;
};

int main(int argc, char** argv) {
    // Variables locales
    Aeropuerto a; // Estructura que almacena las soluciones
    Timer crono;
    vector<int> sol;
    int coste;
    double tiempo;

    // Cargar de datos
    CargarFichero carga;
    carga.cargaParametros();
    string ruta = parametros[CARPETA_DATOS] + parametros[NOMBRE_ARCHIVO];
    cout << "\n-------------------------------------------------\n";
    cout << "       CARGA DE : "+ parametros[NOMBRE_ARCHIVO] +"\n";
    cout << "-------------------------------------------------\n";
    carga.carga(ruta, a.flujo, a.distancia, a.simetrica);
    cout << " Carga completada con exito.\n";


    // Prueba greedy
    Greedy alg;
    cout << "\n-------------------------------------------------\n";
    cout << "   SOLUCION GREEDY PARA : "+ parametros[NOMBRE_ARCHIVO] +"\n";
    cout << "-------------------------------------------------\n";

    // Inicio del contador
    crono.start();

    sol = alg.greedy(a.flujo, a.distancia);

    // Fin del contador
    crono.stop();

    // Escribir soluciones en fichero .log
    coste = calculaCoste(sol, a.flujo, a.distancia, a.simetrica);
    tiempo = crono.getElapsedTimeInMilliSec();
    alg.regitroLog(carga, 0, sol, coste, tiempo);

    //Mostrar datos
    mostrarResultado(sol, tiempo, a.flujo, a.distancia, coste);

    for(int i = 1; i <= stoi(parametros[NUM_PRUEBAS], nullptr, 10); i++){
        // Prueba Local del mejor
        BLocalMejor alg2;
        cout << "-------------------------------------------------\n";
        cout << "   SOLUCION " + to_string(i) +" LOCAL MEJOR PARA : "+ parametros[NOMBRE_ARCHIVO] +"\n";
        cout << "-------------------------------------------------\n";

        // Establezco la semilla para cada prueba
        Set_random(calculaSemilla(i));

        // Inicio del contador
        crono.start();

        sol = alg2.bLocalMejor(carga, i, a.flujo, a.distancia, a.simetrica);

        // Fin del contador
        crono.stop();

        // Escribir soluciones en fichero .log
        coste = calculaCoste(sol, a.flujo, a.distancia, a.simetrica);
        tiempo = crono.getElapsedTimeInMilliSec();
        alg2.regitroLog(carga, i, sol, coste, tiempo, calculaSemilla(i));

        //Mostrar datos
        mostrarResultado(sol, tiempo, a.flujo, a.distancia, coste);
    }
    

    
    return 0;
}

