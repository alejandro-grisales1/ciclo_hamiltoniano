#include "controller.h"

using namespace std;

controller::controller() {}

void controller::inicializar()
{
    view vi;
    model mo;

    LinkedList lista; // Crear una lista enlazada para almacenar los nodos

    char opcion;
    char opcion2;
    bool salir = false;

    vi.mostrarBienvenida();

    while (!salir)
    {
        vi.menu();
        cin >> opcion;

        switch (opcion)
        {
        case '1':
            mo.agregarNodo(lista);
            break;
        case '2':
            mo.eliminarNodo(lista);
            break;
        case '3':
            mo.consultarActualizarNodo(lista);
            break;
        case '4':
            while (true)
            {
                vi.menu2();
                cin >> opcion2;

                switch (opcion2)
                {
                case '1':
                    mo.mostrarTablaDistancias(lista);
                    break;
                case '2':
                    mo.vecinoMasCercano(lista);
                    break;

                case '3':
                    mo.rutaPorInsercion(lista);
                    break;

                case '4':
                    cout << "Volviendo al menú principal..." << endl;
                    break; // Salir del bucle del menú secundario

                case '5':
                    exit(0); // Salir del programa
                    break;   // Salir del bucle del menú secundario

                default:
                    cout << "Opción inválida." << endl;
                    break;
                }

                if (opcion2 == '4') // Si se selecciona la opción para volver al menú principal
                    break;
            }
            break;
        case '5':
            cout << "Saliendo del programa..." << endl;
            salir = true; // Salir del programa
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
            break;
        }
    }

    // No es necesario liberar memoria manualmente, ya que LinkedList maneja su propia
    // liberación de memoria cuando se destruye.
}
