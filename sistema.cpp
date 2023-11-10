// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Autores: Fabricio Garcia (5.473.797-0), Juan Garcia (5.282.647-8), Joaquin
// Gomez (5.398.934-6).
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

  // -------------- VALIDACIONES --------------
  // CASO "CD .." y nos encontramos en raiz.
  if (strcmp(arbol_nombre(arbol_actual(s)), NOMBRE_RAIZ) == 0 &&
      strcmp(nombreDirectorio, "..") == 0) {
    cout << "Se encuentra en el directorio raíz." << endl;
    return ERROR;
  }
  // ------------------------------------------


  // CASO "CD ..".
  if (strcmp(nombreDirectorio, "..") == 0) {
    modificar_actual(s, arbol_anterior(s));
    modificar_anterior(s, arbol_anterior(arbol_anterior(s)));  // Establecer el directorio anterior al anterior del anterior.
    restar_path(s);
    return OK;
  }

  // CASO "CD RAIZ".
  if (strcmp(nombreDirectorio, NOMBRE_RAIZ) == 0) {
    modificar_actual(s, s);
    strcpy(arbol_path(s), NOMBRE_RAIZ);
    return OK;
  }

  // -------------------------------------------------

  // Guardamos su padre (el directorio anterior).
  // por si el anterior era la raiz.
  Sistema directorio =
      arbol_ph(arbol_actual(s));  // baja un nivel desde el actual.
  while (directorio != NULL &&
         (strcmp(arbol_nombre(directorio), nombreDirectorio) != 0 ||
          arbol_tipo(directorio) == 1)) {
    directorio = arbol_sh(directorio);  // nuestro nuevo actual
  }

  // Puede que el directorio exista pero que no se encuentre en el nivel de
  // los hijos.
  if (directorio == NULL) {
    cout << "No se encontró el directorio' " << nombreDirectorio << "'."
         << endl;
    return ERROR;
  }

  // Encontró el directorio en el nivel, vamos a él y guardamos el "actual"
  // como el nuevo anterior.
  modificar_anterior(s, arbol_actual(s));
  sumar_path(s, arbol_nombre(directorio));
  modificar_actual(s, directorio);

  return OK;
}

TipoRet MKDIR(Sistema &s, Cadena nombreDirectorio) {
  // Crea un nuevo directorio.

  Cadena auxiliar = new char[MAX_NOMBRE];
  strcpy(auxiliar, nombreDirectorio);

  // Utilizar strtok para separar el nombre y la extensión
  Cadena nombre = strtok(auxiliar, ".");
  Cadena extension = strtok(NULL, ".");

  // Verificar si se encontró una extensión
  if (extension != NULL) {
    cout << "El nombre del directorio no puede contener una extensión." << endl;
    delete auxiliar;
    return ERROR;
  }

  if (strlen(nombreDirectorio) >= MAX_NOMBRE) {
    cout << "El nombre del directorio no puede superar los 15 caracteres."
         << endl;
    delete auxiliar;
    return ERROR;
  } else {
    // Si pasó las validaciones, se le asigna nombre al directorio y se lo
    // sigue creando.
    Sistema newDir = crear_directorio(nombreDirectorio, arbol_actual(s));
    Sistema actual = arbol_actual(s);

    // Cambiar ARBOL_PERTENECE por una función que busque en un solo nivel,
    // ya que se permiten nombres iguales en distintos niveles.
    if (arbol_pertenece_un_nivel(actual, nombreDirectorio)) {
      cout << "El directorio'" << nombreDirectorio << "' ya existe." << endl;
      delete auxiliar;
      return ERROR;
    } else {
      // Insertamos el nuevo directorio como último hermano.
      arbol_insertar(actual, newDir);
      cout << "El directorio '" << nombreDirectorio
           << "' fue creado exitosamente." << endl;
      delete auxiliar;
      return OK;
    }
  }
}

