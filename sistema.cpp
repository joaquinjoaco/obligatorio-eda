// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Autores: Fabricio Garcia (5.473.797-0), Juan Garcia (5.282.647-8), Joaquin Gomez (5.398.934-6).
//
// Trabajo Obligatorio
// sistema.c
// Modulo de Implementacion del File System.

#include "sistema.h"

#include <string.h>

#include <iostream>

#include "lista.h"

using namespace std;

TipoRet CREARSISTEMA(Sistema &s) {
    // Inicializa el sistema para que contenga únicamente al directorio RAIZ,
    // sin subdirectorios ni archivos.
    // Pre: No debe exisitr un sistema previamente creado.

    s = crear_raiz();
    return OK;
}

TipoRet DESTRUIRSISTEMA(Sistema &s) {
    // Destruye el sistema, liberando la memoria asignada a las estructuras que
    // datos que constituyen el file system.
    // Pre: El sistema debe haber sido creado previamente.

    destruir_arbol(s);
    return OK;
}

TipoRet CD(Sistema &s, Cadena nombreDirectorio) {
    // Cambia directorio.
    return NO_IMPLEMENTADA;
}

TipoRet MKDIR(Sistema &s, Cadena nombreDirectorio) {
    // Crea un nuevo directorio.
    return NO_IMPLEMENTADA;
}

TipoRet RMDIR(Sistema &s, Cadena nombreDirectorio) {
    // Elimina un directorio.
    return NO_IMPLEMENTADA;
}

TipoRet MOVE(Sistema &s, Cadena nombre, Cadena directorioDestino) {
    // mueve un directorio o archivo desde su directorio origen hacia un nuevo
    // directorio destino.
    return NO_IMPLEMENTADA;
}

TipoRet DIR(Sistema &s, Cadena parametro) {
    // Muestra el contenido del directorio actual.
    // Pre: El sistema debe haber sido creado.

    // creamos una lista para insertar los archivos de manera alfabeticamente ordenada.
    Lista archivos_ordenados = crear();
    Sistema aux = s;

    // bajamos al primer nivel.
    aux = arbol_ph(aux);

    // insertamos todos los archivos del primer nivel en la lista.
    while (aux != NULL) {
        archivos_ordenados = insertar(aux, archivos_ordenados);
        aux = arbol_sh(aux);
    }

    // imprimimos la lista que creamos.
    imprimir_lista(archivos_ordenados);

    return OK;
}

TipoRet CREATEFILE(Sistema &s, Cadena nombreArchivo) {
    // Crea un nuevo archivo en el directorio actual.
    // Pre: el nombre del archivo no debe ser vacio.

    // Auxiliar para extension.
    Cadena extension;
    Cadena nombre;
    Cadena auxiliar = new (char[MAX_COMANDO]);
    strcpy(auxiliar, nombreArchivo);

    extension = strtok(auxiliar, "(.)\n");  // se queda con nombre.
    extension = strtok(NULL, "(.)\n");      // se queda con la extension.
    strcpy(nombre, auxiliar);
    cout << "cout: " << nombre << endl;

    if (extension == NULL) {
        cout << "El archivo debe tener una extensión entre 1 y 3 caracteres." << endl;
        delete auxiliar;
        return ERROR;
    } else if (strlen(extension) > MAX_EXTENSION) {
        cout << "La extensión del archivo no puede superar los 3 caracteres." << endl;
        delete auxiliar;
        return ERROR;
    } else if (strlen(nombre) >= MAX_NOMBRE) {
        cout << "El nombre del archivo no puede superar los 15 caracteres." << endl;
        delete auxiliar;
        return ERROR;
    } else {
        // Si pasó las validaciones, se le asigna nombre al archivo y se lo
        // sigue creando.
        Sistema newFile = crear_archivo(nombreArchivo);

        if (arbol_pertenece(s, nombreArchivo)) {
            cout << "El archivo '" << nombreArchivo << "' ya existe.";
            delete auxiliar;
            return ERROR;
        } else {
            // insertamos el nuevo archivo como ultimo hermano.
            arbol_insertar(s, newFile);
            cout << "El archivo '" << nombreArchivo << "' fue creado exitosamente.";
            delete auxiliar;
            return OK;
        }
    }
}

TipoRet DELETE(Sistema &s, Cadena nombreArchivo) {
    // Elimina un archivo del directorio actual, siempre y cuando no sea de sólo
    // lectura.

    if (!arbol_pertenece(s, nombreArchivo)) {
        cout << "El archivo '" << nombreArchivo << "' no existe en el directorio actual.";
        return ERROR;  // El archivo no existe en el directorio actual
    }

    // Encontrar el archivo
    Sistema archivo = arbol_ph(s);
    Sistema archivoAnterior = NULL;
    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
        archivoAnterior = archivo;
        archivo = arbol_sh(archivo);
    }

    // Verificar si el archivo es de solo lectura, en este caso no se elimina
    if (arbol_escritura(archivo) == false) {
        cout << "El archivo '" << nombreArchivo << "' no se puede eliminar.";
        return ERROR;
    }

    arbol_eliminar(s, archivo, archivoAnterior);
    cout << "El archivo '" << nombreArchivo << "' fue eliminado exitosamente.";
    return OK;
}

