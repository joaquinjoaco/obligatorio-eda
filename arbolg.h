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

typedef struct _sistema *Sistema;

Sistema crear_raiz();
// crea la RAIZ vacía.

Sistema crear_archivo(Cadena nombreArchivo);
// crea un archivo vacío.

Sistema crear_directorio(Cadena nombreDirectorio, Sistema directorioActual);
// crea un directorio vacío.

Sistema copiar_nodo(Sistema &copiar);
// Retorna un nodo con los mismos datos que el nodo que recibe y no comparte memoria con el mismo.
// Pre: nodo 'copiar' no vacio.

bool vacio(Sistema s);
// retorna true si el arbol es vacío, false en caso contrario.

Sistema arbol_ph(Sistema s);
// retorna el primer hijo.
// Pre: s no vacío.

Sistema arbol_sh(Sistema s);
// retorna el siguiente hermano.
// Pre: s no vacío.

Sistema arbol_actual(Sistema s);
// retorna el actual.
// Pre: s no vacío.

Sistema arbol_anterior(Sistema s);
// retorna el anterior.
// Pre: s no vacío.

Cadena arbol_nombre(Sistema s);
// retorna el nombre del archivo.
// Pre: s no vacío.

bool arbol_escritura(Sistema s);
// retorna el valor del permiso de escritura.
// Pre: s no vacío.

void modificar_escritura(Sistema &s, bool valor);
// modifica el valor del permiso de escritura.
// Pre: s no vacío.

void modificar_actual(Sistema &s, Sistema actual);
// cambia el directorio actual del sistema.
// Pre: s no vacío.

void modificar_anterior(Sistema &s, Sistema anterior);
// cambia el directorio anterior del sistema.
// Pre: s no vacío.

void modificar_ph(Sistema &s, Sistema q);
// modifica el puntero primer hijo del nodo dado.
// Pre: s no vacío.

void modificar_sh(Sistema &s, Sistema q);
// modifica el puntero siguiente hermano del nodo dado.
// Pre: s no vacío.

void sumar_path(Sistema &s, Cadena subdirectorio);
// modifica el path, concatenándole un nuevo nombre de subdirectorio al final.
// Pre: s no vacío.

void restar_path(Sistema &s);
// modifica el path, removiéndole un nombre de subdirectorio al final.
// Pre: s no vacío.

Cadena arbol_contenido(Sistema s);
// retorna el valor del contenido.
// Pre: s no vacío.

TipoNodo arbol_tipo(Sistema s);
// retorna el tipo del nodo.
// Pre: s no vacío.

Cadena arbol_path(Sistema s);
// retorna el path actual.
// Pre: s no vacio.

Sistema arbol_insertar(Sistema &s, Sistema nodo);
// Inserta un nodo como último sigiente hermano en el primer nivel del arbol.

void arbol_eliminar(Sistema &s, Sistema &nodo, Sistema &nodoAnterior);
// Elimina un archivo o directorio del árbol en el directorio actual.

void destruir_arbol(Sistema &s);
// Destruye el arbol dado.

void eliminar_nodo(Sistema &s, Sistema &nodo, Sistema &nodoAnterior);
// Elimina un nodo cualquiera dado, sin condiciones, ni cambios en punteros.

int mayor(int a, int b);
// Retorna el mayor de dos enteros.

int arbol_profunidad(Sistema s);
// Retorna la profundidad del árbol.

void imprimir_nivel(Sistema s, int nivel);
// Imprime el nivel dado del arbol general.

bool arbol_pertenece(Sistema s, Cadena nombre);
// Retorna true si la cadena 'nombre' pertenece al arbol 's'.

bool arbol_pertenece_un_nivel(Sistema s, Cadena nombre);
// Retorna true si 'nombre' pertenece al nivel actual del árbol 's'.

void mostrar_estructura_recursiva(Sistema s, Cadena path);
// Se muestra en pantalla la estructura de los archivos y directorios desde cualquier lugar del sistema de manera recursiva
// Mostrando al principio los archivos del directorio y luego los subdirectorios del mismo.

#endif