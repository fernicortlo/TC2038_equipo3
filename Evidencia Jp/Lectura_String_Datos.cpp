/** Primera evidencia de Algoritmos Avanzados: Transmision de datos comprometida
 * 
 * En esta evidencia evaluaremos codigo malicioso dentro de protocolos o metodos de 
 * comunicacion, los cuales usamos dia a dia. Nuestra mision es identificar este codigo
 * y eliminarlo antes de que llegue a su destino, con el proposito de generar daños a 
 * personas o compañias.
*/

//** Importamos las bibliotecas necesarias
using namespace std; //** Usamos el bloque de codigo o region de std 
#include <iostream> //** Incluimos la libreria iostream para imprimir en pantalla
#include <string> //** Incluimos la libreria string para trabajar con cadenas de texto
#include <fstream> //** Incluimos la libreria file stream para trabajar con archivos
#include <vector> //** Incluimos la libreria para trabajar con vectores
#include "Funciones.h" //** Header con la declaracion de nuestras funciones 

/**
 * En la funcion main tenemos nuestras funciones desplegadas una vez que las declaramos y definimos
 * en los archivos de funciones.h y funciones.cpp para tener un mejor control sobre 
 * ellas.
 * 
 */

int main(){
    string archivo_malo = lectura_txt("mcode1.txt");
    vector<int> prefix = prefix_function(archivo_malo);
    for(int i=0; i<prefix.size(); i++){
     cout << prefix[i];
    }
    return 0;
}