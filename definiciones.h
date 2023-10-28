#ifndef DEFINICIONES_H
#define DEFINICIONES_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Autores: Fabricio Garcia (5.473.797-0), Juan Garcia (5.282.647-8), Joaquin Gomez (5.398.934-6).
//
// Trabajo Obligatorio
// definiciones.h
// Definiciones generales del proyecto (constantes, etc).

#define NOMBRE_RAIZ "RAIZ"
#define MAX_COMANDO 50
#define TEXTO_MAX 23
#define MAX_NOMBRE 16
#define MAX_EXTENSION 3

// definición de TIPO DE RETORNO.
enum _retorno { OK,
                ERROR,
                NO_IMPLEMENTADA };
typedef enum _retorno TipoRet;

// definición de dato para identificar un nodo como ARCHIVO o DIRECTORIO.
enum _tipo { DIRECTORIO,
             ARCHIVO };
typedef enum _tipo TipoNodo;

// Definición de CADENA.
typedef char *Cadena;

#endif
