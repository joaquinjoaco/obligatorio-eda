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
    Sistema archivo;
    Lista sig;
};

Lista crear() {
    // Crea la lista vacia.
    return NULL;
}

Lista cons(Sistema ar, Lista l) {
    // Inserta n al inicio de l.
    Lista aux = new (_nodo_lista);
    aux->archivo = ar;
    aux->sig = l;
    return aux;
}

bool isEmpty(Lista l) {
    // Retorna true si l es vacia, false en caso contrario.
    return (l == NULL);
}

Sistema archivo(Lista l) {
    // Retorna el archivo del primer elemento de la lista.
    // Pre: l no vacia.
    return l->archivo;
}

Cadena lista_nombre(Lista l) {
    // Retorna la cadena nombre del primer elemento de la lista.
    return arbol_nombre(l->archivo);
}

Lista tail(Lista l) {
    // Retorna el "resto" de la lista.
    // Pre: l no vacia.
    return l->sig;
}

Lista insertar(Sistema ar, Lista l) {
    // Retorna la lista fruto de insertar ordenadamente datos del archivo 'ar' en la
    // lista ordenada l. l no comparte memoria con la lista resultado.

    if (isEmpty(l))
        // caso que la lista es vacía.
        return cons(ar, NULL);
    else if (strcmp(arbol_nombre(archivo(l)), arbol_nombre(ar)) == 0)
        // caso en el que el archivo ya existe en la lista.
        return l;
    else if (strcmp(arbol_nombre(archivo(l)), arbol_nombre(ar)) < 0)
        // caso que el archivo actual sea menor alfabéticamente que el que se quiere insertar.
        return cons(archivo(l), insertar(ar, tail(l)));
    else if (isEmpty(tail(l)))
        // caso que llegamos al último elemento de l
        return cons(ar, cons(archivo(l), NULL));
    else {
        char nombreArchivoActual = tolower(arbol_nombre(archivo(l))[0]);
        char nombreArchivoNuevo = tolower(arbol_nombre(ar)[0]);
        if (nombreArchivoActual == nombreArchivoNuevo) {
            return cons(ar, cons(archivo(l), tail(l)));
        } else {
            return cons(ar, cons(archivo(l), insertar(archivo(tail(l)), tail(l))));
        }
    }
}

void imprimir_lista(Lista l) {
    // Imprime l en la salida estandar.

    cout << NOMBRE_RAIZ << endl
         << endl;

    while (!isEmpty(l)) {
        cout << arbol_nombre(archivo(l)) << "   ";
        // Si es un archivo mostramos sus permisos.
        if (arbol_tipo(archivo(l)) == 1) {
            if (arbol_escritura(archivo(l))) {
                cout << "Lectura/Escritura" << endl;
            } else {
                cout << "Lectura" << endl;
            }
        }
        l = tail(l);
    }
    cout << endl;
}
