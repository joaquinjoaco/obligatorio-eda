// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// sistema.c
// Modulo de Implementacion del File System.

#include "sistema.h"

#include <string.h>

#include <iostream>

// #include "auxiliares.h"

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

// --------------------------------------------------------------------------------------------------
// ------------------------------ Funciones auxiliares ----------------------------------------------
// --------------------------------------------------------------------------------------------------

int mayor(int a, int b) {
    // retorna el mayor de dos enteros.
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int arbol_profunidad(Sistema &s) {
    // retorna la profundidad del arbol (para el caso de arboles generales calculamos la
    // profunidad como la cantidad de niveles). El primer nodo es el nivel 1.

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
        // } else if (s->nombre == nombre) {
        // no es case sensitive, permite la
        // creacion de 'Hola.mp3' y 'hola.mp3'.
    } else if (strcmp(s->nombre, nombre) == 0) {
        return true;
    } else {
        return arbol_pertenece(s->ph, nombre) || arbol_pertenece(s->sh, nombre);
    }
}

// --------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------

TipoRet CREARSISTEMA(Sistema &s) {
    // Inicializa el sistema para que contenga únicamente al directorio RAIZ,
    // sin subdirectorios ni archivos. Para mas detalles ver letra.

    Sistema raiz = new (_sistema);
    raiz->tipo = _tipo(0);
    strcpy(raiz->nombre, "RAIZ");
    raiz->ph = NULL;
    raiz->sh = NULL;
    strcpy(raiz->contenido, "");
    raiz->lectura = true;
    raiz->escritura = true;

    s = raiz;
    return OK;
}

TipoRet DESTRUIRSISTEMA(Sistema &s) {
    // Destruye el sistema, liberando la memoria asignada a las estructuras que
    // datos que constituyen el file system. Para mas detalles ver letra.
    if (s != NULL) {
        DESTRUIRSISTEMA(s->ph);
        DESTRUIRSISTEMA(s->sh);
        delete s;
        return OK;
    } else {
        return ERROR;
    }
}

TipoRet CD(Sistema &s, Cadena nombreDirectorio) {
    // Cambia directorio.
    // Para mas detalles ver letra.
    return NO_IMPLEMENTADA;
}

TipoRet MKDIR(Sistema &s, Cadena nombreDirectorio) {
    // Crea un nuevo directorio.
    // Para mas detalles ver letra.
    return NO_IMPLEMENTADA;
}

TipoRet RMDIR(Sistema &s, Cadena nombreDirectorio) {
    // Elimina un directorio.
    // Para mas detalles ver letra.
    return NO_IMPLEMENTADA;
}

TipoRet MOVE(Sistema &s, Cadena nombre, Cadena directorioDestino) {
    // mueve un directorio o archivo desde su directorio origen hacia un nuevo
    // directorio destino. Para mas detalles ver letra.
    return NO_IMPLEMENTADA;
}

TipoRet DIR(Sistema &s, Cadena parametro) {
    // Muestra el contenido del directorio actual.
    // Para mas detalles ver letra.
    for (int i = 0; i < arbol_profunidad(s); i++) {
        imprimir_nivel(s, i);
        cout << "\n";
    }

    return OK;
}

TipoRet CREATEFILE(Sistema &s, Cadena nombreArchivo) {
    // Crea un nuevo archivo en el directorio actual.
    // Para mas detalles ver letra.

    // lo inserta como ultimo hermano (o ultimo elemento de la lista)
    // con permisos de lectura y escritura.
    Sistema newFile = new (_sistema);
    strcpy(newFile->nombre, nombreArchivo);
    newFile->tipo = _tipo(1);
    strcpy(newFile->contenido, "");
    newFile->ph = NULL;
    newFile->sh = NULL;
    newFile->escritura = true;
    newFile->lectura = true;

    if (arbol_pertenece(s, nombreArchivo)) {
        cout << "El archivo '" << nombreArchivo << "' ya existe.";
        return ERROR;
    }

    if (s->ph != NULL) {
        // Tiene un primer hijo
        Sistema aux = s;
        aux = aux->ph;  // vamos al primer hijo.

        // vamos al ultimo hermano (o ultimo elemento de la lista).
        while (aux->sh != NULL) {
            aux = aux->sh;
        }

        // apuntamos el ultimo hermano al nuevo archivo
        aux->sh = newFile;

    } else {
        // No tiene primer hijo
        s->ph = newFile;
    }

    cout << "El archivo '" << nombreArchivo << "' fue creado exitosamente.";
    return OK;
}

