//* Archivo donde definimos nuestras funciones

//** Importamos las bibliotecas necesarias
using namespace std; //** Usamos el bloque de codigo o region de std 
#include <iostream> //** Incluimos la libreria iostream para imprimir en pantalla
#include <string> //** Incluimos la libreria string para trabajar con cadenas de texto
#include <fstream> //** Incluimos la libreria file stream para trabajar con archivos
#include <vector> //** Incluimos la libreria para trabajar con vectores
#include "Funciones.h" //** Header con la declaracion de nuestras funciones

/**
 * Parte Cero: Lectura de archivos txt
 * 1. Lectura de archivos maliciosos mcode.txt : contiene caracteres de 0-9 y de A-F
 * 2. Lectura de archivos de transmision transmission.txt : contiene caracteres de 0-9 y de A-F
 */

string lectura_txt(string archivo){
    ifstream leerArchivo; //** Declaramos un flujo de entrada de archivo
    string line, res = ""; //** Variable que almacenara una linea del archivo y variable vacia
    leerArchivo.open(archivo); //** Abrimos el archivo a leer
    while (getline(leerArchivo, line)) { //** Leemos cada linea del archivo
        res += line; //** Agregamos cada linea del archivo a la variable res
    }
    leerArchivo.close(); //** Cerramos el archivo despues de leerlo
    return res; //** Devolvemos la cadena completa del archivo
}

/**
 * Parte Uno: 
 * Debemos de identificar que los archivos mcode.txt estan dentro de los archivos de transmission.txt. De ser asi
 * debemos de retornar el valor desde donde inicia el patron en el archivo.
 */

/**
 * Para este primer enfoque usamos la funcion de KMP (Knuth-Morris-Pratt) para encontrar el patron dentro de un string
 * las n veces que deseamos evitando el backtracking. Este algortimos se compone de una sub-funcione: funcion de prefijo
 * 
 */

vector<int> prefix_function(string &pattern){ //** Creamo una funcion que devuelve un entero 
    int x=0,y=1; //** Inicializamos nuestros indices (El numero indica la posicion)
    vector<int> prefix(pattern.length()); //** Creamos un vector con respecto a la longitud del patron
    //** Inicializamos nuestro prefijo con 0
    prefix[0]=0;
    //** Recorremos el patron
    while( prefix[y] != '\0' ){
        if(prefix[y]==prefix[x]){
            prefix[y]=x;
            x++;
        }
        else if(prefix[y]==prefix[0]){
            prefix[y]=0;
            x=1;
        }
        else{
            prefix[y]=0;
            x=0;
        }
        y++;
    }
    //** Retornamos nuestro vector de prefijos
    return prefix;
}

// vector<int> kmp_function(string &transmission, string &pattern, )