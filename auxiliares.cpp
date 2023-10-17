// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// sistema.c
// Modulo de Implementacion de funciones auxiliares.

// #include "auxiliares.h"

// #include <string.h>

// #include <iostream>

// #include "sistema.h"

// using namespace std;

// int mayor(int a, int b) {
//     // retorna el mayor de dos enteros.
//     if (a > b) {
//         return a;
//     } else {
//         return b;
//     }
// }

// int arbol_profunidad(Sistema &s) {
//     // retorna la profundidad del arbol (para el caso de arboles generales calculamos la
//     // profunidad como la cantidad de niveles). El primer nodo es el nivel 1.

//     if (s == NULL) {
//         return 0;
//     } else {
//         return mayor(1 + arbol_profunidad(s->ph), arbol_profunidad(s->sh));
//     }
// }

// void imprimir_nivel(Sistema &s, int nivel) {
//     // imprime el nivel dado del arbol general.
//     if (s != NULL) {
//         if (nivel != 0) {
//             // se va ramificando con las llamadas recursivas.
//             imprimir_nivel(s->ph, nivel - 1);
//             imprimir_nivel(s->sh, nivel);

//         } else {
//             cout << s->nombre << "   ";
//             // Si es un archivo mostramos sus permisos.
//             if (s->tipo == 1) {
//                 if (s->escritura) {
//                     cout << "Lectura/Escritura";
//                 } else {
//                     cout << "Lectura";
//                 }
//             }
//         }

//         cout << endl;
//         imprimir_nivel(s->sh, nivel);
//     }
// }

// bool arbol_pertenece(Sistema &s, Cadena nombre) {
//     // retorna true si 'e' pertenece al arbol 'a'.

//     if (s == NULL) {
//         return false;
//         // } else if (s->nombre == nombre) {
//         // no es case sensitive, permite la
//         // creacion de 'Hola.mp3' y 'hola.mp3'.
//     } else if (strcmp(s->nombre, nombre) == 0) {
//         return true;
//     } else {
//         return arbol_pertenece(s->ph, nombre) || arbol_pertenece(s->sh, nombre);
//     }
// }
