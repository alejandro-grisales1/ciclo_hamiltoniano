#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Definición de la estructura de un nodo de la lista enlazada
struct Node {
    int x;
    int y;
    bool visitado; // Agregar el miembro visitado
    
    Node* next;

    // Constructor
    Node(int x_val, int y_val) : x(x_val), y(y_val), next(nullptr) {}
};

// Definición de la estructura de la lista enlazada
struct LinkedList {
    Node* head;

    // Constructor
    LinkedList() : head(nullptr) {}

    // Método para crear un nuevo nodo
    Node* crearNodo(int x, int y) {
        return new Node(x, y);
    }

    // Método para agregar un nodo al final de la lista
    void append(int x, int y) {
        Node* newNode = crearNodo(x, y);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Método para mostrar los nodos de la lista
    void display() {
        Node* temp = head;
        int i = 1;
        while (temp != nullptr) {
            cout << "Nodo " << i++ << ": (" << temp->x << ", " << temp->y << ")" << endl;
            temp = temp->next;
        }
    }

    // Método para liberar la memoria asignada a los nodos de la lista
    void liberarMemoria() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Definición de la estructura de model
struct model {
    // Constructor
    model();

    // Funciones
    void agregarNodo(LinkedList& lista);
    void eliminarNodo(LinkedList& lista);
    void consultarActualizarNodo(LinkedList& lista);
    double calcularDistancia(const Node* nodo1, const Node* nodo2);
    double **calcularDistancias(const LinkedList &lista);
    void mostrarTablaDistancias(const LinkedList &lista);
    void vecinoMasCercano(const LinkedList& lista);
    void rutaPorInsercion(const LinkedList& lista);
    void imprimirCiclo(int ciclo[], int cantidadNodos);
    void imprimirRuta(int ruta[], int cantidadNodos);
};