TipoRet ATTRIB(Sistema &s, Cadena nombreArchivo, Cadena parametro) {
    // Agrega un texto al comienzo del archivo NombreArchivo.

    if (arbol_pertenece(s, nombreArchivo)) {
        if ((strcasecmp(parametro, "+W") == 0 || strcasecmp(parametro, "-W") == 0)) {
            Sistema aux = s;
            // avanzamos al primer hijo para recorrer los hermanos.
            aux = arbol_ph(aux);

            // buscamos el nodo a editar,
            while (strcmp(arbol_nombre(aux), nombreArchivo) != 0) {
                aux = arbol_sh(aux);
            }

            if (strcasecmp(parametro, "+W") == 0) {
                modificar_escritura(aux, true);
                cout << "El permiso de escritura fue agregado exitosamente al "
                        "archivo '"
                     << nombreArchivo << "'.";
            } else {
                modificar_escritura(aux, false);
                cout << "El permiso de escritura fue removido exitosamente del "
                        "archivo '"
                     << nombreArchivo << "'.";
            }

            return OK;
        } else {
            cout << "Parametro incorrecto, usar -W o +W.";
            return ERROR;
        }
    } else {
        cout << "El archivo '" << nombreArchivo << "' No existe.";
        return ERROR;
    }
}

TipoRet IC(Sistema &s, Cadena nombreArchivo, Cadena texto) {
    // Agrega un texto al principio del archivo NombreArchivo.

    if (arbol_pertenece(s, nombreArchivo)) {
        Sistema aux = s;
        // avanzamos al primer hijo para recorrer los hermanos.
        aux = arbol_ph(aux);

        // buscamos el nodo a editar,
        while (strcmp(arbol_nombre(aux), nombreArchivo) != 0) {
            aux = arbol_sh(aux);
        }
        if (arbol_escritura(aux)) {
            // Agregar texto al principio del contenido del archivo
            char temp[TEXTO_MAX];
            strcpy(temp, arbol_contenido(aux));
            strcpy(arbol_contenido(aux), texto);
            strcat(arbol_contenido(aux), temp);

            // Se limita el contenido a 22 caracteres
            if (strlen(arbol_contenido(aux)) > TEXTO_MAX) {
                arbol_contenido(aux)[TEXTO_MAX] = '\0';
            }

            cout << "Se ha insertado '" << texto << "' al comienzo de '" << nombreArchivo << "' exitosamente.";
            return OK;
        } else {
            cout << "El archivo '" << nombreArchivo << "' es de solo lectura." << endl;
            return ERROR;
        }
    } else {
        cout << "El archivo '" << nombreArchivo << "' no existe en el directorio actual" << endl;
        return ERROR;
    }
}

TipoRet IF(Sistema &s, Cadena nombreArchivo, Cadena texto) {
    // Agrega un texto al final del archivo NombreArchivo.

    if (arbol_pertenece(s, nombreArchivo)) {
        Sistema aux = s;
        // avanzamos al primer hijo para recorrer los hermanos.
        aux = arbol_ph(aux);

        // buscamos el nodo a editar,
        while (strcmp(arbol_nombre(aux), nombreArchivo) != 0) {
            aux = arbol_sh(aux);
        }
        if (arbol_escritura(aux)) {
            // agregamos al contenido el texto ingresado en la cadena (al final en este caso)
            strcat(arbol_contenido(aux), texto);
            // Se limita el contenido a 22 caracteres
            if (strlen(arbol_contenido(aux)) > TEXTO_MAX) {
                arbol_contenido(aux)[TEXTO_MAX] = '\0';
            }

            cout << "Se ha insertado '" << texto << "' al final de '" << nombreArchivo << "' exitosamente.";
            return OK;
        } else {
            cout << "El archivo '" << nombreArchivo << "' es de solo lectura." << endl;
            return ERROR;
        }
    } else {
        cout << "El archivo '" << nombreArchivo << "' no existe en el directorio actual" << endl;
        return ERROR;
    }
}

