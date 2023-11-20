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

int main()
{
	int menu;
	
	do
	{
		cout << "\nHola, Escoja la accion que desea realizar: "<<endl;
	
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
