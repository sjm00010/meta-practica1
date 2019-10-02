/* 
 * File:   Parametros.h
 * Author: PORTATIL
 *
 * Created on 27 de septiembre de 2019, 10:58
 */

#ifndef PARAMETROS_H
#define PARAMETROS_H

#include <string>
#include <vector>

    int INT_MAX = +2147483647;
    int INT_MIN = -2147483648;
    int DNI = 26515294;
    int NUM_MOV_LOCAL = 10;
    int MAX_INTENTOS = 100;
    int LIM_EVA_LOCAL = 50000;
    
    std::string log = "resultados.log";
    std::string nombreCarpeta = "./_data/";
    std::vector<std::string> archivos = {
        "madrid01.dat", "madrid02.dat", "madrid03.dat", "madrid04.dat",
        "malaga01.dat", "malaga02.dat", "malaga03.dat", "malaga04.dat",
    };
#endif /* PARAMETROS_H */

