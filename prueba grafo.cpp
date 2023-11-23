#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Guardian_Ranking {
    string Nombre;
    int Poder;
    string Maestro;
    string Ciudad;
};

struct CompareGuardians {
    bool operator()(const Guardian_Ranking& g1, const Guardian_Ranking& g2) const {
        // Comparar por cantidad de poder de forma descendente
        return g1.Poder > g2.Poder;
    }
};

int main() {
    multiset<Guardian_Ranking, CompareGuardians> guardianRanking; // Multiset para permitir duplicados

    ifstream archivo("Guardianes.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo 'Guardianes.txt'.";
        return 1;
    }

    // Leer la primera línea (encabezado) y descartarla
    string encabezado;
    getline(archivo, encabezado);

    string linea;
    while (getline(archivo, linea)) {
        istringstream ss(linea);
        Guardian_Ranking guardian;
        getline(ss, guardian.Nombre, ',');
        ss >> guardian.Poder;
        ss.ignore(); // Ignorar la coma después del poder
        getline(ss, guardian.Maestro, ',');
        getline(ss, guardian.Ciudad);

        guardianRanking.insert(guardian);
    }

    archivo.close();

    // Mostrar el ranking
    cout << "Guardianes Ranking (Ordenados por Poder de Mayor a Menor):\n";
    int posicion = 1;
    for (const Guardian_Ranking& guardian : guardianRanking) {
        cout << posicion << ". " << guardian.Nombre << " - Poder: " << guardian.Poder << endl;
        posicion++;
    }

    return 0;
}