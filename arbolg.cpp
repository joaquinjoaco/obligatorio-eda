// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Autores: Fabricio Garcia (5.473.797-0), Juan Garcia (5.282.647-8), Joaquin Gomez (5.398.934-6).
//
// Trabajo Obligatorio
// sistema.c
// Modulo de Implementacion de funciones relacionadas al arbol general (finitario).

#include "arbolg.h"

#include <string.h>

#include <iostream>

#include "sistema.h"

using namespace std;

struct _arbolg {
    // aquí deben figurar los campos que usted considere necesarios para
    // manipular el sistema de directorios. Se deberan crear nuevos modulos.

    // LA ESTRUCTURA OPTADA ES LA DE TIPO ARBOL GENERAL
    // Tipo de nodo
    TipoNodo tipo;  //  "DIR" || "FILE".
    // --------------------------------

    // Nombre del archivo/directorio.
    Cadena nombre = new (char[MAX_NOMBRE]);
    // -----------------------------

    // Primer hijo (para directorios).
    Arbolg ph;
    // directorio anterior (para directorios).
    Arbolg anterior;
    // ------------------------------
    // Siguiente hermano (para directorios y archivos).
    Arbolg sh;
    // -----------------------------------------------

    // Atributos para archivos.
    Cadena contenido = new (char[TEXTO_MAX]);
    bool lectura;
    bool escritura;
    // -----------------------
};

Arbolg crear_raiz() {
    // crea la RAIZ vacía.

    Arbolg raiz = new (_arbolg);
    raiz->tipo = _tipo(0);
    strcpy(raiz->nombre, NOMBRE_RAIZ);

    raiz->ph = NULL;
    raiz->sh = NULL;
    raiz->anterior = NULL;  // Raíz no tiene anterior.

    strcpy(raiz->contenido, "");
    raiz->lectura = true;
    raiz->escritura = true;

    return raiz;
}

Arbolg crear_archivo(Cadena nombreArchivo) {
    // crea un archivo vacío.

    Arbolg newFile = new (_arbolg);
    strcpy(newFile->nombre, nombreArchivo);
    newFile->tipo = _tipo(1);
    strcpy(newFile->contenido, "");
    newFile->ph = NULL;
    newFile->sh = NULL;
    newFile->escritura = true;
    newFile->lectura = true;

    return newFile;
}

Arbolg crear_directorio(Cadena nombreDirectorio, Arbolg directorioActual) {
    // crea un directorio vacío.

    Arbolg newDir = new (_arbolg);
    strcpy(newDir->nombre, nombreDirectorio);
    newDir->tipo = _tipo(0);
    newDir->ph = NULL;
    newDir->sh = NULL;
    newDir->anterior = directorioActual;
    newDir->escritura = false;
    newDir->lectura = false;

    return newDir;
}

Arbolg copiar_nodo(Arbolg &copiar) {
    // Retorna un nodo con los mismos datos que el nodo que recibe y no comparte memoria con el mismo.
    // Pre: nodo 'copiar' no vacio.

    Arbolg nodo = new (_arbolg);
    strcpy(nodo->nombre, copiar->nombre);
    nodo->tipo = copiar->tipo;
    strcpy(nodo->contenido, copiar->contenido);
    nodo->ph = copiar->ph;
    nodo->sh = copiar->sh;
    nodo->escritura = copiar->escritura;
    nodo->lectura = copiar->lectura;
    return nodo;
}

bool vacio(Arbolg s) {
    // retorna true si el arbol es vacío, false en caso contrario.
    return (s == NULL);
}

Arbolg arbol_ph(Arbolg s) {
    // retorna el primer hijo.
    // Pre: s no vacio.
    return s->ph;
}

Arbolg arbol_sh(Arbolg s) {
    // retorna el siguiente hermano.
    // Pre: s no vacio.
    return s->sh;
}

// Arbolg arbol_actual(Arbolg s) {
//     // retorna el directorio actual.
//     // Pre: s no vacío.
//     return s->actual;
// }

Arbolg arbol_anterior(Arbolg s) {
    // retorna el directorio actual.
    // Pre: s no vacío.
    return s->anterior;
}

Cadena arbol_nombre(Arbolg s) {
    // retorna el nombre del archivo.
    // Pre: s no vacio.
    return s->nombre;
}

Cadena arbol_contenido(Arbolg s) {
    // retorna el valor del contenido.
    // Pre: s no vacio.
    return s->contenido;
}

TipoNodo arbol_tipo(Arbolg s) {
    // retorna el tipo del nodo.
    // Pre: s no vacio.
    return s->tipo;
}

// Cadena arbol_path(Sistema s) {
//     // retorna el path actual.
//     // Pre: s no vacio.
//     return s->path;
// }

bool arbol_escritura(Arbolg s) {
    // retorna el valor del permiso de escritura.
    // Pre: s no vacio.
    return s->escritura;
}

void modificar_escritura(Arbolg &s, bool valor) {
    // modifica el valor del permiso de escritura.
    // Pre: s no vacio.
    s->escritura = valor;
}

void modificar_anterior(Arbolg &s, Arbolg anterior) {
    // cambia el directorio anterior del sistema.
    // Pre: s no vacío.
    s->anterior = anterior;
}

void modificar_ph(Arbolg &s, Arbolg q) {
    // modifica el puntero primer hijo del nodo dado.
    // Pre: s no vacío.
    s->ph = q;
}

void modificar_sh(Arbolg &s, Arbolg q) {
    // modifica el puntero siguiente hermano del nodo dado.
    // Pre: s no vacío.
    s->sh = q;
}

