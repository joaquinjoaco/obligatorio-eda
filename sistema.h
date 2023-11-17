#ifndef SISTEMA_H
#define SISTEMA_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Autores: Fabricio Garcia (5.473.797-0), Juan Garcia (5.282.647-8), Joaquin Gomez (5.398.934-6).
//
// Trabajo Obligatorio
// sistema.h
// Modulo de Definición del File System.

#include "arbolg.h"
#include "lista.h"

TipoRet CREARSISTEMA(Sistema &s);
// Inicializa el sistema para que contenga únicamente al directorio RAIZ,
// sin subdirectorios ni archivos.
// Pre: No debe exisitr un sistema previamente creado.

TipoRet DESTRUIRSISTEMA(Sistema &s);
// Destruye el sistema, liberando la memoria asignada a las estructuras de
// datos que constituyen el file system.
// Pre: El sistema debe haber sido creado previamente.

TipoRet CD(Sistema &s, Cadena nombreDirectorio);
// Cambia de directorio.

TipoRet MKDIR(Sistema &s, Cadena nombreDirectorio);
// Crea un nuevo directorio.

TipoRet RMDIR(Sistema &s, Cadena nombreDirectorio);
// Elimina un directorio.

TipoRet MOVE(Sistema &s, Cadena nombre, Cadena directorioDestino);
// Mueve un directorio o archivo desde su directorio origen hacia un nuevo directorio destino.

TipoRet DIR(Sistema &s, Cadena parametro);
// Muestra el contenido del directorio actual.
// Pre: El sistema debe haber sido creado.

TipoRet CREATEFILE(Sistema &s, Cadena nombreArchivo);
// Crea un nuevo archivo en el directorio actual.
// Pre: el nombre del archivo no debe ser vacio.

TipoRet DELETE(Sistema &s, Cadena nombreArchivo);
// Elimina un archivo del directorio actual, siempre y cuando no sea de sólo lectura.

TipoRet ATTRIB(Sistema &s, Cadena nombreArchivo, Cadena parametro);
// Agrega un texto al comienzo del archivo NombreArchivo.

TipoRet IC(Sistema &s, Cadena nombreArchivo, Cadena texto);
// Agrega un texto al principio del archivo NombreArchivo.

TipoRet IF(Sistema &s, Cadena nombreArchivo, Cadena texto);
// Agrega un texto al final del archivo NombreArchivo.

TipoRet DC(Sistema &s, Cadena nombreArchivo, int k);
// Elimina los a lo sumo K primeros caracteres del archivo parámetro.

TipoRet DF(Sistema &s, Cadena nombreArchivo, int k);
// Elimina los a lo sumo K últimos caracteres del archivo parámetro.

TipoRet TYPE(Sistema &s, Cadena nombreArchivo);
// Imprime el contenido del archivo parámetro.

TipoRet SEARCH(Sistema &s, Cadena nombreArchivo, Cadena texto);
// Busca dentro del archivo la existencia del texto y devuelve la posición en que lo encuentra.

TipoRet REPLACE(Sistema &s, Cadena nombreArchivo, Cadena texto1, Cadena texto2);
// Busca y reemplaza dentro del archivo la existencia del texto1 por el texto2.

#endif