TipoRet RMDIR(Sistema &s, Cadena nombreDirectorio) {
  // Elimina un directorio.

  // TODO: QUE SEA RECURSIVO (O SEA QUE BORRE TODO PARA ADENTRO DEL
  // DIRECTORIO).

  if (!arbol_pertenece_un_nivel(arbol_actual(s), nombreDirectorio)) {
    cout << "El directorio '" << nombreDirectorio
         << "' no existe en el directorio actual." << endl;
    return ERROR;  // El directorio no existe en el directorio actual.
  }

  // Encontrar el directorio
  Sistema directorio = arbol_ph(arbol_actual(s));  // baja un nivel.
  Sistema directorioAnterior = NULL;
  while (directorio != NULL &&
             strcmp(arbol_nombre(directorio), nombreDirectorio) != 0 ||
         arbol_tipo(directorio) == 1) {
    directorioAnterior = directorio;
    directorio = arbol_sh(directorio);  // nuestro nodo a eliminar
  }

  // Puede que el directorio exista pero que no se encuentre en el nivel de
  // los hijos.
  if (directorio == NULL) {
    cout << "No se encontró el directorio' " << nombreDirectorio << "'."
         << endl;
    return ERROR;
  }

  // if (arbol_tipo(directorio) == 1) {
  //     cout << "El '" << nombreDirectorio
  //          << "' es un archivo, pruebe usar 'DELETE'." << endl;
  //     return ERROR;
  // }

  // // modificamos los punteros para que el actual apunte al siguiente
  // hermano Sistema actual = arbol_actual(s); modificar_ph(actual, NULL);

  Sistema actual = arbol_actual(s);
  arbol_eliminar(actual, directorio, directorioAnterior);

  // destruir_arbol(directorio);
  cout << "El directorio '" << nombreDirectorio
       << "' fue eliminado exitosamente." << endl;

  // Sistema troll = arbol_actual(s);
  // cout << arbol_nombre(troll) << endl;

  return OK;
}

TipoRet MOVE(Sistema &s, Cadena nombre, Cadena directorioDestino) {
  // mueve un directorio o archivo desde su directorio origen hacia un nuevo
  // directorio destino.
  return NO_IMPLEMENTADA;
}

TipoRet DIR(Sistema &s, Cadena parametro) {
  // Muestra el contenido del directorio actual.
  // Pre: El sistema debe haber sido creado.
  // creamos una lista para insertar los archivos de manera alfabeticamente
  // ordenada.
  Lista archivos_ordenados = crear();
  Lista directorios_ordenados = crear();

  // imprimimos la lista que creamos.
  if (s == arbol_actual(s)) {
    // Caso en el que el directorio actual sea la RAIZ y no se uso el parametro
    // '/s'.
    Sistema auxArchivos = s;
    auxArchivos = arbol_ph(auxArchivos);
    Sistema auxDirectorios = s;
    auxDirectorios = arbol_ph(auxDirectorios);

    // insertamos todos los archivos del primer nivel en la lista.
    while (auxArchivos != NULL) {
      if (arbol_tipo(auxArchivos) == 1) {
        // si el nodo es un archivo, lo insertamos en la lista de archivos.
        archivos_ordenados = insertar(auxArchivos, archivos_ordenados);
      }
      auxArchivos = arbol_sh(auxArchivos);
    }

    // insertamos todos los directorios del primer nivel en la lista.
    while (auxDirectorios != NULL) {
      if (arbol_tipo(auxDirectorios) == 0) {
        // si el nodo es un directorio, lo insertamos en la lista de
        // directorios.
        directorios_ordenados = insertar(auxDirectorios, directorios_ordenados);
      }
      auxDirectorios = arbol_sh(auxDirectorios);
    }

    // Imprimimos el nombre del directorio.
    cout << NOMBRE_RAIZ << endl;
    cout << endl;
    // Luego se imprimen los archivos ordenados alfabeticamente, seguido de los
    // directorios ordenados de igual manera.
    imprimir_lista(archivos_ordenados);
    imprimir_lista(directorios_ordenados);
  } else {
    // Caso donde nos encontramos en un subdirectorio.
    // Encontrar el directorio actual.
    Sistema auxArchivos = arbol_actual(s);
    auxArchivos = arbol_ph(auxArchivos);  // bajamos un nivel desde el "actual".
    Sistema auxDirectorios = arbol_actual(s);
    auxDirectorios = arbol_ph(auxDirectorios);

    // insertamos todos los archivos del primer nivel del directorio
    // "actual" en la lista.
    while (auxArchivos != NULL) {
      if (arbol_tipo(auxArchivos) == 1) {
        // si el nodo es un archivo, lo insertamos en la lista de archivos.
        archivos_ordenados = insertar(auxArchivos, archivos_ordenados);
      }
      auxArchivos = arbol_sh(auxArchivos);
    }

    // insertamos todos los directorios del primer nivel en la lista.
    while (auxDirectorios != NULL) {
      if (arbol_tipo(auxDirectorios) == 0) {
        // si el nodo es un directorio, lo insertamos en la lista de
        // directorios.
        directorios_ordenados = insertar(auxDirectorios, directorios_ordenados);
      }
      auxDirectorios = arbol_sh(auxDirectorios);
    }

    // Imprimimos el path del subdirectorio.
    cout << arbol_path(s) << endl;
    cout << endl;

    // Luego se imprimen los archivos ordenados alfabeticamente, seguido de los
    // directorios ordenados de igual manera.
    imprimir_lista(archivos_ordenados);
    imprimir_lista(directorios_ordenados);
  }

  return OK;

  // // cosa del /s
  if (parametro != NULL && strcasecmp(parametro, "/s") != 0) {
      cout << "Parametro: " << parametro << endl;
      for (int i = 0; i < arbol_profunidad(arbol_actual(s)); i++) {
          imprimir_nivel(s, i);
          cout << "\n";
      }
  }
}

