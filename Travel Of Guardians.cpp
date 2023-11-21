#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//Declaracion de estructura de guardian con los datos que se necesitan para ser cargados desde el archivo
struct Guardian
{
	string Nombre;
	int Poder;
	string Maestro;
	string Ciudad;
	
};


//************Fin declaracion de estructuras********

/*****Funcionamiento de jerarquia guardianes.*****/

using Arbol = unordered_map<string, vector<Guardian>>;//Codigo para generacion del mapa del arbol en base a un vector.

//En esta funcion se realiza la carga de informacion desde el archivo Guardianes.txt, para luego asignar los datos de todos y cada uno de los guardianes
void CargaInformacion(const string &Archivocarga, Arbol &arbol) {
    ifstream Archivo(Archivocarga);

    if (!Archivo.is_open()) {
        cout << "Error al abrir el archivo '" << Archivocarga << "'.";
        return;
    }

    string linea;
    while (getline(Archivo, linea)) {
        istringstream ss(linea);
        Guardian guardian;
        getline(ss, guardian.Nombre, ',');
        ss >> guardian.Poder;
        ss.ignore(); // Ignorar la coma despues del poder
        getline(ss, guardian.Maestro, ',');
        getline(ss, guardian.Ciudad);

        // Agregar el guardian al arbol
        arbol[guardian.Maestro].push_back(guardian);
    }

    Archivo.close();
}

/*En esta funcion se recorre el arbol creado a partir de los datos del archivo y luego se procede a imprimirlo en el formato que se necesite.
 En este caso se busca imprimirlos en orden jerarquico.*/
void imprimirArbol(const Arbol &arbol, const string &raiz, int nivel) {
    if (arbol.find(raiz) == arbol.end()) {
        return;
    }

    for (const auto &guardian : arbol.at(raiz)) {
        for (int i = 0; i < nivel; ++i) {
            cout << "  ";
        }
        cout << "- " << guardian.Nombre << " (" << guardian.Ciudad << ")\n";

        // Llamada recursiva para imprimir los hijos del guardian actual
        imprimirArbol(arbol, guardian.Nombre, nivel + 1);
    }
}
//***************Fin funcionalidades Jerarquia**********

//***********Funcionalidades arbol binario**********
/*Por medio de esta funcion ordenaremos segun el nivel de poder los guardianes.*/
struct Ranking
{
	int data;
	Ranking* left;
	Ranking* right;	
};

//Funcion para crear nodos en el ranking.
Ranking* CrearRank(int data)
{
	Ranking* Nuevorank = new Ranking;
	Nuevorank -> data = data;
	Nuevorank -> left = NULL;
	Nuevorank -> right = NULL;
	return Nuevorank;
}

//*********Fin funcionalidades arbol Binario.********

//**********Funcionalidades grafo Ciudades********

using Grafo = unordered_map<string, unordered_set<string>>;

void CargaInfociudades(const string &CargaArchivo, Grafo &grafo, unordered_set<string> &ciudadesUnicas) {
    ifstream archivo(CargaArchivo);

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo '" << CargaArchivo << "'.";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string ciudad1, ciudad2;
        getline(ss, ciudad1, ',');
        getline(ss, ciudad2);

        // Agregar conexiones al grafo no dirigido
        grafo[ciudad1].insert(ciudad2);
        grafo[ciudad2].insert(ciudad1);

        // Agregar ciudades al conjunto
        ciudadesUnicas.insert(ciudad1);
        ciudadesUnicas.insert(ciudad2);
    }

    archivo.close();
}

void imprimirGrafo(const Grafo &grafo) {
    cout << "Grafo de Ciudades:\n";
    for (const auto &par : grafo) {
        cout << par.first << ": ";
        for (const auto &vecino : par.second) {
            cout << vecino << " ";
        }
        cout << "\n";
    }
}

void imprimirMatrizAdyacenciaConLetras(const unordered_set<string> &ciudadesUnicas, const Grafo &grafo, const unordered_map<string, char> &ciudadLetra) {
    cout << "\nMatriz de Adyacencia con letras:\n";

    // Imprimir encabezado
    cout << "   ";
    for (const auto &ciudad : ciudadesUnicas) {
        cout << ciudadLetra.at(ciudad) << " ";
    }
    cout << "\n";

    // Imprimir filas de la matriz
    for (const auto &ciudad : ciudadesUnicas) {
        cout << ciudadLetra.at(ciudad) << ": ";
        for (const auto &otraCiudad : ciudadesUnicas) {
            cout << (grafo.at(ciudad).count(otraCiudad) > 0 ? "1 " : "0 ");
        }
        cout << "\n";
    }
}

//*********Fin funcionalidades para grafo*******


// Funcion para agregar ejes y crear grafo de las ciudades
void addEdge(vector<vector<int>>& graph, int u, int v) {
graph[u][v] = 1;
graph[v][u] = 1;
}

// Funcion para imprimir la matriz de adyacencia
/*Por medio de esta funcion vamos a mostrar la matriz con las conexiones que tiene cada ciudad con otra.*/
void printGraph(const vector<vector<int>>& graph) {
	cout << "Matriz de adyacencia:\n";
	for (const auto& row : graph) {
		for (int val : row) {
		cout << val << " ";
		}
	cout << '\n';
	}
}


int main()
{
	int menu;
	
	Arbol arbol;
	
	struct NodoCiudad *listaCiudades = NULL;
	
	Grafo grafo;
    unordered_set<string> ciudadesUnicas;
    CargaInfociudades("ciudades.txt", grafo, ciudadesUnicas);
    
    // Asignar letras a las ciudades
	unordered_map<string, char> ciudadLetra;
	char letra = 'A';
	for (const auto &ciudad : ciudadesUnicas) 
	{
		ciudadLetra[ciudad] = letra;
		++letra;
	}
	
	do
	{
		cout << "Hola, Escoja la accion que desea realizar: "<<endl;
	
		cout<< "(1)Carga de informacion Guardianes(jerarquia).\n(2)Ver Lista de Candidatos.\n(3)Ver al Guardian.\n(4)Conocer el reino.\n(5)Presenciar una batalla.\n(0)Salir"<<endl;
		cin>> menu;
		
		switch(menu)
		{
			case 1:
				CargaInformacion("Guardianes.txt", arbol);
				cout << "arbol de Personajes:\n";
    			imprimirArbol(arbol, "None", 0);
				break;
				
			case 2: 
			
			    // En este for se asignan las letras a las ciudades
			    cout << "\nNomenclatura de letras \n";
			    for (const auto &par : ciudadLetra) {
			        cout << par.second << ":" << par.first << "\n";
			    }
			
				// Imprimir la matriz asignada
				imprimirMatrizAdyacenciaConLetras(ciudadesUnicas, grafo, ciudadLetra);
				break;
			
			case 3:
				cout<<"Hola";
				break;
			
			case 4: 
				cout<<"Ahora el 4 subnormal.";
				break;
				
			case 5:
				cout<<"Este es el ultimo.";
				break;
				
			case 0:
				cout<<"Cerrando el programa....";
				break;
				
			default:
				cout<<"Opcion no valida.";
				break;
										 		
		}
	} while(menu !=0 );
	
	
	return 0;
}
