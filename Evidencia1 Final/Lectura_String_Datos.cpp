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
#include "Funciones.hpp" //** Header con la declaracion de nuestras funciones 

/**
 * En la funcion main tenemos nuestras funciones desplegadas una vez que las declaramos y definimos
 * en los archivos de funciones.h y funciones.cpp para tener un mejor control sobre 
 * ellas.
 */

static void part1(std::vector <std::string> t, std::vector <std::string> m)
{
    int identificar;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            vector<int> prefix = prefix_function(m[j]);

            int identificar = kmp_function(t[i],m[j],prefix);
            if(identificar == -1){
                cout << "false" << endl;
            }
            else{
                cout << "true " << "el archivo de transmision" << i+1 << " contiene el codigo mcode" << j+1 << " en la posicion " << identificar << endl;
            }
        }
    }
}

static void part2(std::vector <std::string> t)
{
    int find_pos;

    for (int i = 0; i < 2; i++)
    {
        int size = 0;
        find_pos = manacher(t[i].c_str(), &size);
        printf("%d %d\n", find_pos, size + find_pos);
    }
}

static void part3(const std::vector<std::string>& t) {
    LCS_Result result = longest_common_substring(t[0], t[1]);
    printf("%d %d\n", result.start_index, result.end_index);
}



int main(){

    //** Vectores de strings

    std::vector <std::string> t;
    std::vector <std::string> m;

    //** Archivos

    t.push_back(lectura_txt("transmission1.txt"));
    t.push_back(lectura_txt("transmission2.txt"));
    m.push_back(lectura_txt("mcode1.txt"));
    m.push_back(lectura_txt("mcode2.txt"));
    m.push_back(lectura_txt("mcode3.txt"));

    //** Ejecucion de la parte 1

    printf("Parte 1:\n");
    part1(t, m);

    //** Ejecucion de la parte 2

    printf("Parte 2:\n");
    part2(t);

    //** Ejecucion de la parte 3

    printf("Parte 3:\n");
    part3(t);

    return 0;
}