TipoRet DELETE(Sistema &s, Cadena nombreArchivo) {
    // Elimina un archivo del directorio actual, siempre y cuando no sea de sólo
    // lectura. Para mas detalles ver letra.
    if (!arbol_pertenece(s, nombreArchivo)) {
        cout << "El archivo '" << nombreArchivo << "' no existe en el directorio actual.";
        return ERROR;  // El archivo no existe en el directorio actual
    }

    // Encontrar el archivo
    Sistema archivo = s->ph;
    Sistema archivoAnterior = NULL;
    while (archivo != NULL && strcmp(archivo->nombre, nombreArchivo) != 0) {
        archivoAnterior = archivo;
        archivo = archivo->sh;
    }

    // Verificar si el archivo es de solo lectura, en este caso no se elimina
    if (archivo->escritura == false) {
        cout << "El archivo '" << nombreArchivo << "' no se puede eliminar.";
        return ERROR;
    }

    // Eliminar el archivo del directorio actual
    if (archivoAnterior == NULL) {
        s->ph = archivo->sh;  // El archivo es el primer hijo del directorio
    } else {
        archivoAnterior->sh = archivo->sh;  // El archivo no es el primer hijo
    }

    delete archivo;  // Liberar memoria del archivo
    cout << "El archivo '" << nombreArchivo << "' fue eliminado exitosamente.";
    return OK;
}