TipoRet CREATEFILE(Sistema &s, Cadena nombreArchivo) {
  // Crea un nuevo archivo en el directorio actual.
  // Pre: el nombre del archivo no debe ser vacio.

  // Auxiliar para extension.
  Cadena extension;
  Cadena nombre = new (char[MAX_NOMBRE]);
  Cadena auxiliar = new (char[MAX_COMANDO]);
  strcpy(auxiliar, nombreArchivo);

  extension = strtok(auxiliar, "(.)\n");  // se queda con nombre.
  extension = strtok(NULL, "(.)\n");      // se queda con la extension.
  strcpy(nombre, auxiliar);

  if (extension == NULL) {
    cout << "El archivo debe tener una extensión entre 1 y 3 caracteres."
         << endl;
    delete auxiliar;
    return ERROR;
  } else if (strlen(extension) > MAX_EXTENSION) {
    cout << "La extensión del archivo no puede superar los 3 caracteres."
         << endl;
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

    if (arbol_pertenece_un_nivel(arbol_actual(s), nombreArchivo)) {
      cout << "El archivo '" << nombreArchivo << "' ya existe." << endl;
      delete auxiliar;
      return ERROR;
    } else {
      // insertamos el nuevo archivo como ultimo hermano.
      Sistema actual = arbol_actual(s);
      arbol_insertar(actual, newFile);
      cout << "El archivo '" << nombreArchivo << "' fue creado exitosamente."
           << endl;
      delete auxiliar;
      return OK;
    }
  }
}

TipoRet DELETE(Sistema &s, Cadena nombreArchivo) {
  // Elimina un archivo del directorio actual, siempre y cuando no sea de sólo
  // lectura.

  if (!arbol_pertenece_un_nivel(arbol_actual(s), nombreArchivo)) {
    cout << "El archivo '" << nombreArchivo
         << "' no existe en el directorio actual." << endl;
    return ERROR;  // El archivo no existe en el directorio actual
  }

  // Encontrar el archivo
  Sistema archivo =
      arbol_ph(arbol_actual(s));  // bajamos un nivel desde el actual
  Sistema archivoAnterior = NULL;
  while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
    archivoAnterior = archivo;
    archivo = arbol_sh(archivo);
  }

  // Verificar si el archivo es de solo lectura, en este caso no se elimina. O
  // si se está intentando borrar un directorio.
  if (arbol_tipo(archivo) == 0) {
    cout << "El '" << nombreArchivo
         << "' es un directorio, pruebe usar 'RMDIR'." << endl;
    return ERROR;
  } else if (arbol_escritura(archivo) == false) {
    cout << "El archivo '" << nombreArchivo
         << "' no se puede eliminar, no se tiene permiso de escritura "
            "sobre el archivo."
         << endl;
    return ERROR;
  }

  Sistema actual = arbol_actual(s);
  arbol_eliminar(actual, archivo, archivoAnterior);
  cout << "El archivo '" << nombreArchivo << "' fue eliminado exitosamente."
       << endl;
  return OK;
}

