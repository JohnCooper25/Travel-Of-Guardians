#include <iostream>
#include <vector>
using namespace std;

struct Guardian
{
	string Nombre;
	int Poder;
	string Maestro;
	vector<Guardian*> aprendices;
};

//Funcion para arbol Binario.
/*Por medio de esta funcion ordenaremos segun el nivel de poder los guardianes.*/
struct Ranking
{
	int data;
	Node* left;
	Node* right;	
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



void CargaInformacion()
{
			
}

int main()
{
	int menu;
	
	do
	{
		cout << "Hola, Escoja la accion que desea realizar: "<<endl;
	
		cout<< "(1)Carga de informacion.\n(2)Ver Lista de Candidatos.\n(3)Ver al Guardian.\n(4)Conocer el reino.\n(5)Presenciar una batalla.\n(0)Salir"<<endl;
		cin>> menu;
		
		switch(menu)
		{
			case 1:
				cout<<"Hola caso 1 aweonao.";
				break;
				
			case 2: 
				cout<<"Caso 2 pedazo de pete.";
				break;
			
			case 3:
				cout<<"Ahora el 3 aweonaito.";
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
