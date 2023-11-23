#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
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

//Declaracion de estructura de guardian para funcionamiento del ranking.
struct Guardian_Ranking {
    string Nombre;
    int Poder;
    string Maestro;
    string Ciudad;
};

//Estructura para realizar la comparativa del poder de los guardianes que se encuentran dentro de la estructura "Guardian_Ranking"
struct CompareGuardians {
    bool operator()(const Guardian_Ranking& g1, const Guardian_Ranking& g2) const {
        // Comparar por cantidad de poder de forma descendente
        return g1.Poder > g2.Poder;
    }
};


//************Fin declaracion de estructuras********

/*****Funcionamiento de jerarquia guardianes*****/

using Arbol = unordered_map<string, vector<Guardian>>;//Codigo para generacion del mapa del arbol en base a un vector.

//En esta funcion se realiza la carga de informacion desde el archivo Guardianes.txt, para luego asignar los datos de todos y cada uno de los guardianes
void CargaInformacion(const string &Archivocarga, Arbol &arbol) {
    ifstream Archivo(Archivocarga);

    if (!Archivo.is_open()) {
        cout << "Error al abrir el archivo '" << Archivocarga << "'.";
        return;
    }
	
	//Asignamos la informacion extraida a las variables de la estructura Guardian
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

//**********Funcionalidades grafo Ciudades********

typedef pair<string, string> Ciudad;
typedef unordered_map<string, char> Representaciones;
typedef unordered_map<string, int> Indices;

//En este vector leemos el archivo .txt asignado a la variable "archivo" el cual es asignado con el nombre del archivo.
vector<Ciudad> leerCiudades(const string &archivo) {
    vector<Ciudad> ciudades;
    ifstream f(archivo);

    if (!f.is_open()) {
        cerr << "No se pudo encontrar el archivo: " << archivo << endl;
        return ciudades;
    }
	
	//aca tomamos los nombres de las ciudades y los asignamos a las variables para luego identificar las conexiones entre ellas
    string linea;
    while (getline(f, linea)) {
        size_t pos = linea.find(',');
        if (pos != string :: npos) {
            string ciudad1 = linea.substr(0, pos);
            string ciudad2 = linea.substr(pos + 1);
            ciudades.push_back(Ciudad(ciudad1, ciudad2));
        }
    }

    f.close();
    return ciudades;
}

//Funcion que utiliza la informacion recopilada en el vector Ciudad para luego tomar los datos y extraerlos para utilizarlos como indices
vector<string> obtenerNombresCiudades(const vector<Ciudad> &ciudades) {
    Indices indices;
    vector<string> nombres;

    for (const Ciudad &c : ciudades) {
        if (indices.find(c.first) == indices.end()) {
            indices[c.first] = nombres.size();
            nombres.push_back(c.first);
        }
        if (indices.find(c.second) == indices.end()) {
            indices[c.second] = nombres.size();
            nombres.push_back(c.second);
        }
    }

    return nombres;
}

//Esta funcion recorren e imprime la matriz de adyacencia del grafo de las ciudades
void mostrarMatriz(const vector<Ciudad> &ciudades, const vector<string> &nombres, const Representaciones &representaciones) {
    Indices indices;
    for (size_t i = 0; i < nombres.size(); ++i) {
        indices[nombres[i]] = i;
    }
	
	//toma las representaciones de los nombres en la matriz
    vector<vector<char>> matriz(nombres.size(), vector<char>(nombres.size(), '-'));

    for (const Ciudad &c : ciudades) {
        int i = indices[c.first];
        int j = indices[c.second];
        matriz[i][j] = representaciones.at(c.second);
        matriz[j][i] = representaciones.at(c.first);
    }

    Representaciones representaciones_copy = representaciones; // Copia de representaciones
	
	//A continuacion se muestra la matriz creada con las representaciones de las letras por ciudad y las conexiones que tiene cada una.
	cout<<"\nMatriz de Adyacencia Ciudades"<<endl;
	
    cout << "  ";
    for (size_t i = 0; i < nombres.size(); ++i) {
        cout << representaciones_copy[nombres[i]] << " ";
    }
    cout << endl;

    for (size_t i = 0; i < nombres.size(); ++i) {
        cout << representaciones_copy[nombres[i]] << " ";
        for (size_t j = 0; j < nombres.size(); ++j) {
            if (matriz[i][j] == '-') {
                cout << "0 ";
            } else {
                cout << "1 ";
            }
        }
        cout << std::endl;
    }
}

//*********Fin funcionalidades para grafo*******

//*********Funcionalidades de Conocer el reino*************

//Dentro de esta funcion se encuentra un menu con opciones disponibles para el usuario en las cuales puede realizar consultas generales acerca de las ciudades.
void ConocerElReino(vector<string> &nombres, const Representaciones &representaciones, multiset<Guardian_Ranking, CompareGuardians> &guardianRanking)
{
    int opcion;
    cout << "Escoja la accion que desea realizar:" << endl;

    cout << "(1)Viajar a traves del Reino.\n(2)Crear Nuevos Caminos.\n(3)Consultar Caminos Existentes.\n(0)Salir.\n";
    cin >> opcion;


    switch (opcion)
    {
    case 1:
        cout << "Viajar";
        break;

    case 2:
        //cout <<"Crear";
        crearNuevosCaminos(matrizAdyacencia, nombres, representaciones);
        break;

    case 3:
        cout << "Consultar";
        break;

    case 0:
        cout << "Saliendo al menu";
        break;

    default:
        cout << "Opcion no valida";
    }
}


int main()
{
	int menu;
	
	Arbol arbol;
	
	//**********Funcionalidades para grafo de ciudades**************
	
	vector<vector<int>> matrizAdyacencia;
	string archivo = "Ciudades.txt";//se declara archivo con el nombre del archivo .txt que se necesita
    vector<Ciudad> ciudades = leerCiudades(archivo);//aplicamos la funcion para leer el archivo deseado
    vector<string> nombres = obtenerNombresCiudades(ciudades);//Obtenemos los nombres de las ciudades por medio de la funcion llamada

    Representaciones representaciones;// aca se declara la variable para las representaciones de las ciudades por medio de letras
    
    //En este for recorremos las ciudades y asignamos una letra a cada una para ser representada correctamente en la matriz
	for (size_t i = 0; i < nombres.size(); ++i) {
        representaciones[nombres[i]] = i < 26 ? static_cast<char>('A' + i) : static_cast<char>('a' + i - 26);
    }
    
    //***************Fin funcionalidades para grafo de ciudades*************
    
    
    //**************Inicio Funcionalidades para Ranking*******************
    
    multiset<Guardian_Ranking, CompareGuardians> guardianRanking; // Multiset para permitir duplicados y no provocar omision de informacion
    
    ifstream archivo2("Guardianes.txt");// se asigna el nombre del archivo que se utiliza para extraer los datos.
    
    //Dentro de este if se verifica si se encuentra el archivo, para luego de haberlo encontrado asignar los datos correspondientes a cada variable de la estructura Guardian_Ranking
    if (!archivo2.is_open()) {
			        cout << "Error al abrir el archivo 'Guardianes.txt'.";
			        return 1;
			    }
			
			    // Lee la primera linea  y la descarta
			    string encabezado;
			    getline(archivo2, encabezado);
				
				//aca asignamos las datos a sus variables correspondientes.
			    string linea;
			    while (getline(archivo2, linea)) {
			        istringstream ss(linea);
			        Guardian_Ranking guardian;
			        getline(ss, guardian.Nombre, ',');
			        ss >> guardian.Poder;
			        ss.ignore(); // Ignorar las comas despues del poder
			        getline(ss, guardian.Maestro, ',');
			        getline(ss, guardian.Ciudad);
			
			        guardianRanking.insert(guardian);
			    }
			
	archivo2.close();
	
	int posicion = 1;
	
	//*************Fin funcionalidades para Ranking***************
	
	do
	{
		cout << "Hola, Escoja la accion que desea realizar: "<<endl;
	
		cout<< "(1)Carga de informacion Guardianes(jerarquia).\n(2)Ver Lista de Candidatos.\n(3)Ver al Guardian.\n(4)Conocer el reino.\n(5)Presenciar una batalla.\n(0)Salir"<<endl;
		cin>> menu;
		
		switch(menu)
		{
			case 1:
				//*******Carga informacion de guardianes***********
				
				CargaInformacion("Guardianes.txt", arbol);//Se realiza el llamado a la funcion correspondiente para realizar la carga de archivo segun su nombre y tipo.
				cout << "Arbol de Personajes:\n";
    			imprimirArbol(arbol, "None", 0);
    			
    			//*********Asignacion e impresion de matriz*********
    			
    			mostrarMatriz(ciudades, nombres, representaciones);//Mostramos la matriz con la informacion de las conexiones entre las ciudades.
    			
    			//En este codigo se asigna la nomenclatura de a que ciudad equivale cada letra en la matriz.
			    cout << "Nomenclatura: " << endl;
				for (size_t i = 0; i < nombres.size(); ++i) {
				    cout << representaciones[nombres[i]] << " = " << nombres[i] << endl;
				}
    			
    			break;
				
			case 2: 
			
			    // Mostrar el ranking
			    cout << "Guardianes Ranking (Ordenados por Poder de Mayor a Menor):\n";
			    
			    //se recorre el arbol Guardian_Ranking para mostrar la informacion del ranking.
			    for (const Guardian_Ranking& guardian : guardianRanking) {
			        cout << posicion << ". " << guardian.Nombre << " - Poder: " << guardian.Poder << endl;
			        posicion++;
			    }
				break;
			
			case 3:
				//cout<<"Hola";
				ConocerElReino(matrizAdyacencia, nombres, representaciones, guardianRanking);
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