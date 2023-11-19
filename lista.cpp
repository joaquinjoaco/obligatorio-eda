// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Autores: Fabricio Garcia (5.473.797-0), Juan Garcia (5.282.647-8), Joaquin Gomez (5.398.934-6).
//
// Trabajo Obligatorio
// lista.c
// Modulo de Implementacion de funciones relacionadas a lista simple.

#include "lista.h"

#include <string.h>

#include <iostream>

#include "arbolg.h"
#include "definiciones.h"
#include "sistema.h"

using namespace std;

struct _nodo_lista {
    Arbolg nodo;  // archivo o directorio.
    Lista sig;
};

Lista crear() {
    // Crea la lista vacia.
    return NULL;
}

Lista cons(Arbolg n, Lista l) {
    // Inserta el nodo (archivo o directorio) al inicio de l.
    Lista aux = new (_nodo_lista);
    aux->nodo = n;
    aux->sig = l;
    return aux;
}

bool isEmpty(Lista l) {
    // Retorna true si l es vacia, false en caso contrario.
    return (l == NULL);
}

Arbolg nodo(Lista l) {
    // Retorna el nodo (archivo o directorio) del primer elemento de la lista.
    // Pre: l no vacia.
    return l->nodo;
}

Cadena lista_nombre(Lista l) {
    // Retorna la cadena nombre del primer elemento de la lista.
    return arbol_nombre(l->nodo);
}

Lista tail(Lista l) {
    // Retorna el "resto" de la lista.
    // Pre: l no vacia.
    return l->sig;
}

Lista insertar(Arbolg n, Lista l) {
    // Retorna la lista fruto de insertar ordenadamente el nodo 'n' en la lista.
    // El nodo puede ser tanto un directorio como un archivo.
    // La lista resultante no comparte memoria con la lista resultado.

    if (isEmpty(l))
        // caso que la lista es vacía.
        return cons(n, NULL);
    else if (strcmp(arbol_nombre(nodo(l)), arbol_nombre(n)) == 0)
        // caso en el que el nodo ya existe en la lista.
        return l;
    else if (strcmp(arbol_nombre(nodo(l)), arbol_nombre(n)) < 0)
        // caso que el nombre del nodo de la lista sea menor alfabéticamente que el que se quiere insertar.
        return cons(nodo(l), insertar(n, tail(l)));
    else if (isEmpty(tail(l)))
        // caso que llegamos al último elemento de la lista.
        return cons(n, cons(nodo(l), NULL));
    else {
        char nombreArchivoActual = tolower(arbol_nombre(nodo(l))[0]);
        char nombreArchivoNuevo = tolower(arbol_nombre(n)[0]);
        if (nombreArchivoActual == nombreArchivoNuevo) {
            return cons(n, cons(nodo(l), tail(l)));
        } else {
            return cons(n, cons(nodo(l), insertar(nodo(tail(l)), tail(l))));
        }
    }
}

void imprimir_lista(Lista l) {
    // Imprime l en la salida estandar.

    while (!isEmpty(l)) {
        cout << arbol_nombre(nodo(l)) << "   ";
        // Si es un archivo mostramos sus permisos.
        if (arbol_tipo(nodo(l)) == 1) {
            if (arbol_escritura(nodo(l))) {
                cout << "Lectura/Escritura";
            } else {
                cout << "Lectura";
            }
        }
        cout << endl;
        l = tail(l);
    }
    cout << endl;
}
