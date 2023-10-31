//* Archivo donde definimos nuestras funciones

//** Importamos las bibliotecas necesarias
using namespace std; //** Usamos el bloque de codigo o region de std 
#include <iostream> //** Incluimos la libreria iostream para imprimir en pantalla
#include <string> //** Incluimos la libreria string para trabajar con cadenas de texto
#include <fstream> //** Incluimos la libreria file stream para trabajar con archivos
#include <vector> //** Incluimos la libreria para trabajar con vectores
#include "Funciones.hpp" //** Header con la declaracion de nuestras funciones

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
    while( pattern[y] != '\0' ){ //** Recorremos el patron hasta que lleguemos a un valor null
        if(pattern[y]==pattern[x]){ //** Evaluamos si los indices son iguales
            x++; //** Incrementamos el indice x un valor
            prefix[y]=x;
        }
        else{ //** Si los indices no son iguales
            x=0; //** Regresamos el indice x al inicio
            if(pattern[y]==pattern[x]){ //** Evaluamos si los indices son iguales
                x++; //** Incrementamos el indice x un valor
                prefix[y]=x;
            }
            else{
                prefix[y]=0; //** El valor de la casilla es default o 0
            }
        }
        y++; //** Incrementamos el indice y un valor
    }
    //** Retornamos nuestro vector de prefijos
    return prefix;
}

int kmp_function(string &transmission, string &pattern, vector<int> &prefix ){
    int i,j = 0; //** Inicializamos nuestro indices (uno para el patron y otro para la transmision)
    for(i; i<transmission.length(); i++){ //** Recorremos el archivo o mensaje de transmision
        if(pattern[j]=='\0'){ //** Si recorremos el patron completo, significa que esta dentro del mensaje
            return ((i+1)-pattern.length()); //** Regresamos la posicion final del indice de transmision
        }
        else if(transmission[i]==pattern[j]){ //** Si ambos indices son iguales avanza el indice de patron
            j++; //** Incrementa la probabilidad de que el patron este dentro del mensaje
        }
        else{
            j=prefix[j];
            if(transmission[i]==pattern[j]){ //** Si ambos indices son iguales avanza el indice de patron
                j++; //** Incrementa la probabilidad de que el patron este dentro del mensaje
            }
        }
    }
    return -1; //** Si no se encuentra el patron dentro del mensaje
}

/**
 * Parte Dos:
 * Debemos de hallar el palindromo mas largo dentro de los archivos de transmision, ya que existe la posibilidad de que el
 * codigo malicioso este "espejeado"
 */

static int *manacher_inner(char *pattern, int *biggest) //** Declaramos una funcion estatica que devuelve un entero
{
    int *l = (int *)malloc(sizeof(int) * strlen(pattern)); //** Creamos un arreglo dinamico de entero del tamaño del patron
    l[0] = 0; //** Inicializamos el arreglo con 0
    l[1] = 1;//** El segundo valor del arreglo lo inicializamos con 1
    int i = 1, count = 0; //** Creamos un contador y un indice que inicia desde el segundo elemento del arreglo
    for (int k = 2; k < strlen(pattern); k++) //** Recorremos nuestro patron desde el tercer elemento
    {
        //** Aplicamos el algoritmo de Manacher
        while((k - i) >= 0 && (k + i) < strlen(pattern) && pattern[k - i] == pattern[k + i]) //** Recorremos el patron desde la posicion k
        {
            i++; //** Incrementamos i
            count++; //**Incrementamos el contador
            if (count > *biggest)
                *biggest = count; //** Guardamos el palindormo mas largo
        }
        l[k] = count; //** Guardamos el contador en la posicion k y lo guardamos en nuestro arreglo
        count = 0; //** Reiniciamos el contador para cada nueva posicion k
        i = 1; //** Reiniciamos el indice
    }
    return l; //** Regresamos el arreglo
}

int manacher(const char *main, int *biggest) //** Declaramos la funcion de Manacher
{ 
    char *new_string = (char *)malloc(sizeof(char) * ((strlen(main) * 2) + 1)); //** Creamos un arreglo de strings

    new_string[0] = '$'; //** Inicializamos el arreglo con un caracter especial
    for (int i = 0; i < strlen(main); i++) //** Recorremos nuestro arreglo de strings
    {
        new_string[(i * 2) + 1] = main[i]; //** Insertamos las letras de nuestro string main en cada posicion par
        new_string[(i * 2) + 2] = '$'; //** Insertamos el caracter especial em cada posicion impar
    }

    int *l = manacher_inner(new_string, biggest); //** Generamos un arreglo y aplicamos el algortimo Manacher
    int position; //** Variable de posicion

    for (int i = 0; i < strlen(new_string); i++) //** Recoremos el arreglo de Manacher
    {
        if (l[i] == *biggest) //** Buscamos la posicion que contiene el palindromo mas largo
        {
            position = (i - *biggest) / 2;
            free(l); //** Liberamos memoria del arreglo de manacher
            free(new_string); //** Liberamos memoria del arreglo de string
            return(position); //** Regresamo la posicion donde se encuentra el palindromo mas largo
        }
    }

    free(l); //** Liberamos memoria del arreglo de manacher
    free(new_string); //** Liberamos memoria del arreglo de string
    return -1;
}

/**
 * Parte Tres:
 * La ultima parte se enfoca en comparar los archivos de transmision y encontrar el sub-string mas largo que 
 * ambos archivo poseen. 
 */

// Ahora la función devuelve una LCSResult en lugar de un std::pair
LCS_Result longest_common_substring(const std::string& s1, const std::string& s2) {
    int n1 = s1.size(), n2 = s2.size();
    std::vector<std::vector<int>> dp(n1 + 1, std::vector<int>(n2 + 1));
    int max_length = 0, end_index_s1 = 0;

    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max_length) {
                    max_length = dp[i][j];
                    end_index_s1 = i;
                }
            }
        }
    }

    // Crea una instancia de LCSResult con los resultados y la devuelve
    LCS_Result result;
    result.length = max_length;
    result.start_index = end_index_s1 - max_length;
    result.end_index = end_index_s1 - 1;
    
    return result;
}