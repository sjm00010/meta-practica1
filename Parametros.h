/* 
 * File:   Parametros.h
 * Author: PORTATIL
 *
 * Created on 27 de septiembre de 2019, 10:58
 */

#ifndef PARAMETROS_H
#define PARAMETROS_H

#include <string>

using namespace std;
    
    // Parametros necesarios que se necesitan
    string rutaParam = "parametros.txt";
    int numParam = 9; 

    // Parametros a cargar del archivo parametros.txt
    int DNI;
    int NUM_SOLU_LOCAL;
    int MAX_INTENTOS_LOCAL;
    int LIM_EVA_LOCAL;
    int NUM_PRUEBAS;
    int TEN_TABU;
    
    string carpetaDatos;
    string nombreArchivo;
    string carpetaLog;
    
#endif /* PARAMETROS_H */

