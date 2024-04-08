#include "view.h"

using namespace std;

view::view(){}

void view::mostrarBienvenida()
{
  cout << "\n\n******************************************************" << endl;
  cout << "*BIENVENIDOS A NUESTRO PROGRAMA DE CICLO HAMILTONIANO*" << endl;
  cout << "******************************************************\n" << endl;
}

void view::menu()
{
  cout << "\n1. AGREGAR NODO" << endl;
  cout << "2. ELIMINAR NODO" << endl;
  cout << "3. ACTUALIZAR NODO" << endl;
  cout << "4. SIGUIENTE" << endl;
  cout << "5. SALIR" << endl;
  cout << "\nINGRESE LA OPCION: ";
}

void view::menu2()
{
  cout << "\n1. VER TABLA DE ADYACENCIA" << endl;
  cout << "2. VECINO MÁS CERCANO" << endl;
  cout << "3. INSERCIÓN MÁS CERCANA" << endl;
  cout << "4. ANTERIOIR " << endl;
  cout << "5. SALIR" << endl;
  cout << "\nINGRESE LA OPCION: ";
}