#ifndef ARBOLG_H
#define ARBOLG_H

// // Estructuras de Datos y Algoritmos - Curso 2023
// // Tecnologo en Informatica FIng - DGETP - UTEC
// //
// // Trabajo Obligatorio
// // arbolg.h
// // Definiciones de arbol general.

#include "definiciones.h"

typedef struct _sistema *Sistema;

Sistema crear_raiz();
// crea el directorio raíz.

Sistema crear_archivo(Cadena nombreArchivo);
// crea un archivo.

void destruir_arbol(Sistema &s);
// destruye el arbol dado.

bool vacio(Sistema s);
// retorna true si el arbol es vacío, false en caso contrario.

Sistema arbol_ph(Sistema s);
// retorna el primer hijo.

Sistema arbol_sh(Sistema s);
// retorna el siguiente hermano.

Cadena arbol_nombre(Sistema s);
// retorna el nombre del archivo.

bool arbol_escritura(Sistema s);
// retorna el valor del permiso de escritura.

void modificar_escritura(Sistema &s, bool valor);
// modifica el valor del permiso de escritura.

Cadena arbol_contenido(Sistema s);
// retorna el valor del contenido.

TipoNodo arbol_tipo(Sistema s);
// retorna el tipo del nodo.

Sistema arbol_insertar(Sistema &s, Sistema newFile);
// inserta un nodo como ultimo sigiente hermano en el primer nivel del arbol.

Sistema arbol_eliminar(Sistema &s, Sistema &archivo, Sistema &archivoAnterior);
// Elimina un archivo de un arbol.

int mayor(int a, int b);
// retorna el mayor de dos enteros.

int arbol_profunidad(Sistema &s);
// retorna la profundidad del arbol (para el caso de arboles generales
// calculamos la profunidad como la cantidad de niveles). El primer nodo es el
// nivel 1.

void imprimir_nivel(Sistema &s, int nivel);
// imprime el nivel dado del arbol general.

bool arbol_pertenece(Sistema &s, Cadena nombre);
// retorna true si 'e' pertenece al arbol 'a'.

#endif