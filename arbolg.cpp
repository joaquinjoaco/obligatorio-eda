// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Autores: Fabricio Garcia (5.473.797-0), Juan Garcia (5.282.647-8), Joaquin Gomez (5.398.934-6).
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

    // SOLO LA RAIZ (en el futuro solo el sistema, el arbol va por separado)
    // directorio actual.
    Sistema actual;
    // directorio anterior.
    Sistema anterior;
    // Cadena para el path.
    Cadena path = new (char[64]);

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
    raiz->actual = raiz;
    raiz->anterior = NULL;
    strcpy(raiz->path, NOMBRE_RAIZ);
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

Sistema crear_directorio(Cadena nombreDirectorio, Sistema directorioActual) {
    // crea un directorio.

    Sistema newDir = new (_sistema);
    strcpy(newDir->nombre, nombreDirectorio);
    newDir->tipo = _tipo(0);
    newDir->ph = NULL;
    newDir->sh = NULL;
    newDir->anterior = directorioActual;
    newDir->escritura = false;
    newDir->lectura = false;

    return newDir;
}

Sistema copiar_nodo(Sistema &copiar) {
    // Retorna un nodo que no comparte memoria con el que recibe y tiene los mismos datos.
    // Pre: nodo 'copiar' no vacio.
    Sistema nodo = new (_sistema);
    strcpy(nodo->nombre, copiar->nombre);
    nodo->tipo = copiar->tipo;
    strcpy(nodo->contenido, copiar->contenido);
    nodo->ph = copiar->ph;
    nodo->sh = copiar->sh;
    nodo->escritura = copiar->escritura;
    nodo->lectura = copiar->lectura;
    return nodo;
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

Sistema arbol_actual(Sistema s) {
    // retorna el directorio actual.
    // Pre: s no vacío.
    return s->actual;
}

Sistema arbol_anterior(Sistema s) {
    // retorna el directorio actual.
    // Pre: s no vacío.
    return s->anterior;
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

Cadena arbol_path(Sistema s) {
    // retorna el path actual.
    // Pre: s no vacio.
    return s->path;
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

void modificar_actual(Sistema &s, Sistema actual) {
    // modifica el directorio actual.
    // Pre: s no vacío.
    s->actual = actual;
}

void modificar_anterior(Sistema &s, Sistema anterior) {
    // cambia el directorio anterior.
    // Pre: s no vacío.
    s->anterior = anterior;
}

void modificar_ph(Sistema &s, Sistema q) {
    // modifica el puntero primer hijo del nodo dado.
    // Pre: s no vacío.
    s->ph = q;
}

void modificar_sh(Sistema &s, Sistema q) {
    // modifica el puntero siguiente hermano del nodo dado.
    // Pre: s no vacío.
    s->sh = q;
}

void sumar_path(Sistema &s, Cadena subdirectorio) {
    // modifica el path, concatenándole un nuevo nombre de subdirectorio.
    // Pre: s no vacío.
    strcat(s->path, "/");
    strcat(s->path, subdirectorio);
}

void restar_path(Sistema &s) {
    // modifica el path, removiéndole un nombre de subdirectorio.
    // Pre: s no vacío.

    //   s->path = strtok(s->path, "(/)\n");

    Cadena src = new (char[64]);
    Cadena dest = new (char[64]);

    // copiamos el contenido del path actual en 'src'.
    strcpy(src, s->path);
    // tomamos el largo de la cadena.
    int len = strlen(src);
    // invertimos la cadena para hacer un strtok posteriormente.
    for (int i = 0; i < len; i++) {
        dest[len - i - 1] = src[i];
    }
    // le hacemos un strtok para quitar el ultimo subdirectorio del path.
    dest = strtok(dest, "(/)\n");
    // invertimos la cadena nuevamente para que sea legible.
    for (int i = 0; i < len; i++) {
        s->path[len - i - 1] = dest[i];
    }

    delete src;
    delete dest;
}

Sistema arbol_insertar(Sistema &s, Sistema nuevoNodo) {
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
        aux->sh = nuevoNodo;

    } else {
        // No tiene primer hijo
        s->ph = nuevoNodo;
    }
    return s;
}

void arbol_eliminar(Sistema &s, Sistema &nodo, Sistema &nodoAnterior) {
    // Elimina un archivo o directorio del árbol en el directorio actual.

    if (nodoAnterior == NULL) {
        s->ph = nodo->sh;  // Actualiza el puntero del primer hijo del directorio
    } else {
        nodoAnterior->sh = nodo->sh;  // Actualiza el puntero del nodo anterior (el archivo )
    }

    if (arbol_tipo(nodo) == 1) {
        // El nodo es un archivo
        delete nodo;  // Libera la memoria del archivo
    } else {
        // El nodo es un directorio
        destruir_arbol(nodo->ph);  // Elimina los subdirectorios
        delete nodo;               // Libera la memoria del directorio
    }
}

void destruir_arbol(Sistema &s) {
    // destruye el arbol dado.
    if (!vacio(s)) {
        destruir_arbol(s->ph);
        destruir_arbol(s->sh);
        delete s;
    }

    s = NULL;
}

void eliminar_nodo(Sistema &s) {
    // Elimina un nodo cualquiera dado, sin condiciones, ni cambios en punteros.
    delete s;
    s = NULL;
}

int mayor(int a, int b) {
    // retorna el mayor de dos enteros.
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int arbol_profunidad(Sistema s) {
    // retorna la profundidad del arbol (para el caso de arboles generales
    // calculamos la profunidad como la cantidad de niveles). El primer nodo es
    // el nivel 1.

    if (s == NULL) {
        return 0;
    } else {
        return mayor(1 + arbol_profunidad(s->ph), arbol_profunidad(s->sh));
    }
}

void imprimir_nivel(Sistema s, int nivel) {
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

bool arbol_pertenece(Sistema s, Cadena nombre) {
    // retorna true si 'e' pertenece al arbol 'a'.

    if (s == NULL) {
        return false;
    } else if (strcmp(s->nombre, nombre) == 0) {
        return true;
    } else {
        return arbol_pertenece(s->ph, nombre) || arbol_pertenece(s->sh, nombre);
    }
}

bool arbol_pertenece_un_nivel(Sistema s, Cadena nombre) {
    // Retorna true si 'nombre' pertenece al nivel actual del árbol 's'.
    s = s->ph;
    while (s != NULL) {
        if (strcmp(s->nombre, nombre) == 0) {
            return true;
        }
        s = s->sh;
    }
    return false;
}

void mostrar_estructura_recursiva(Sistema s, Cadena path) {
    // Se muestra en pantalla la estructura de los archivos y directorios desde cualquier lugar del sistema de manera recursiva
    // Mostrando al principio los archivos del directorio y luego los subdirectorios del mismo.

    // Almacenar nombres de archivos y directorios en arreglos
    Cadena archivos[MAX_NOMBRE];
    Cadena directorios[MAX_NOMBRE];

    int numArchivos = 0;
    int numDirectorios = 0;

    // Procesar los hijos del directorio actual
    Sistema subdirectorio = arbol_ph(s);
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
        Sistema subdir = arbol_ph(s);
        while (subdir != NULL) {
            if (strcmp(arbol_nombre(subdir), directorios[i]) == 0) {
                mostrar_estructura_recursiva(subdir, aux_path);
            }
            subdir = arbol_sh(subdir);
        }

        delete[] aux_path;
    }
}