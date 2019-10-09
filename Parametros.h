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
string rutaParam = "../parametros.txt";
int numParam = 9;
vector<string> parametros;
// Parametros a cargar del archivo parametros.txt
enum valor {
    CARPETA_DATOS = 0,
    NOMBRE_ARCHIVO = 1,
    DNI = 2,
    NUM_SOLU_LOCAL = 3,
    MAX_INTENTOS_LOCAL = 4,
    LIM_EVA_LOCAL = 5,
    CARPETA_LOG = 6,
    NUM_PRUEBAS = 7,
    TEN_TABU = 8,
};

#endif /* PARAMETROS_H */

