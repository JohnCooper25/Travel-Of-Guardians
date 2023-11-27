#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
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


struct CompareGuardians {
    bool operator()(const Guardian_Ranking& lhs, const Guardian_Ranking& rhs) const {
        return lhs.Poder > rhs.Poder; // Modifica la lógica según tus necesidades
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
void mostrarMatriz(const vector<Ciudad>& ciudades, const vector<string>& nombres, Representaciones& representaciones) {
    Indices indices;
    for (size_t i = 0; i < nombres.size(); ++i) {
        indices[nombres[i]] = i;
    }

    // Actualizar representaciones para incluir nuevas ciudades si es necesario
    for (const Ciudad& conexion : ciudades) {
        if (representaciones.find(conexion.first) == representaciones.end()) {
            representaciones[conexion.first] = representaciones.size() < 26 ? static_cast<char>('A' + representaciones.size()) : static_cast<char>('a' + representaciones.size() - 26);
        }
        if (representaciones.find(conexion.second) == representaciones.end()) {
            representaciones[conexion.second] = representaciones.size() < 26 ? static_cast<char>('A' + representaciones.size()) : static_cast<char>('a' + representaciones.size() - 26);
        }
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
void ConocerElReino(vector<Ciudad> &ciudades, vector<string> &nombres, Representaciones &representaciones)  {
    
	int opcion;
    string ciudadElegida;
    
    string ciudad1, ciudad2;
    
    cout << "Escoja la accion que desea realizar:" << endl;
    cout << "(1) Mostrar Ciudades y Conexiones.\n(2) Crear Nuevos Caminos.\n(3) Consultar Rutas entre ciudades.\n(4)Eliminar Caminos.\n(0) Salir.\n";
    cin >> opcion;

    switch (opcion) {
        case 1:
            // Mostrar todas las ciudades existentes
            cout << "Ciudades Disponibles:\n";
            for (const string &ciudad : nombres) {
                cout << "- " << ciudad << endl;
            }

            // Permitir al jugador elegir una ciudad
            
            cout << "Ingrese el nombre de la ciudad que desea explorar: ";
            cin.ignore(); 
            getline(cin, ciudadElegida);

            // Mostrar las conexiones de la ciudad elegida
            cout << "Conexiones de la Ciudad " << ciudadElegida << ":\n";
            for (const Ciudad &conexion : ciudades) {
                if (conexion.first == ciudadElegida || conexion.second == ciudadElegida) {
                    string otraCiudad = (conexion.first == ciudadElegida) ? conexion.second : conexion.first;
                    cout << "- Conectada con " << otraCiudad << endl;
                }
            }
            break;

        case 2:
        {
        	cout << "Ciudades Disponibles:\n";
		    for (const string& ciudad : nombres) {
		        cout << "- " << ciudad << endl;
		    }
		
		    string ciudad1, ciudad2;
		    char nuevaConexion;
		
		    cout << "Ingrese el nombre de la primera ciudad: ";
		    cin.ignore();
		    getline(cin, ciudad1);
		
		    cout << "Ingrese el nombre de la segunda ciudad: ";
		    getline(cin, ciudad2);
		
		    // Verificar si la conexion ya existe
		    bool conexionExistente = false;
		    for (const Ciudad& conexion : ciudades) {
		        if ((conexion.first == ciudad1 && conexion.second == ciudad2) || (conexion.first == ciudad2 && conexion.second == ciudad1)) {
		            conexionExistente = true;
		            break;
		        }
		    }
		
		    if (conexionExistente) {
		        cout << "La conexion entre " << ciudad1 << " y " << ciudad2 << " ya existe.\n";
		    } else {
		        cout << "Desea crear una nueva conexion entre " << ciudad1 << " y " << ciudad2 << "? (S/N): ";
		        cin >> nuevaConexion;
		
		        if (nuevaConexion == 'S' || nuevaConexion == 's') {
		            // Agregar la nueva conexion al vector de ciudades
		            ciudades.push_back(Ciudad(ciudad1, ciudad2));
		
		            // Mostrar la matriz de adyacencia actualizada
		            mostrarMatriz(ciudades, nombres, representaciones);
		        } else {
		            cout << "No se creo una nueva conexion.\n";
		        }
		    }
		    break;		
		}
        case 3:
	    {
		    cout << "Ciudades Disponibles:\n";
		    for (const string &ciudad : nombres) {
		        cout << "- " << ciudad << endl;
		    }
		
		    string ciudadOrigen, ciudadDestino;
		    cout << "Ingrese el nombre de la ciudad de origen: ";
		    cin.ignore();
		    getline(cin, ciudadOrigen);
		
		    cout << "Ingrese el nombre de la ciudad de destino: ";
		    getline(cin, ciudadDestino);
		
		    // Verificar si las ciudades están conectadas directamente
		    bool conexionDirecta = false;
		    for (const Ciudad &conexion : ciudades) {
		        if ((conexion.first == ciudadOrigen && conexion.second == ciudadDestino) ||
		            (conexion.first == ciudadDestino && conexion.second == ciudadOrigen)) {
		            conexionDirecta = true;
		            break;
		        }
		    }
		
		    if (conexionDirecta) {
		        cout << "Las ciudades " << ciudadOrigen << " y " << ciudadDestino << " tienen conexion directa.\n";
		    } 
			else {
		        // BFS
		        queue<string> cola;
		        unordered_map<string, string> padres;
		
		        cola.push(ciudadOrigen);
		        padres[ciudadOrigen] = "";
		
		        bool rutaEncontrada = false;
		
		        while (!cola.empty()) {
		            string actual = cola.front();
		            cola.pop();
		
		            for (const Ciudad &conexion : ciudades) {
		                if (conexion.first == actual || conexion.second == actual) {
		                    string vecino = (conexion.first == actual) ? conexion.second : conexion.first;
		
		                    if (padres.find(vecino) == padres.end()) {
		                        cola.push(vecino);
		                        padres[vecino] = actual;
		
		                        if (vecino == ciudadDestino) {
		                            rutaEncontrada = true;
		                            break;
		                        }
		                    }
		                }
		            }
		
		            if (rutaEncontrada) {
		                break;
		            }
		        }
		
				// Mostrar la ruta sugerida
				if (rutaEncontrada) {
				    cout << "Ruta sugerida: ";
				    
				    // Construye la ruta en el orden correcto
				    vector<string> ruta;
				    string ciudadActual = ciudadDestino;
				
				    while (!padres[ciudadActual].empty()) {
				        ruta.push_back(ciudadActual);
				        ciudadActual = padres[ciudadActual];
				    }
				
				    ruta.push_back(ciudadOrigen);  // Aniadir la ciudad de origen
				
				    // Imprimir la ruta en el orden correcto
				    for (auto it = ruta.rbegin(); it != ruta.rend(); ++it) {
				        cout << *it;
				        if (next(it) != ruta.rend()) {
				            cout << " -> ";
				        }
				    }
				
				    cout << endl;
				} else {
				    cout << "No se encontro una ruta sugerida.\n";
				}
		
		    break;
		}
	}
	    	
        case 4:  
		{
		    cout << "Ciudades Disponibles:\n";
		    for (const string &ciudad : nombres) {
		        cout << "- " << ciudad << endl;
		    }
		
		    string ciudad1, ciudad2;
		    char eliminarConexion;
		
		    cout << "Ingrese el nombre de la primera ciudad: ";
		    cin.ignore();
		    getline(cin, ciudad1);
		
		    cout << "Ingrese el nombre de la segunda ciudad: ";
		    getline(cin, ciudad2);
		
		    // Verificar si la conexion existe
		    auto it = find_if(ciudades.begin(), ciudades.end(), [&](const Ciudad &conexion) {
		        return (conexion.first == ciudad1 && conexion.second == ciudad2) ||
		               (conexion.first == ciudad2 && conexion.second == ciudad1);
		    });
		
		    if (it != ciudades.end()) {
		        cout << "Desea eliminar la conexion entre " << ciudad1 << " y " << ciudad2 << "? (S/N): ";
		        cin >> eliminarConexion;
		
		        if (eliminarConexion == 'S' || eliminarConexion == 's') {
		            // Eliminar la conexion del vector de ciudades
		            ciudades.erase(it);
		
		            // Mostrar la matriz de adyacencia actualizada
		            mostrarMatriz(ciudades, nombres, representaciones);
		        } else {
		            cout << "No se elimino la conexion.\n";
		        }
		    } else {
		        cout << "La conexion entre " << ciudad1 << " y " << ciudad2 << " no existe.\n";
		    }
		    break;
		}
    	
    	case 0:
    		cout<< "Saliendo al menu";
			break;
		default :
			cout<<"Opcion no disponible.";			    
    }
}

//**********Fin de funcionalidades Conocer El Reino************

bool esMaestroDeAlguien(const string& nombreGuardian, const vector<Guardian_Ranking>& guardianRanking) {
    // Verificar si el guardian es maestro de algún aprendiz
    return any_of(guardianRanking.begin(), guardianRanking.end(), [&](const Guardian_Ranking& guardian) {
        return guardian.Maestro == nombreGuardian;
    });
}
void mostrarGuardianesParaBatalla(const vector<Guardian_Ranking>& guardianRanking) {
    cout << "Guardianes para Batalla (con menos de 90 puntos y no son maestros):\n";

    for (const Guardian_Ranking& guardian : guardianRanking) {
        // Verificar que el poder sea menor de 90 y que no sea maestro de ningun aprendiz
        if (guardian.Poder < 90 && !esMaestroDeAlguien(guardian.Nombre, guardianRanking)) {
            cout << "- " << guardian.Nombre << " - Poder: " << guardian.Poder << endl;
        }
    }
}


void Batalla(const Arbol &arbol, vector<Guardian_Ranking> &guardianRanking){

    int OPC;
	mostrarGuardianesParaBatalla(guardianRanking);
    // Solicitar al jugador que elija un guardian
    string nombreGuardianElegido;
    cout << "Ingrese el nombre del guardian que desea para la batalla: ";
    cin.ignore();
    getline(cin, nombreGuardianElegido);

    // Verificar que el guardian elegido esté en la lista y obtener su información
    auto itGuardian = find_if(guardianRanking.begin(), guardianRanking.end(), [&](const Guardian_Ranking &guardian) {
        return guardian.Nombre == nombreGuardianElegido;
    });

    if (itGuardian != guardianRanking.end()) {
        // Mostrar otros guardianes en la misma ciudad sin incluir al guardian seleccionado
        string ciudadGuardianElegido = itGuardian->Ciudad;

        cout << "Guardianes en la misma ciudad (" << ciudadGuardianElegido << "):\n";
        for (const Guardian_Ranking &otroGuardian : guardianRanking) {
            if (otroGuardian.Ciudad == ciudadGuardianElegido && otroGuardian.Nombre != nombreGuardianElegido) {
                cout << "- " << otroGuardian.Nombre << " - Poder: " << otroGuardian.Poder << endl;
            }
        }

        do {
            cout << "Escoja la acción que desea realizar: " << endl;
            cout << "(1) Pelear Con Rivales de la ciudad.\n(2) Viajar.\n(0) Salir al Menú Principal.\n";
            cin >> OPC;

            switch (OPC) {
                case 1: 
				{
				    // Obtener la ciudad del guardian elegido previamente
				    auto itGuardianElegido = find_if(guardianRanking.begin(), guardianRanking.end(), [&](const Guardian_Ranking &guardian) {
				        return guardian.Nombre == nombreGuardianElegido;
				    });
				
				    if (itGuardianElegido != guardianRanking.end()) {
				        // Mostrar otros guardianes en la misma ciudad sin incluir al guardian seleccionado localmente
				        string ciudadGuardianElegido = itGuardianElegido->Ciudad;
				
				        cout << "Guardianes en la misma ciudad (" << ciudadGuardianElegido << ") para la batalla:\n";
				        for (const Guardian_Ranking &otroGuardian : guardianRanking) {
				            if (otroGuardian.Ciudad == ciudadGuardianElegido && otroGuardian.Nombre != nombreGuardianElegido) {
				                cout << "- " << otroGuardian.Nombre << " - Poder: " << otroGuardian.Poder << endl;
				            }
				        }
				
				        // Solicitar al jugador que elija un guardian contra el que pelear
				        string nombreGuardianContra;
				        cout << "Ingrese el nombre del guardian contra el que desea pelear: ";
				        cin.ignore();
				        getline(cin, nombreGuardianContra);
				
				        // Verificar que el guardian contra el que pelear esté en la lista y obtener su información
				        auto itGuardianContra = find_if(guardianRanking.begin(), guardianRanking.end(), [&](const Guardian_Ranking &guardian) {
				            return guardian.Nombre == nombreGuardianContra;
				        });
				
				        if (itGuardianContra != guardianRanking.end()) {
				            // Realizar la simulación del duelo
				            bool esLocal = ciudadGuardianElegido == itGuardianContra->Ciudad;
				            double probabilidadGanarLocal = 0.5;  // Probabilidad de ganar si ambos son locales
				
				            if (!esLocal) {
				                probabilidadGanarLocal = 0.4;  // Probabilidad de ganar si el usuario es visitante
				            }
				
				            // Simulación aleatoria
				            double resultado = ((double)rand() / RAND_MAX);  // Número aleatorio entre 0 y 1
				
				            // Mostrar el resultado del duelo
				            cout << "Duelo!\n";
				            cout << nombreGuardianElegido << " vs. " << nombreGuardianContra << "\n";
				
				            // Modificar puntos de poder según el resultado del duelo
				            if (resultado < probabilidadGanarLocal) {
				                // El ganador gana 5 puntos de poder
				                itGuardianElegido->Poder += 5;
				                // El perdedor pierde 1 punto de poder
				                itGuardianContra->Poder -= 1;
				
				                cout << nombreGuardianElegido << " gana el duelo!\n";
				            } else {
				                // El ganador gana 5 puntos de poder
				                itGuardianContra->Poder += 5;
				                // El perdedor pierde 1 punto de poder
				                itGuardianElegido->Poder -= 1;
				
				                cout << nombreGuardianContra << " gana el duelo!\n";
				            }
				        } else {
				            cout << "Guardian contra el que pelear no encontrado en la lista.\n";
				        }
				    } else {
				        cout << "Guardian elegido previamente no encontrado en la lista.\n";
				    }
				    break;
				}

                case 2:
                    break;

                case 0:
                    cout << "Volviendo al menú principal..." << endl;
                    break;

                default:
                    cout << "Opción no válida";
                    break;
            }
        } while (OPC != 0);

    } else {
        cout << "Guardian no encontrado en la lista.\n";
    }
}



int main()
{
	int menu;
	
	Arbol arbol;
	
	//**********Funcionalidades para grafo de ciudades**************
	
	//vector<vector<int>> matrizAdyacencia;
	string archivo = "Ciudades.txt";   //se declara archivo con el nombre del archivo .txt que se necesita
	
    vector<Ciudad> ciudades = leerCiudades(archivo);  //aplicamos la funcion para leer el archivo deseado
    
    vector<string> nombres = obtenerNombresCiudades(ciudades);//Obtenemos los nombres de las ciudades por medio de la funcion llamada

    Representaciones representaciones;// aca se declara la variable para las representaciones de las ciudades por medio de letras
    
    //En este for recorremos las ciudades y asignamos una letra a cada una para ser representada correctamente en la matriz
	for (size_t i = 0; i < nombres.size(); ++i) {
        representaciones[nombres[i]] = i < 26 ? static_cast<char>('A' + i) : static_cast<char>('a' + i - 26);
    }
    
    //***************Fin funcionalidades para grafo de ciudades*************
    
    
    //**************Inicio Funcionalidades para Ranking*******************
    
    vector<Guardian_Ranking> guardianRanking; // Multiset para permitir duplicados y no provocar omision de informacion
    
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
			        
			    // Lee el resto de las líneas
				string linea;
				while (getline(archivo2, linea)) {
				    istringstream ss(linea);
				    Guardian_Ranking guardian;
				    getline(ss, guardian.Nombre, ',');
				    ss >> guardian.Poder;
				    ss.ignore(); // Ignorar las comas después del poder
				    getline(ss, guardian.Maestro, ',');
				    getline(ss, guardian.Ciudad);
				
				    // Agregar el guardian a guardianRanking
				    guardianRanking.push_back(guardian);
				}
				
				// Ordenar guardianRanking después de cargar todos los guardianes
				sort(guardianRanking.begin(), guardianRanking.end(), CompareGuardians());    
							
							        
			    }
			
	archivo2.close();
	
	int posicion = 1;
	
	
	
	//Bool para comprobar la busqueda de guardian
	bool encontrado = false;
	//Guarda el guardian elegido a buscar
	string nombreGuardianElegido;
	
	// Buscar el guardian en el arbol
	Guardian guardianElegido;
	
	//*************Fin funcionalidades para Ranking***************
	
	do
	{
		
		nombreGuardianElegido = "";  // Reiniciar el nombre del guardian elegido
    	encontrado = false;
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
			{
				 // Mostrar los guardianes con poder entre 90 y 99
			    cout << "Guardianes con Poder entre 90 y 99 (Ordenados por Poder de Mayor a Menor):\n";
			
			    int posicion = 1;
			    for (const Guardian_Ranking& guardian : guardianRanking) {
			        if (guardian.Poder >= 90 && guardian.Poder <= 99) {
			            cout << posicion << ". " << guardian.Nombre << " - Poder: " << guardian.Poder << endl;
			            posicion++;
			        }
			    }
			
			    // Si no hay guardianes en el rango, mostrar un mensaje
			    if (posicion == 1) {
			        cout << "No hay guardianes con poder entre 90 y 99.\n";
			    }
			    break;	
			}
			   
			case 3:
				// Mostrar todos los guardianes disponibles
			    cout << "Lista de Guardianes Disponibles:\n";
			    for (const auto& pair : arbol) {
			        for (const Guardian& guardian : pair.second) {
			            cout << "- " << guardian.Nombre << endl;
			        }
			    }
			
			    // Solicitar al jugador que elija un guardian
			    cout << "Ingrese el nombre del guardian que desea ver: ";
			    cin.ignore(); 
			    getline(cin, nombreGuardianElegido);
			
			    // Evitamos problemas de mayusculas y minusculas
			    transform(nombreGuardianElegido.begin(), nombreGuardianElegido.end(), nombreGuardianElegido.begin(), ::tolower);
			
			    for (const auto& pair : arbol) {
			        for (const Guardian& guardian : pair.second) {
			            // Convertir a minusculas para evitar problemas 
			            string nombreGuardianActual = guardian.Nombre;
			            transform(nombreGuardianActual.begin(), nombreGuardianActual.end(), nombreGuardianActual.begin(), ::tolower);
			
			            if (nombreGuardianActual == nombreGuardianElegido) {
			                guardianElegido = guardian;
			                encontrado = true;
			                break;
			            }
			        }
			        if (encontrado) {
			            break;
			        }
			    }
			
			    // Mostrar detalles del guardian elegido
			    if (encontrado) {
			        cout << "Detalles del Guardian:\n";
			        cout << "Nombre: " << guardianElegido.Nombre << endl;
			        cout << "Poder: " << guardianElegido.Poder << endl;
			        cout << "Maestro: " << guardianElegido.Maestro << endl;
			        cout << "Ciudad: " << guardianElegido.Ciudad << endl;
			    } else {
			        cout << "Guardian no encontrado.\n";
			    }
				break;
			
			case 4:
				ConocerElReino(ciudades, nombres, representaciones);
				break;
				
			case 5:
				{
				Batalla(arbol, guardianRanking);
				break;
					
				}
				
				
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