Arbolg arbol_insertar(Arbolg &s, Arbolg nuevoNodo) {
    // Inserta un nodo como último sigiente
    // hermano en el primer nivel del arbol.

    if (!vacio(arbol_ph(s))) {
        // Tiene un primer hijo
        Arbolg aux = s;
        aux = arbol_ph(aux);  // vamos al primer hijo.

        // vamos al último hermano (o último elemento de la lista).
        while (!vacio(arbol_sh(aux))) {
            aux = arbol_sh(aux);
        }

        // apuntamos el último hermano al nuevo archivo
        aux->sh = nuevoNodo;

    } else {
        // No tiene primer hijo
        s->ph = nuevoNodo;
    }

    return s;
}

void arbol_eliminar(Arbolg &s, Arbolg &nodo, Arbolg &nodoAnterior) {
    // Elimina un archivo o directorio del árbol en el directorio actual.

    if (nodoAnterior == NULL) {
        s->ph = nodo->sh;  // Actualiza el puntero del primer hijo del directorio.
    } else {
        nodoAnterior->sh = nodo->sh;  // Actualiza el puntero del nodo anterior.
    }

    if (arbol_tipo(nodo) == 1) {
        // El nodo es un archivo.
        delete nodo;  // Libera la memoria del nodo archivo con delete.
    } else {
        // El nodo es un directorio,
        destruir_arbol(nodo->ph);  // Elimina los subdirectorios recursivamente.
        delete nodo;               // Luego libera la memoria del nodo directorio con delete.
    }
}

void destruir_arbol(Arbolg &s) {
    // Destruye el arbol dado.
    if (!vacio(s)) {
        destruir_arbol(s->ph);
        destruir_arbol(s->sh);
        delete s;
    }

    s = NULL;
}

void eliminar_nodo(Arbolg &s, Arbolg &nodo, Arbolg &nodoAnterior) {
    // Elimina un nodo cualquiera dado, sin condiciones, ni cambios en punteros.
    if (nodoAnterior == NULL) {
        s->ph = nodo->sh;  // Actualiza el puntero del primer hijo del directorio
    } else {
        nodoAnterior->sh = nodo->sh;  // Actualiza el puntero del nodo anterior (el archivo )
    }

    delete nodo;
    nodo = NULL;
}

int mayor(int a, int b) {
    // Retorna el mayor de dos enteros.
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int arbol_profunidad(Arbolg s) {
    // Retorna la profundidad del árbol.

    if (s == NULL) {
        return 0;
    } else {
        return mayor(1 + arbol_profunidad(s->ph), arbol_profunidad(s->sh));
    }
}

void imprimir_nivel(Arbolg s, int nivel) {
    // Imprime el nivel dado del arbol general.
    if (s != NULL) {
        if (nivel != 0) {
            // se va "ramificando" con las llamadas recursivas.
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

bool arbol_pertenece(Arbolg s, Cadena nombre) {
    // Retorna true si la cadena 'nombre' pertenece al arbol 's'.

    if (s == NULL) {
        return false;
    } else if (strcmp(s->nombre, nombre) == 0) {
        return true;
    } else {
        return arbol_pertenece(s->ph, nombre) || arbol_pertenece(s->sh, nombre);
    }
}

bool arbol_pertenece_un_nivel(Arbolg s, Cadena nombre) {
    // Retorna true si la cadena 'nombre' pertenece al nivel actual del árbol 's'.
    s = s->ph;
    while (s != NULL) {
        if (strcmp(s->nombre, nombre) == 0) {
            return true;
        }
        s = s->sh;
    }
    return false;
}

void mostrar_estructura_recursiva(Arbolg s, Cadena path) {
    // Se muestra en pantalla la estructura de los archivos y directorios desde cualquier lugar del sistema de manera recursiva
    // Mostrando al principio los archivos del directorio y luego los subdirectorios del mismo.

    // Almacenar nombres de archivos y directorios en arreglos
    Cadena archivos[MAX_NOMBRE];
    Cadena directorios[MAX_NOMBRE];

    int numArchivos = 0;
    int numDirectorios = 0;

    // Procesar los hijos del directorio actual
    Arbolg subdirectorio = arbol_ph(s);
    while (subdirectorio != NULL) {
        if (arbol_tipo(subdirectorio) == 1) {
            // Es un archivo, almacenar su nombre
            archivos[numArchivos] = arbol_nombre(subdirectorio);
            numArchivos++;
        } else {
            // Es un directorio, almacenar su nombre
            directorios[numDirectorios] = arbol_nombre(subdirectorio);
            numDirectorios++;
        }

        // Avanzar al siguiente subdirectorio
        subdirectorio = arbol_sh(subdirectorio);
    }

    // Mostrar primero los archivos y luego los directorios
    for (int i = 0; i < numArchivos; i++) {
        // Construir la ruta completa del archivo
        Cadena aux_path = new char[strlen(path) + strlen("/") + strlen(archivos[i]) + 1];
        strcpy(aux_path, path);
        strcat(aux_path, "/");
        strcat(aux_path, archivos[i]);
        cout << aux_path << endl;
        delete[] aux_path;
    }

    for (int i = 0; i < numDirectorios; i++) {
        // Construir la ruta completa del subdirectorio
        Cadena aux_path = new char[strlen(path) + strlen("/") + strlen(directorios[i]) + 1];
        strcpy(aux_path, path);
        strcat(aux_path, "/");
        strcat(aux_path, directorios[i]);
        cout << aux_path << endl;

        // Llamada recursiva con la ruta del subdirectorio
        Arbolg subdir = arbol_ph(s);
        while (subdir != NULL) {
            if (strcmp(arbol_nombre(subdir), directorios[i]) == 0) {
                mostrar_estructura_recursiva(subdir, aux_path);
            }
            subdir = arbol_sh(subdir);
        }

        delete[] aux_path;
    }
}