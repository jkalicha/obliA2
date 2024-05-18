#include <cassert>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct NodoListaInt
{
    int dato;
    NodoListaInt *sig;
    NodoListaInt(int v) : dato(v), sig(nullptr) {}
};

struct _cabezalColaInt
{
    NodoListaInt *ppio;
    NodoListaInt *cola;
    unsigned int cant;
};

typedef _cabezalColaInt *ColaInt;

ColaInt crearColaInt()
{
    ColaInt nuevo = new _cabezalColaInt();
    nuevo->ppio = NULL;
    nuevo->cola = NULL;
    nuevo->cant = 0;
    return nuevo;
}

void encolar(ColaInt &c, int e)
{
    if (c->cant == 0)
    {
        c->ppio = c->cola = new NodoListaInt(e);
    }
    else
    {
        NodoListaInt *nuevo = new NodoListaInt(e);
        c->cola->sig = nuevo;
        c->cola = nuevo;
    }
    c->cant++;
}

int principio(ColaInt c)
{
    if (c->cant > 0)
    {
        return c->ppio->dato;
    }
    return 0;
}

void desencolar(ColaInt &c)
{
    if (c->cant > 0)
    {
        NodoListaInt *aBorrar = c->ppio;
        c->ppio = c->ppio->sig;
        if (c->ppio == nullptr)
        {
            c->cola = nullptr;
        }
        delete aBorrar;
        c->cant--;
    }
}

bool esVacia(ColaInt c)
{
    return (c->cant == 0);
}

unsigned int cantidadElementos(ColaInt c)
{
    return c->cant;
}

void destruir(ColaInt &c)
{
    while (!esVacia(c))
    {
        desencolar(c);
    }
    delete c;
}

struct NodoLista
{
    int vertice;
    NodoLista *sig;
    int peso;
    NodoLista(int v, int p = 1, NodoLista *n = nullptr) : vertice(v), peso(p), sig(n) {}
};

typedef NodoLista *Lista;

class GrafoListaAdy
{
private:
    Lista *lista;
    int V;

public:
    GrafoListaAdy(int cantidadDeVertices)
    {
        V = cantidadDeVertices;
        lista = new Lista[V + 1];
        for (int i = 0; i <= V; i++)
        {
            lista[i] = nullptr;
        }
    }

    ~GrafoListaAdy()
    {
        for (int i = 0; i <= V; i++)
        {
            Lista actual = lista[i];
            while (actual != nullptr)
            {
                Lista tmp = actual;
                actual = actual->sig;
                delete tmp;
            }
        }
        delete[] lista;
    }

    void agregarArista(int v, int w)
    {
        NodoLista *nuevoNodo = new NodoLista(w);
        nuevoNodo->sig = lista[v];
        lista[v] = nuevoNodo;
    }

    int BFS(int inicial)
    {
        int res = 0;
        ColaInt cola = crearColaInt();
        bool *encolados = new bool[V + 1]{false};
        int *distancia = new int[V + 1]{0}; // Inicializar las distancias en 0
        encolados[inicial] = true;
        encolar(cola, inicial);

        while (!esVacia(cola))
        {
            int v = principio(cola);
            desencolar(cola);
            res += distancia[v]; // Sumar la distancia del nodo actual

            Lista aux = lista[v];
            while (aux != nullptr)
            {
                if (!encolados[aux->vertice])
                {
                    encolar(cola, aux->vertice);
                    encolados[aux->vertice] = true;
                    distancia[aux->vertice] = distancia[v] + 1; // Aumentar la distancia en 1
                }
                aux = aux->sig;
            }
        }
    }
};

int main()
{
    int cantV, cantCaminos, origen, destino;
    cin >> cantV;
    GrafoListaAdy *grafo = new GrafoListaAdy(cantV);
    int *vec = new int[cantV + 1]();
    cin >> cantCaminos;
    for (int i = 0; i < cantCaminos; i++)
    {
        cin >> origen;
        destino = -1; // entra al menos una vez al while
        while (destino != 0)
        {
            cin >> destino;
            if (destino == 0)
            {
                break;
            }
            grafo->agregarArista(origen, destino);
            vec[origen]++; // cuento cuantas salidas tiene esta parada
            vec[destino]++;
            origen = destino;
        }
    }
    int max = 0;
    for (int i = 1; i <= cantV; i++)
    {
        if (vec[i] > 2) // si es importante la parada
        {
            int actual = grafo->BFS(i);
            if (actual > max)
                max = actual;
        }
    }
    cout << max / cantV << endl;
    delete[] vec;
    delete grafo;
    return 0;
}
