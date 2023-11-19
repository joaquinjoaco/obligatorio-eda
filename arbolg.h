#ifndef ARBOLG_H
#define ARBOLG_H

//  Estructuras de Datos y Algoritmos - Curso 2023
//  Tecnologo en Informatica FIng - DGETP - UTEC
//
// Autores: Fabricio Garcia (5.473.797-0), Juan Garcia (5.282.647-8), Joaquin Gomez (5.398.934-6).
//
//  Trabajo Obligatorio
//  arbolg.h
//  Definiciones de arbol general (finitario).

#include "definiciones.h"

typedef struct _arbolg *Arbolg;

Arbolg crear_raiz();
// crea la RAIZ vacía.

Arbolg crear_archivo(Cadena nombreArchivo);
// crea un archivo vacío.

Arbolg crear_directorio(Cadena nombreDirectorio, Arbolg directorioActual);
// crea un directorio vacío.

Arbolg copiar_nodo(Arbolg &copiar);
// Retorna un nodo con los mismos datos que el nodo que recibe y no comparte memoria con el mismo.
// Pre: nodo 'copiar' no vacio.

bool vacio(Arbolg s);
// retorna true si el arbol es vacío, false en caso contrario.

Arbolg arbol_ph(Arbolg s);
// retorna el primer hijo.
// Pre: s no vacío.

Arbolg arbol_sh(Arbolg s);
// retorna el siguiente hermano.
// Pre: s no vacío.

Arbolg arbol_anterior(Arbolg s);
// retorna el anterior.
// Pre: s no vacío.

Cadena arbol_nombre(Arbolg s);
// retorna el nombre del archivo.
// Pre: s no vacío.

bool arbol_escritura(Arbolg s);
// retorna el valor del permiso de escritura.
// Pre: s no vacío.

void modificar_escritura(Arbolg &s, bool valor);
// modifica el valor del permiso de escritura.
// Pre: s no vacío.

void modificar_anterior(Arbolg &s, Arbolg anterior);
// cambia el directorio anterior del sistema.
// Pre: s no vacío.

void modificar_ph(Arbolg &s, Arbolg q);
// modifica el puntero primer hijo del nodo dado.
// Pre: s no vacío.

void modificar_sh(Arbolg &s, Arbolg q);
// modifica el puntero siguiente hermano del nodo dado.
// Pre: s no vacío.

Cadena arbol_contenido(Arbolg s);
// retorna el valor del contenido.
// Pre: s no vacío.

TipoNodo arbol_tipo(Arbolg s);
// retorna el tipo del nodo.
// Pre: s no vacío.

// Cadena arbol_path(Sistema s);
// // retorna el path actual.
// // Pre: s no vacio.

Arbolg arbol_insertar(Arbolg &s, Arbolg nodo);
// Inserta un nodo como último sigiente hermano en el primer nivel del arbol.

void arbol_eliminar(Arbolg &s, Arbolg &nodo, Arbolg &nodoAnterior);
// Elimina un archivo o directorio del árbol en el directorio actual.

void destruir_arbol(Arbolg &s);
// Destruye el arbol dado.

void eliminar_nodo(Arbolg &s, Arbolg &nodo, Arbolg &nodoAnterior);
// Elimina un nodo cualquiera dado, sin condiciones, ni cambios en punteros.

int mayor(int a, int b);
// Retorna el mayor de dos enteros.

int arbol_profunidad(Arbolg s);
// Retorna la profundidad del árbol.

void imprimir_nivel(Arbolg s, int nivel);
// Imprime el nivel dado del arbol general.

bool arbol_pertenece(Arbolg s, Cadena nombre);
// Retorna true si la cadena 'nombre' pertenece al arbol 's'.

bool arbol_pertenece_un_nivel(Arbolg s, Cadena nombre);
// Retorna true si 'nombre' pertenece al nivel actual del árbol 's'.

void mostrar_estructura_recursiva(Arbolg s, Cadena path);
// Se muestra en pantalla la estructura de los archivos y directorios desde cualquier lugar del sistema de manera recursiva
// Mostrando al principio los archivos del directorio y luego los subdirectorios del mismo.

#endif