#ifndef LISTA_H
#define LISTA_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// lista.h
// Definiciones de la lista.

#include "definiciones.h"
#include "sistema.h"

typedef struct _nodo_lista *Lista;

Lista crear();
// Crea la lista vacía.

Lista cons(Sistema ar, Lista l);
// Inserta el archivo al principio de la lista l.

bool isEmpty(Lista l);
// Retorna true si l es vacía, false en caso contrario.

Sistema archivo(Lista l);
// Retorna el archivo del primer elemento de la lista.

Cadena lista_nombre(Lista l);
// Retorna la cadena nombre del primer elemento de la lista.

Lista tail(Lista l);
// Retorna la lista sin su primer elemento.
// Pre: l no vacía.

Lista insertar(Sistema archivo, Lista l);
// Retorna la lista fruto de insertar ordenadamente el elemento x en la lista ordenada l.
// l no comparte memoria con la lista resultado.

void lista_imprimir(Lista l);
// Imprime los elementos de la lista.

#endif