TipoRet ATTRIB(Sistema &s, Cadena nombreArchivo, Cadena parametro) {
  // 
  
  if (arbol_pertenece_un_nivel(arbol_actual(s), nombreArchivo)) {
    if ((strcasecmp(parametro, "+W") == 0 ||
         strcasecmp(parametro, "-W") == 0)) {

      // buscamos el nodo a editar,
    Sistema archivo =
        arbol_ph(arbol_actual(s));  // bajamos un nivel desde el actual
    Sistema archivoAnterior = NULL;
    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
      archivoAnterior = archivo;  
      archivo = arbol_sh(archivo);
    }

      if (strcasecmp(parametro, "+W") == 0) {
        modificar_escritura(archivo, true);
        cout << "El permiso de escritura fue agregado exitosamente al "
                "archivo '"
             << nombreArchivo << "'." << endl;
      } else {
        modificar_escritura(archivo, false);
        cout << "El permiso de escritura fue removido exitosamente del "
                "archivo '"
             << nombreArchivo << "'." << endl;
      }
      return OK;

    } else {
      cout << "Parametro incorrecto, usar -W o +W." << endl;
      return ERROR;
    }
  } else {
    cout << "El archivo '" << nombreArchivo << "' No existe." << endl;
    return ERROR;
  }
}

TipoRet IC(Sistema &s, Cadena nombreArchivo, Cadena texto) {
  // Agrega un texto al principio del archivo NombreArchivo.

  if (arbol_pertenece_un_nivel(arbol_actual(s), nombreArchivo)) {

    // buscamos el nodo a editar,
     Sistema archivo =
        arbol_ph(arbol_actual(s));  // bajamos un nivel desde el actual
    Sistema archivoAnterior = NULL;
    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
      archivoAnterior = archivo;  
      archivo = arbol_sh(archivo);
    }
    if (arbol_tipo(archivo) == 0) {
      cout << "No se puede aplicar este comando sobre un directorio"
           << "." << endl;
      return ERROR;
    }
    if (arbol_escritura(archivo)) {
      // Agregar texto al principio del contenido del archivo
      char temp[TEXTO_MAX];
      strcpy(temp, arbol_contenido(archivo));
      strcpy(arbol_contenido(archivo), texto);
      strcat(arbol_contenido(archivo), temp);

      // Se limita el contenido a 22 caracteres
      if (strlen(arbol_contenido(archivo)) > TEXTO_MAX) {
        arbol_contenido(archivo)[TEXTO_MAX] = '\0';
      }

      cout << "Se ha insertado '" << texto << "' al comienzo de '"
           << nombreArchivo << "' exitosamente." << endl;
      return OK;
    } else {
      cout << "El archivo '" << nombreArchivo << "' es de solo lectura."
           << endl;
      return ERROR;
    }
  } else {
    cout << "El archivo '" << nombreArchivo
         << "' no existe en el directorio actual" << endl;
    return ERROR;
  }
}

TipoRet IF(Sistema &s, Cadena nombreArchivo, Cadena texto) {
  // Agrega un texto al final del archivo NombreArchivo.

   if (arbol_pertenece_un_nivel(arbol_actual(s), nombreArchivo)) {

    // buscamos el nodo a editar,
     Sistema archivo =
        arbol_ph(arbol_actual(s));  // bajamos un nivel desde el actual
    Sistema archivoAnterior = NULL;
    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
      archivoAnterior = archivo;  
      archivo = arbol_sh(archivo);
    }
    if (arbol_tipo(archivo) == 0) {
      cout << "No se puede aplicar este comando sobre un directorio"
           << "." << endl;
      return ERROR;
    }
    if (arbol_escritura(archivo)) {
      // agregamos al contenido el texto ingresado en la cadena (al final
      // en este caso)
      strcat(arbol_contenido(archivo), texto);
      // Se limita el contenido a 22 caracteres
      if (strlen(arbol_contenido(archivo)) > TEXTO_MAX) {
        arbol_contenido(archivo)[TEXTO_MAX] = '\0';
      }

      cout << "Se ha insertado '" << texto << "' al final de '" << nombreArchivo
           << "' exitosamente." << endl;
      return OK;
    } else {
      cout << "El archivo '" << nombreArchivo << "' es de solo lectura."
           << endl;
      return ERROR;
    }
  } else {
    cout << "El archivo '" << nombreArchivo
         << "' no existe en el directorio actual" << endl;
    return ERROR;
  }
}

