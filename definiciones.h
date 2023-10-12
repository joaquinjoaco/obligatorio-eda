#ifndef DEFINICIONES_H
#define DEFINICIONES_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// definiciones.h
// Definiciones generales del proyecto (constantes, etc).

#define MAX_COMANDO 50

// definición de TIPO DE RETORNO.
enum _retorno { OK,
                ERROR,
                NO_IMPLEMENTADA };
typedef enum _retorno TipoRet;

// definición de dato para identificar un nodo como ARCHIVO o DIRECTORIO.
// enum _tipo { DIR,
//              FILE };
// typedef enum _tipo Tipo;

// Definición de CADENA.
typedef char* Cadena;

#endif
