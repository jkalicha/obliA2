#include <cassert>
#include <climits>
#include <iostream>

using namespace std;

struct NodoLista {
    int vertice;
    NodoLista *sig;
    NodoLista(int v) : vertice(v), sig(nullptr) {}
};

typedef NodoLista *Lista;

class GrafoListaAdyacencia {
private:
    Lista *lista;
    int cantV; // Cantidad de vértices

    void DFSUtil(int v, bool *visitados) {
        visitados[v] = true;
        NodoLista *aux = lista[v];
        while (aux != nullptr) {
            int ady = aux->vertice;
            if (!visitados[ady]) {
                DFSUtil(ady, visitados);
            }
            aux = aux->sig;
        }
    }

public:
    GrafoListaAdyacencia(int cantidadDeVertices) {
        cantV = cantidadDeVertices;
        lista = new Lista[cantV + 1];
        for (int i = 0; i <= cantV; i++) {
            lista[i] = nullptr;
        }
    }

    ~GrafoListaAdyacencia() {
        for (int i = 0; i <= cantV; i++) {
            Lista actual = lista[i];
            while (actual != nullptr) {
                Lista tmp = actual;
                actual = actual->sig;
                delete tmp;
            }
        }
        delete[] lista;
    }

    void agregarArista(int v, int w) {
        NodoLista *nuevoNodo = new NodoLista(w);
        nuevoNodo->sig = lista[v];
        lista[v] = nuevoNodo;
    }

    void DFS(int origen, bool *visitados) {
        DFSUtil(origen, visitados);
    }
};

int main() {
    int cantV;
    cin >> cantV;
    GrafoListaAdyacencia *grafo = new GrafoListaAdyacencia(cantV);
    int cantAristas;
    cin >> cantAristas;
    for (int i = 0; i < cantAristas; i++) {
        int origen, dest;
        cin >> origen >> dest;
        grafo->agregarArista(origen, dest);
    }
    bool *visitados = new bool[cantV + 1]{false}; 
    grafo->DFS(1, visitados);
    int cantDestinos;
    cin >> cantDestinos;
    for (int j = 0; j < cantDestinos; j++) {
        int dest;
        cin >> dest;
        if (visitados[dest])
            cout << dest << " si" << endl;
        else
            cout << dest << " no" << endl;
    }
    delete[] visitados;
    delete grafo;
    return 0;
}