TipoRet DC(Sistema &s, Cadena nombreArchivo, int k) {
  // Elimina los a lo sumo K primeros caracteres del archivo parámetro.

  if (arbol_pertenece_un_nivel(arbol_actual(s), nombreArchivo)) {

    // buscamos el nodo a editar,
     Sistema archivo =
        arbol_ph(arbol_actual(s));  // bajamos un nivel desde el actual
    Sistema archivoAnterior = NULL;
    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
      archivoAnterior = archivo;  
      archivo = arbol_sh(archivo);
    }
    if (arbol_tipo(archivo) == 0) {
      cout << "No se puede aplicar este comando sobre un directorio"
           << "." << endl;
      return ERROR;
    }
    if (arbol_escritura(archivo) == 1) {
      // revisamos el largo total del contenido
      string S_Aux = arbol_contenido(archivo);
      int auxNum = S_Aux.length();

      if (k > strlen(arbol_contenido(archivo))) {
        // Si el 'k' dado se excede del largo total de la cadena de
        // contenido tomaremos un nuevo entero con el largo total de la
        // cadena.
        int largoTotal = strlen(arbol_contenido(archivo));

        // almacenamos el nuevo contenido con k caracteres borrados de
        // su inicio.
        S_Aux = S_Aux.substr(largoTotal, auxNum);
        strcpy(arbol_contenido(archivo), S_Aux.c_str());
      } else {
        // Si el 'k' dado no se excede, podemos borrar 'k' caracteres.
        S_Aux = S_Aux.substr(k, auxNum);
        strcpy(arbol_contenido(archivo), S_Aux.c_str());
      }

      cout << "Se han eliminado los primeros '" << k
           << "' caracteres del archivo '" << nombreArchivo << "' exitosamente."
           << endl;
      return OK;
    } else {
      cout << "El archivo '" << nombreArchivo << "' es de solo lectura."
           << endl;
      return ERROR;
    }
  } else {
    cout << "El archivo '" << nombreArchivo
         << "' no existe en el directorio actual" << endl;
    return ERROR;
  }
}

TipoRet DF(Sistema &s, Cadena nombreArchivo, int k) {
  // Elimina los a lo sumo K últimos caracteres del archivo parámetro.

  if (arbol_pertenece_un_nivel(arbol_actual(s), nombreArchivo)) {

    // buscamos el nodo a editar,
     Sistema archivo =
        arbol_ph(arbol_actual(s));  // bajamos un nivel desde el actual
    Sistema archivoAnterior = NULL;
    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
      archivoAnterior = archivo;  
      archivo = arbol_sh(archivo);
    }
    if (arbol_tipo(archivo) == 0) {
      cout << "No se puede aplicar este comando sobre un directorio"
           << "." << endl;
      return ERROR;
    }
    if (arbol_escritura(archivo) == 1) {
      string S_Aux = arbol_contenido(archivo);
      int auxNum = S_Aux.length();

      if (k > strlen(arbol_contenido(archivo))) {
        // almacenamos el nuevo contenido con k caracteres borrados de
        // su final.
        S_Aux = S_Aux.substr(0, 0);
        strcpy(arbol_contenido(archivo), S_Aux.c_str());
      } else {
        int limite = auxNum - k;
        // almacenamos el nuevo contenido con k caracteres borrados de
        // su final.
        S_Aux = S_Aux.substr(0, limite);
        strcpy(arbol_contenido(archivo), S_Aux.c_str());
      }

      cout << "Se han eliminado los ultimos '" << k
           << "' caracteres del archivo '" << nombreArchivo << "' exitosamente."
           << endl;
      return OK;
    } else {
      cout << "El archivo '" << nombreArchivo << "' es de solo lectura."
           << endl;
      return ERROR;
    }

  } else {
    cout << "El archivo '" << nombreArchivo
         << "' no existe en el directorio actual" << endl;
    return ERROR;
  }
}

