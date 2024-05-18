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
    NodoListaInt *nuevo = new NodoListaInt(e);
    if (c->cant == 0)
    {
        c->ppio = c->cola = nuevo;
    }
    else
    {
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
        // Como es un grafo no dirigido, agregamos también la arista en sentido opuesto
        NodoLista *nuevoNodo2 = new NodoLista(v);
        nuevoNodo2->sig = lista[w];
        lista[w] = nuevoNodo2;
    }

    double BFS(int inicial)
    {
        int res = 0;
        ColaInt cola = crearColaInt();
        bool *encolados = new bool[V + 1]{false};
        int *distancia = new int[V + 1]{0}; // Inicializar las distancias en 0
        encolados[inicial] = true;
        encolar(cola, inicial);

        int totalVertices = 0;

        while (!esVacia(cola) && totalVertices < V)
        {
            int v = principio(cola);
            desencolar(cola);
            res += distancia[v]; // Sumar la distancia del nodo actual
            totalVertices++;

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

        delete[] encolados;
        delete[] distancia;
        destruir(cola);

        return double(res) / totalVertices; // Devolver el promedio de distancias
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
    double minPromedio = 1000000000;
    int paradaFugitivo = -1;
    for (int i = 1; i <= cantV; i++)
    {
        if (vec[i] > 2) // si es importante la parada
        {
            double promedio = grafo->BFS(i);
            if (promedio < minPromedio)
            {
                minPromedio = promedio;
                paradaFugitivo = i;
            }
        }
    }
    cout << "El fugitivo está en: " << paradaFugitivo << endl;
    delete[] vec;
    delete grafo;
    return 0;
}


