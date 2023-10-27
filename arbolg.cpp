// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// sistema.c
// Modulo de Implementacion de funciones relacionadas a arbol general.

#include "arbolg.h"

#include <string.h>

#include <iostream>

#include "sistema.h"

using namespace std;

struct _sistema {
    // aquí deben figurar los campos que usted considere necesarios para
    // manipular el sistema de directorios Se deberan crear nuevos modulos

    // LA ESTRUCTURA OPTADA ES LA DE TIPO ARBOL GENERAL
    // Tipo de nodo
    TipoNodo tipo;  //  "DIR" || "FILE"
    // --------------------------------

    // Nombre del archivo/directorio
    Cadena nombre = new (char[MAX_NOMBRE]);
    // -----------------------------

    // Primer hijo (para directorios)
    Sistema ph;
    // ------------------------------
    // Siguiente hermano (para directorios y archivos)
    Sistema sh;
    // -----------------------------------------------

    // Atributos para archivos
    Cadena contenido = new (char[TEXTO_MAX]);
    bool lectura;
    bool escritura;
    // -----------------------
};

Sistema crear_raiz() {
    // crea un directorio vacío.

    Sistema raiz = new (_sistema);
    raiz->tipo = _tipo(0);
    strcpy(raiz->nombre, NOMBRE_RAIZ);
    raiz->ph = NULL;
    raiz->sh = NULL;
    strcpy(raiz->contenido, "");
    raiz->lectura = true;
    raiz->escritura = true;

    return raiz;
}

Sistema crear_archivo(Cadena nombreArchivo) {
    // crea un archivo.

    Sistema newFile = new (_sistema);
    strcpy(newFile->nombre, nombreArchivo);
    newFile->tipo = _tipo(1);
    strcpy(newFile->contenido, "");
    newFile->ph = NULL;
    newFile->sh = NULL;
    newFile->escritura = true;
    newFile->lectura = true;

    return newFile;
}

bool vacio(Sistema s) {
    // retorna true si el arbol es vacío, false en caso contrario.
    return (s == NULL);
}

Sistema arbol_ph(Sistema s) {
    // retorna el primer hijo.
    // Pre: s no vacio.
    return s->ph;
}

Sistema arbol_sh(Sistema s) {
    // retorna el siguiente hermano.
    // Pre: s no vacio.
    return s->sh;
}

Cadena arbol_nombre(Sistema s) {
    // retorna el nombre del archivo.
    // Pre: s no vacio.
    return s->nombre;
}

Cadena arbol_contenido(Sistema s) {
    // retorna el valor del contenido.
    // Pre: s no vacio.
    return s->contenido;
}

TipoNodo arbol_tipo(Sistema s) {
    // retorna el tipo del nodo.
    // Pre: s no vacio.
    return s->tipo;
}

bool arbol_escritura(Sistema s) {
    // retorna el valor del permiso de escritura.
    // Pre: s no vacio.
    return s->escritura;
}

void modificar_escritura(Sistema &s, bool valor) {
    // modifica el valor del permiso de escritura.
    // Pre: s no vacio.
    s->escritura = valor;
}

Sistema arbol_insertar(Sistema &s, Sistema newFile) {
    // inserta un nodo como ultimo sigiente
    // hermano en el primer nivel del arbol.
    if (!vacio(arbol_ph(s))) {
        // Tiene un primer hijo
        Sistema aux = s;
        aux = arbol_ph(aux);  // vamos al primer hijo.

        // vamos al ultimo hermano (o ultimo elemento de la lista).
        while (!vacio(arbol_sh(aux))) {
            aux = arbol_sh(aux);
        }

        // apuntamos el ultimo hermano al nuevo archivo
        aux->sh = newFile;

    } else {
        // No tiene primer hijo
        s->ph = newFile;
    }
    return s;
}

Sistema arbol_eliminar(Sistema &s, Sistema &archivo, Sistema &archivoAnterior) {
    // Elimina un archivo de un arbol.
    // Eliminar el archivo del directorio actual
    if (archivoAnterior == NULL) {
        s->ph = archivo->sh;  // El archivo es el primer hijo del directorio
    } else {
        archivoAnterior->sh = archivo->sh;  // El archivo no es el primer hijo
    }

    delete archivo;  // Liberar memoria del archivo
    return s;
}

void destruir_arbol(Sistema &s) {
    // destruye el arbol dado.

    if (!vacio(s)) {
        destruir_arbol(s->ph);
        destruir_arbol(s->sh);
        delete s;
    }
}

int mayor(int a, int b) {
    // retorna el mayor de dos enteros.
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int arbol_profunidad(Sistema &s) {
    // retorna la profundidad del arbol (para el caso de arboles generales
    // calculamos la profunidad como la cantidad de niveles). El primer nodo es
    // el nivel 1.

    if (s == NULL) {
        return 0;
    } else {
        return mayor(1 + arbol_profunidad(s->ph), arbol_profunidad(s->sh));
    }
}

void imprimir_nivel(Sistema &s, int nivel) {
    // imprime el nivel dado del arbol general.
    if (s != NULL) {
        if (nivel != 0) {
            // se va ramificando con las llamadas recursivas.
            imprimir_nivel(s->ph, nivel - 1);
            imprimir_nivel(s->sh, nivel);

        } else {
            cout << s->nombre << "   ";
            // Si es un archivo mostramos sus permisos.
            if (s->tipo == 1) {
                if (s->escritura) {
                    cout << "Lectura/Escritura";
                } else {
                    cout << "Lectura";
                }
            }
        }

        cout << endl;
        imprimir_nivel(s->sh, nivel);
    }
}

bool arbol_pertenece(Sistema &s, Cadena nombre) {
    // retorna true si 'e' pertenece al arbol 'a'.

    if (s == NULL) {
        return false;
    } else if (strcmp(s->nombre, nombre) == 0) {
        return true;
    } else {
        return arbol_pertenece(s->ph, nombre) || arbol_pertenece(s->sh, nombre);
    }
}
