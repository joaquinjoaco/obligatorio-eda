#ifndef LISTA_H
#define LISTA_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Autores: Fabricio Garcia (5.473.797-0), Juan Garcia (5.282.647-8), Joaquin Gomez (5.398.934-6).
//
// Trabajo Obligatorio
// lista.h
// Definiciones de la lista.

#include "definiciones.h"
#include "sistema.h"

typedef struct _nodo_lista *Lista;

Lista crear();
// Crea la lista vacía.

Lista cons(Sistema s, Lista l);
// Inserta el nodo (archivo o directorio) al inicio de l.

bool isEmpty(Lista l);
// Retorna true si l es vacía, false en caso contrario.

Sistema nodo(Lista l);
// Retorna el nodo (archivo o directorio) del primer elemento de la lista.
// Pre: l no vacía.

Cadena lista_nombre(Lista l);
// Retorna la cadena nombre del primer elemento de la lista.

Lista tail(Lista l);
// Retorna el "resto" de la lista.
// Pre: l no vacia.

Lista insertar(Sistema archivo, Lista l);
// Retorna la lista fruto de insertar ordenadamente el nodo 'n' en la lista.
// El nodo puede ser tanto un directorio como un archivo.
// La lista resultante no comparte memoria con la lista resultado.

void imprimir_lista(Lista l);
// Imprime los elementos de la lista.

#endif