TipoRet DC(Sistema &s, Cadena nombreArchivo, int k) {
    // Elimina los a lo sumo K primeros caracteres del archivo parámetro.

    if (arbol_pertenece(s, nombreArchivo)) {
        Sistema aux = s;
        // avanzamos al primer hijo para recorrer los hermanos.
        aux = arbol_ph(aux);

        // buscamos el nodo a editar,
        while (strcmp(arbol_nombre(aux), nombreArchivo) != 0) {
            aux = arbol_sh(aux);
        }

        if (arbol_escritura(aux) == 1) {
            // revisamos el largo total del contenido
            string S_Aux = arbol_contenido(aux);
            int auxNum = S_Aux.length();

            if (k > strlen(arbol_contenido(aux))) {
                // Si el 'k' dado se excede del largo total de la cadena de contenido tomaremos un nuevo entero con el largo total de la cadena.
                int largoTotal = strlen(arbol_contenido(aux));

                // almacenamos el nuevo contenido con k caracteres borrados de su inicio.
                S_Aux = S_Aux.substr(largoTotal, auxNum);
                strcpy(arbol_contenido(aux), S_Aux.c_str());
            } else {
                // Si el 'k' dado no se excede, podemos borrar 'k' caracteres.
                S_Aux = S_Aux.substr(k, auxNum);
                strcpy(arbol_contenido(aux), S_Aux.c_str());
            }

            cout << "Se han eliminado los primeros '" << k << "' caracteres del archivo '" << nombreArchivo << "' exitosamente.";
            return OK;
        } else {
            cout << "El archivo '" << nombreArchivo << "' es de solo lectura." << endl;
            return ERROR;
        }
    } else {
        cout << "El archivo '" << nombreArchivo << "' no existe en el directorio actual" << endl;
        return ERROR;
    }
}

TipoRet DF(Sistema &s, Cadena nombreArchivo, int k) {
    // Elimina los a lo sumo K últimos caracteres del archivo parámetro.

    if (arbol_pertenece(s, nombreArchivo)) {
        Sistema aux = s;
        // avanzamos al primer hijo para recorrer los hermanos.
        aux = arbol_ph(aux);

        // buscamos el nodo a editar,
        while (strcmp(arbol_nombre(aux), nombreArchivo) != 0) {
            aux = arbol_sh(aux);
        }

        if (arbol_escritura(aux) == 1) {
            string S_Aux = arbol_contenido(aux);
            int auxNum = S_Aux.length();

            if (k > strlen(arbol_contenido(aux))) {
                // almacenamos el nuevo contenido con k caracteres borrados de su final.
                S_Aux = S_Aux.substr(0, 0);
                strcpy(arbol_contenido(aux), S_Aux.c_str());
            } else {
                int limite = auxNum - k;
                // almacenamos el nuevo contenido con k caracteres borrados de su final.
                S_Aux = S_Aux.substr(0, limite);
                strcpy(arbol_contenido(aux), S_Aux.c_str());
            }

            cout << "Se han eliminado los ultimos '" << k << "' caracteres del archivo '" << nombreArchivo << "' exitosamente.";
            return OK;
        } else {
            cout << "El archivo '" << nombreArchivo << "' es de solo lectura." << endl;
            return ERROR;
        }

    } else {
        cout << "El archivo '" << nombreArchivo << "' no existe en el directorio actual" << endl;
        return ERROR;
    }
}

TipoRet TYPE(Sistema &s, Cadena nombreArchivo) {
    // Imprime el contenido del archivo parámetro.

    // Verificar si el archivo existe en el directorio actual.
    if (!arbol_pertenece(s, nombreArchivo)) {
        cout << "El archivo '" << nombreArchivo << "' no existe en el directorio actual" << endl;
        return ERROR;
    }

    // Encontrar el archivo
    Sistema archivo = arbol_ph(s);

    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
        archivo = arbol_sh(archivo);
    }

    string contenido = arbol_contenido(archivo);

    if (contenido.empty()) {
        cout << "El archivo " << nombreArchivo << " no tiene contenido" << endl;
        return OK;
    } else {
        cout << "Contenido de " << nombreArchivo << ":" << endl;
        cout << arbol_contenido(archivo) << endl;
        return OK;
    }
}

TipoRet SEARCH(Sistema &s, Cadena nombreArchivo, Cadena texto) {
    // Busca dentro del archivo la existencia del texto y devuelve la posición en que lo encuentra.

    // Chequea si el archivo existe
    if (!arbol_pertenece(s, nombreArchivo)) {
        cout << "El archivo '" << nombreArchivo << "' no existe en el directorio actual" << endl;
        return ERROR;
    }

    // Encontrar el archivo
    Sistema archivo = arbol_ph(s);

    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
        archivo = arbol_sh(archivo);
    }

    // Realiza la búsqueda del texto dentro del archivo
    string contenidoArchivo = arbol_contenido(archivo);

    // Encuentra la primera ocurrencia del texto en el contenido del archivo
    size_t posicion = contenidoArchivo.find(texto);

    if (posicion != string::npos) {
        cout << "Texto encontrado en la posición: " << posicion << endl;
        return OK;
    } else {
        cout << "Texto no encontrado en el archivo." << endl;
        return ERROR;
    }
}

TipoRet REPLACE(Sistema &s, Cadena nombreArchivo, Cadena texto1, Cadena texto2) {
    // Busca y reemplaza dentro del archivo la existencia del texto1 por el texto2.
    return NO_IMPLEMENTADA;
}
