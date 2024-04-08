#include "model.h"

using namespace std;

model::model(){}

void model::agregarNodo(LinkedList& lista) {
    int x, y;
    cout << "Ingrese la coordenada x del nuevo nodo: ";
    cin >> x;
    cout << "Ingrese la coordenada y del nuevo nodo: ";
    cin >> y;
    lista.append(x, y);
    cout << "Nodo agregado exitosamente." << endl;
}

void model::eliminarNodo(LinkedList& lista) {
    if (lista.head == nullptr) {
        cout << "No hay nodos guardados." << endl;
        return;
    }

    cout << "Nodos guardados:" << endl;
    int ind = 0;
    Node* temp = lista.head;
    while (temp != nullptr) {
        cout << "Índice " << ind << ": Coordenada x: " << temp->x << ", Coordenada y: " << temp->y << endl;
        temp = temp->next;
        ind++;
    }

    int indice;
    cout << "Ingrese el índice del nodo que desea eliminar: ";
    cin >> indice;

    Node* current = lista.head;
    Node* prev = nullptr;
    int contador = 0;
    while (current != nullptr && contador < indice) {
        prev = current;
        current = current->next;
        contador++;
    }

    if (current != nullptr && contador == indice) {
        if (prev == nullptr) { // El nodo a eliminar es la cabeza
            lista.head = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        cout << "Nodo eliminado exitosamente." << endl;
    } else {
        cout << "Índice de nodo inválido." << endl;
    }
}

void model::consultarActualizarNodo(LinkedList& lista) {
    if (lista.head == nullptr) {
        cout << "No hay nodos guardados." << endl;
        return;
    }

    cout << "Nodos guardados:" << endl;
    int indice = 0;
    Node* temp = lista.head;
    while (temp != nullptr) {
        cout << "Índice " << indice << ": Coordenada x: " << temp->x << ", Coordenada y: " << temp->y << endl;
        temp = temp->next;
        indice++;
    }

    cout << "Ingrese el número de índice del nodo que desea consultar o actualizar:" << endl;
    cin >> indice;

    temp = lista.head;
    int contador = 0;
    while (temp != nullptr && contador < indice) {
        temp = temp->next;
        contador++;
    }

    if (temp != nullptr && contador == indice) {
        cout << "Nodo encontrado. ¿Desea actualizar las coordenadas? (S/N): ";
        char respuesta;
        cin >> respuesta;
        if (toupper(respuesta) == 'S') {
            cout << "Ingrese las nuevas coordenadas:" << endl;
            cout << "Nueva coordenada x: ";
            cin >> temp->x;
            cout << "Nueva coordenada y: ";
            cin >> temp->y;
            cout << "Nodo actualizado correctamente." << endl;
        } else {
            cout << "Coordenadas del nodo:" << endl;
            cout << "Coordenada x: " << temp->x << endl;
            cout << "Coordenada y: " << temp->y << endl;
        }
    } else {
        cout << "Índice fuera de rango. No se pudo encontrar el nodo." << endl;
    }
}


double model::calcularDistancia(const Node* nodo1, const Node* nodo2) {
    double diff_x = nodo2->x - nodo1->x;
    double diff_y = nodo2->y - nodo1->y;
    return sqrt(diff_x * diff_x + diff_y * diff_y);
}

double** model::calcularDistancias(const LinkedList& lista) {
    // Obtener el número de nodos en la lista
    int n = 0;
    Node* temp = lista.head;
    while (temp != nullptr) {
        ++n;
        temp = temp->next;
    }

    // Crear la matriz de distancias
    double** distancias = new double*[n];
    for (int i = 0; i < n; ++i) {
        distancias[i] = new double[n];
    }

    // Calcular las distancias entre todos los pares de nodos
    temp = lista.head;
    for (int i = 0; i < n; ++i) {
        Node* temp2 = lista.head;
        for (int j = 0; j < n; ++j) {
            if (temp != nullptr && temp2 != nullptr) {
                distancias[i][j] = calcularDistancia(temp, temp2);
            } else {
                // Manejo de error: si uno de los nodos es nulo, asignar una distancia grande
                distancias[i][j] = std::numeric_limits<double>::infinity();
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }

    return distancias;
}

void model::mostrarTablaDistancias(const LinkedList& lista) {
    cout << "Tabla de distancias:" << endl;

    int n = 0; // Inicializar el contador de nodos

    // Contar el número total de nodos en la lista
    Node* tempCount = lista.head;
    while (tempCount != nullptr) {
        ++n;
        tempCount = tempCount->next;
    }

    // Mostrar la numeración en la parte superior
    cout << " ";
    for (int i = 0; i < n; ++i) {
        cout << setw(4) << i << "\t";
    }
    cout << endl;

    Node* temp1 = lista.head;
    int i = 0;
    while (temp1 != nullptr) {
        Node* temp2 = lista.head;
        cout << i << "|"; // Mostrar la numeración en el lado izquierdo
        int j = 0;
        while (temp2 != nullptr) {
            if (temp1 != temp2) {
                cout << fixed << setprecision(2) << setw(4) << calcularDistancia(temp1, temp2) << "\t|";
            } else {
                cout << setw(4) << "-\t|"; // Si los nodos son iguales, imprimir un guión en su lugar
            }
            temp2 = temp2->next;
            ++j;
        }
        cout << endl;
        temp1 = temp1->next;
        ++i;
    }
}


void model::vecinoMasCercano(const LinkedList& lista) {
    if (lista.head == nullptr) {
        cout << "No hay nodos guardados." << endl;
        return;
    }

    // Obtener el número de nodos en la lista
    int cantidadNodos = 0;
    Node* temp = lista.head;
    while (temp != nullptr) {
        ++cantidadNodos;
        temp = temp->next;
    }

    // Matriz de distancias
    double** distancias = calcularDistancias(lista); // Revisar esta función

    // Arreglo para almacenar el camino
    int* camino = new int[cantidadNodos + 1]; // +1 para el nodo inicial al final del camino
    bool* visitado = new bool[cantidadNodos](); // Inicializado en falso por defecto

    // Elegir un nodo inicial aleatorio
    int nodoActual = 0;
    camino[0] = nodoActual;
    visitado[nodoActual] = true;

    // Iterar para agregar nodos al camino
    for (int i = 1; i < cantidadNodos; ++i) {
        // Encontrar el vecino más cercano no visitado
        int vecinoMasCercano = -1;
        double distanciaMinima = numeric_limits<double>::max();
        for (int j = 0; j < cantidadNodos; ++j) {
            if (!visitado[j] && distancias[nodoActual][j] < distanciaMinima) { // Revisar acceso a la matriz de distancias
                vecinoMasCercano = j;
                distanciaMinima = distancias[nodoActual][j];
            }
        }
        // Agregar el vecino más cercano al camino
        camino[i] = vecinoMasCercano;
        visitado[vecinoMasCercano] = true;
        nodoActual = vecinoMasCercano;
    }

    // Agregar el nodo inicial al final del camino para cerrarlo
    camino[cantidadNodos] = camino[0];

    // Liberar la memoria de la matriz de distancias y el arreglo de visitados
    for (int i = 0; i < cantidadNodos; ++i) {
        delete[] distancias[i];
    }
    delete[] distancias;
    delete[] visitado;

    // Imprimir el ciclo
    imprimirCiclo(camino, cantidadNodos);
}

void model::rutaPorInsercion(const LinkedList& lista) {
    if (lista.head == nullptr) {
        cout << "No hay nodos disponibles para calcular la ruta." << endl;
        return;
    }

    int cantidadNodos = 0;
    Node* temp = lista.head;
    while (temp != nullptr) {
        ++cantidadNodos;
        temp = temp->next;
    }

    int ruta[cantidadNodos];
    bool visitado[cantidadNodos] = {false};

    // Elegir el primer nodo como punto de partida
    int nodoInicial = 0;
    ruta[0] = nodoInicial;
    visitado[nodoInicial] = true;

    for (int i = 1; i < cantidadNodos; ++i) {
        double distanciaMinima = numeric_limits<double>::max();
        int posicionMinima = -1;
        for (int j = 0; j < cantidadNodos; ++j) {
            if (!visitado[j]) {
                for (int k = i - 1; k >= 0; --k) {
                    double distancia = calcularDistancia(&lista.head[ruta[k]], &lista.head[j]);
                    if (distancia < distanciaMinima) {
                        distanciaMinima = distancia;
                        posicionMinima = k;
                    }
                }
            }
        }
        // Insertar el nodo en la posición que minimiza la distancia total
        int nodoInsertar = -1;
        for (int j = 0; j < cantidadNodos; ++j) {
            if (!visitado[j]) {
                nodoInsertar = j;
                break;
            }
        }
        for (int l = i; l > posicionMinima + 1; --l) {
            ruta[l] = ruta[l - 1];
        }
        ruta[posicionMinima + 1] = nodoInsertar;
        visitado[nodoInsertar] = true;
    }

    // Imprimir la ruta
    imprimirRuta(ruta, cantidadNodos);
}

void model::imprimirCiclo(int ciclo[], int cantidadNodos) {
    cout << "Ciclo del vecino más cercano:" << endl;
    for (int i = 0; i < cantidadNodos; ++i) {
        cout << ciclo[i] << " ";
    }
    cout << ciclo[0] << endl; // Regresar al nodo inicial para cerrar el ciclo
}

void model::imprimirRuta(int ruta[], int cantidadNodos) {
    cout << "Ruta encontrada por inserción:" << endl;
    for (int i = 0; i < cantidadNodos; ++i) {
        cout << ruta[i] << " ";
    }
    cout << "0" << endl; // Regresar al nodo inicial para cerrar el ciclo
}