TipoRet ATTRIB(Sistema &s, Cadena nombreArchivo, Cadena parametro) {
    if (arbol_pertenece(s, nombreArchivo)) {
        if ((strcasecmp(parametro, "+W") == 0 ||
             strcasecmp(parametro, "-W") == 0)) {
            Sistema aux = s;
            // avanzamos al primer hijo para recorrer los hermanos.
            aux = aux->ph;

            // buscamos el nodo a editar,
            while (strcmp(aux->nombre, nombreArchivo) != 0) {
                aux = aux->sh;
            }

            if (strcasecmp(parametro, "+W") == 0) {
                aux->escritura = true;
                cout << "El permiso de escritura fue agregado exitosamente al archivo '" << nombreArchivo << "'.";
            } else {
                aux->escritura = false;
                cout << "El permiso de escritura fue removido exitosamente del archivo '" << nombreArchivo << "'.";
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
    // Para mas detalles ver letra.

    if (arbol_pertenece(s, nombreArchivo)) {
        Sistema aux = s;
        // avanzamos al primer hijo para recorrer los hermanos.
        aux = aux->ph;

        // buscamos el nodo a editar,
        while (strcmp(aux->nombre, nombreArchivo) != 0) {
            aux = aux->sh;
        }
        if (aux->escritura) {
            // Agregar texto al principio del contenido del archivo
            char temp[TEXTO_MAX];
            strcpy(temp, aux->contenido);
            strcpy(aux->contenido, texto);
            strcat(aux->contenido, temp);

            // Se limita el contenido a 22 caracteres
            if (strlen(aux->contenido) > TEXTO_MAX) {
                aux->contenido[TEXTO_MAX] = '\0';
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
    // Para mas detalles ver letra.

    if (arbol_pertenece(s, nombreArchivo)) {
        Sistema aux = s;
        // avanzamos al primer hijo para recorrer los hermanos.
        aux = aux->ph;

        // buscamos el nodo a editar,
        while (strcmp(aux->nombre, nombreArchivo) != 0) {
            aux = aux->sh;
        }
        if (aux->escritura) {
            // agregamos al contenido el texto ingresado en la cadena (al final
            // en este caso)
            strcat(aux->contenido, texto);
            // Se limita el contenido a 22 caracteres
            if (strlen(aux->contenido) > TEXTO_MAX) {
                aux->contenido[TEXTO_MAX] = '\0';
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
    // Para mas detalles ver letra.
    if (arbol_pertenece(s, nombreArchivo)) {
        Sistema aux = s;
        // avanzamos al primer hijo para recorrer los hermanos.
        aux = aux->ph;

        // buscamos el nodo a editar,
        while (strcmp(aux->nombre, nombreArchivo) != 0) {
            aux = aux->sh;
        }

        if (aux->escritura == 1) {
            // revisamos el largo total del contenido
            string S_Aux = aux->contenido;
            int auxNum = S_Aux.length();

            if (k > strlen(aux->contenido)) {
                // Si el 'k' dado se excede del largo total
                // de la cadena de contenido tomaremos un nuevo
                // entero con el largo total de la cadena.
                int largoTotal = strlen(aux->contenido);

                // almacenamos el nuevo contenido
                // con k caracteres borrados de su inicio.
                S_Aux = S_Aux.substr(largoTotal, auxNum);
                strcpy(aux->contenido, S_Aux.c_str());
            } else {
                // Si el 'k' dado no se excede, podemos borrar 'k' caracteres tranquilamente.
                S_Aux = S_Aux.substr(k, auxNum);
                strcpy(aux->contenido, S_Aux.c_str());
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
    // Para mas detalles ver letra.
    if (arbol_pertenece(s, nombreArchivo)) {
        Sistema aux = s;
        // avanzamos al primer hijo para recorrer los hermanos.
        aux = aux->ph;

        //     // buscamos el nodo a editar,
        while (strcmp(aux->nombre, nombreArchivo) != 0) {
            aux = aux->sh;
        }

        if (aux->escritura == 1) {
            string S_Aux = aux->contenido;
            int auxNum = S_Aux.length();

            if (k > strlen(aux->contenido)) {
                // almacenamos el nuevo contenido con k caracteres borrados de su final.
                S_Aux = S_Aux.substr(0, 0);
                strcpy(aux->contenido, S_Aux.c_str());

            } else {
                int limite = auxNum - k;
                // almacenamos el nuevo contenido con k caracteres borrados de su final.
                S_Aux = S_Aux.substr(0, limite);
                strcpy(aux->contenido, S_Aux.c_str());
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
    // Para mas detalles ver letra.

    // Verificar si el archivo existe en el directorio actual.
    if (!arbol_pertenece(s, nombreArchivo)) {
        cout << "El archivo '" << nombreArchivo << "' no existe en el directorio actual" << endl;
        return ERROR;
    }

    // Encontrar el archivo
    Sistema archivo = s->ph;

    while (archivo != NULL && strcmp(archivo->nombre, nombreArchivo) != 0) {
        archivo = archivo->sh;
    }

    cout << "Contenido de " << nombreArchivo << ":" << endl;
    cout << archivo->contenido << endl;

    return OK;
}

TipoRet SEARCH(Sistema &s, Cadena nombreArchivo, Cadena texto) {
    // Busca dentro del archivo la existencia del texto.
    // Para mas detalles ver letra.

    // Chequea si el archivo existe
    if (!arbol_pertenece(s, nombreArchivo)) {
        cout << "El archivo '" << nombreArchivo << "' no existe en el directorio actual" << endl;
        return ERROR;
    }

    // Encontrar el archivo
    Sistema archivo = s->ph;

    while (archivo != NULL && strcmp(archivo->nombre, nombreArchivo) != 0) {
        archivo = archivo->sh;
    }

    // Realiza la búsqueda del texto dentro del archivo
    string contenidoArchivo = archivo->contenido;

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

TipoRet REPLACE(Sistema &s, Cadena nombreArchivo, Cadena texto1,
                Cadena texto2) {
    // Busca y reemplaza dentro del archivo la existencia del texto1 por el
    // texto2. Para mas detalles ver letra.
    return NO_IMPLEMENTADA;
}
