//* Incluimos las librerias
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

//* Tarea de Algormitmos

//*Algormitos de Kruskal

//*Primero leemos el archivo de texto

vector <vector<int>> leerArchivo(string archivo){
    vector <vector<int>> contenido; //* Vector que guarda el vectores de enteros completo
    ifstream csv(archivo); //* El ifstream es una clase que permite el modo lectura del archivo
    if(csv.is_open()){ //* Revisa si el archivo esta abierto
        string linea; //* Linea del documento (conexion entre nodos y su peso)
        while(getline(csv,linea)){ //* Bucle que recorre todas las lineas
            vector <int> conexiones;//* Creamos un vector para guardar dos nodos
            istringstream stream(linea); //* Creamos un stream (secuencia de datos) a partir de un string
            string caracter; //* Variable que cotiene un numero por separado
            while(stream >> caracter){ //* Leemos los numeros de la linea por separados
                int numero = stoi(caracter); //*Convertimos los caracteres en numeros enteros
                conexiones.push_back(numero); //* Añadimos los numeros al final del vector
            }
            contenido.push_back(conexiones);//* Agregamos los valores al final del arreglo principal
        } 
        csv.close(); //* Cerramos la lectura
    }else{
        cout << "No se pudo leer el archivo" << endl; //* Imprimimos un mensaje de error si el archivo no se abre
    }
    // for(int i=0; i<contenido.size(); i++){ //* Imprimimos todos los elementos del vector principal
    //     for(int j=0; j<contenido[i].size(); j++){
    //         cout << contenido[i][j];
    //     }
    //     cout << "\n";
    // }
    // cout << contenido[13][2]; //* Se imprime el ultimo elemento del vector de vectores
    return contenido; //* Regresamos el vector de vectores
}

//* Algoritmo tipo sort: Usamos un sort para ordenar los pesos de cada conexion o del grafo

bool Comp(vector<int> a,vector<int> b){ //* Creamos una funcion que verifique y compare siempre el tercer elemento del vector. Luego, programamos que debe de ser en orden ascendente.
    return a[2] < b[2]; //* Devuelve true si el valor a debe de ir antes que b. False, si el valor a debe ir despues de b
}

vector <vector<int>> Sort(vector<vector<int>> grafo){
    sort(grafo.begin(),grafo.end(),Comp);
    // for (int i=0; i<grafo.size(); i++) {
    //         for(int j=0; j<grafo[i].size();j++){
    //             cout<<grafo[i][j]<<" ";
    //         }
    //         cout<<"\n";
    //     }
    return grafo;
}

//* Segundo Algoritmo de Kruskal

//* Algoritmo de kruskal, es un algoritmo vor que tiene el proposito de hallar MST en un grafo no dirigido. Se debe de ordenar el peso del grafo en forma ascendente

vector <vector<int>> Kruskal(string archivo){ //* El algoritmo de Kruskal recibe un .txt con espacios y devuelve un vector de enteros
    vector <vector<int>> Kruskal; //* Vector que contiene el MST
    vector <int> Vertices; 
    vector <vector<int>> Grafo = leerArchivo(archivo); //* Creamos el grafo a partir de un .txt
    Grafo = Sort(Grafo); //* Organizamos el grafo del menor al mayor peso
    for(int i=0; i < Grafo.size(); i++){
        if(find(Vertices.begin(), Vertices.end(), Grafo[i][0]) != Vertices.end() && find(Vertices.begin(), Vertices.end(), Grafo[i][1]) != Vertices.end()){
            cout << "Ya existe conexion" << endl;
        }
        else{
            if(find(Vertices.begin(), Vertices.end(), Grafo[i][0]) == Vertices.end()){
                Vertices.push_back(Grafo[i][0]);
            }if(find(Vertices.begin(), Vertices.end(), Grafo[i][1]) == Vertices.end()){
                Vertices.push_back(Grafo[i][1]);
            }
            Kruskal.push_back(Grafo[i]);
        }
    }
    for(int i=0; i<Kruskal.size(); i++){
        for(int j=0; j<Kruskal[i].size(); j++){
            cout << Kruskal[i][j] << " ";
        }
        cout << endl;
    }
    return Kruskal;
     
}

int main(){
    Kruskal("test.txt");
}