TipoRet TYPE(Sistema &s, Cadena nombreArchivo) {
  // Imprime el contenido del archivo parámetro.

  // Verificar si el archivo existe en el directorio actual.

 if (!arbol_pertenece_un_nivel(arbol_actual(s), nombreArchivo)) {
    cout << "El archivo '" << nombreArchivo
         << "' no existe en el directorio actual" << endl;
    return ERROR;
  }
    // buscamos el nodo a editar,
     Sistema archivo =
        arbol_ph(arbol_actual(s));  // bajamos un nivel desde el actual
    Sistema archivoAnterior = NULL;
    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
      archivoAnterior = archivo;  
      archivo = arbol_sh(archivo);
    }
    if (arbol_tipo(archivo) == 0) {
      cout << "No se puede aplicar este comando sobre un directorio"
           << "." << endl;
      return ERROR;
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
  // Busca dentro del archivo la existencia del texto y devuelve la posición
  // en que lo encuentra.

  // Chequea si el archivo existe
  if (!arbol_pertenece_un_nivel(arbol_actual(s), nombreArchivo)) {
    cout << "El archivo '" << nombreArchivo
         << "' no existe en el directorio actual" << endl;
    return ERROR;
  }

  // Encontrar el archivo
      Sistema archivo =
        arbol_ph(arbol_actual(s));  // bajamos un nivel desde el actual
    Sistema archivoAnterior = NULL;
    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
      archivoAnterior = archivo;  
      archivo = arbol_sh(archivo);
    }
    if (arbol_tipo(archivo) == 0) {
      cout << "No se puede aplicar este comando sobre un directorio"
           << "." << endl;
      return ERROR;
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

TipoRet REPLACE(Sistema &s, Cadena nombreArchivo, Cadena texto1,Cadena texto2) {
  
  // Chequea si el archivo existe
  if (!arbol_pertenece_un_nivel(arbol_actual(s), nombreArchivo)) {
    cout << "El archivo '" << nombreArchivo
         << "' no existe en el directorio actual" << endl;
    return ERROR;
  }

  // Encontrar el archivo
      Sistema archivo =
        arbol_ph(arbol_actual(s));  // bajamos un nivel desde el actual
    Sistema archivoAnterior = NULL;
    while (archivo != NULL && strcmp(arbol_nombre(archivo), nombreArchivo) != 0) {
      archivoAnterior = archivo;  
      archivo = arbol_sh(archivo);
    }
    if (arbol_tipo(archivo) == 0) {
      cout << "No se puede aplicar este comando sobre un directorio"
           << "." << endl;
      return ERROR;
    }

  // Realiza la búsqueda del texto dentro del archivo
  string contenidoArchivo_Rep = arbol_contenido(archivo);

  // Encuentra la primera ocurrencia del texto en el contenido del archivo
  size_t posicion_Rep = contenidoArchivo_Rep.find(texto1);

    // Verificamos permisos de escritura
   if (arbol_escritura(archivo)) {
    // Buscamos la posicion de la cadena texto1
     if (posicion_Rep != string::npos) {
  
      // Declaramos Cadenas auxiliares
      Cadena temp = new char[TEXTO_MAX];
      Cadena temp2 = new char[TEXTO_MAX];
      Cadena aux = new char[MAX_COMANDO];
      aux[0] = '\0';
      
      // Calculamos en que posicion culimina el texto a reemplazar
      int lugar_aux = static_cast<int>(posicion_Rep);
      int lugar = static_cast<int>(posicion_Rep)+strlen(texto1);
      
      // Calculamos cuantos caracteres hay desde donde termina la cadena a reemplazar hasta el final del contenido
      int temp2_length_aux = strlen(arbol_contenido(archivo));
      int temp2_length = temp2_length_aux-lugar;
      
      // Almacenamos el contenido desde el comienzo del contenido hasta el comienzo de la cadena a reemplazar
      strncpy(temp, arbol_contenido(archivo) + 0, posicion_Rep);
      temp[posicion_Rep] = '\0';
 
      // Almacenamos el contenido desde que culmina la cadena a reemplazar hasta que culmina el contenido del archivo
      strncpy(temp2, arbol_contenido(archivo) + lugar, temp2_length);
      temp2[temp2_length] = '\0';
     

      // Sumamos las cadenas de forma ordenada
      strcat(aux, temp);
      strcat(aux, texto2);
      strcat(aux, temp2);
      aux[strlen(aux)] = '\0';

        // Usando una cadena auxiliar verificamos que el reemplazo de la cadena previa por la nueva no sobrepase el limite del contenido
          if(strlen(aux) > TEXTO_MAX) {
          cout << "El texto ingresado hace que el archivo supere su limite de contenido" << endl;
           // Liberamos las Cadenas auxiliares
            delete[] temp;
            delete[] temp2;
            delete[] aux;
          return ERROR;
      } else { 
        
      //Ingresamos el contenido modificado al archivo
      strcpy(arbol_contenido(archivo), aux);

      // Liberamos las Cadenas auxiliares
      delete[] temp;
      delete[] temp2;
      delete[] aux;
      };

    return OK;
  } else {
    cout << "Texto no encontrado en el archivo." << endl;
    return ERROR;
  }
    } else {
      cout << "El archivo '" << nombreArchivo << "' es de solo lectura."
           << endl;
      return ERROR;
}
    } 

