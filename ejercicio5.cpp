#include <cassert>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

const int INF = numeric_limits<int>::max();

struct NodoLista
{
    int vertice;
    int peso;
    NodoLista *sig;
    NodoLista(int v, int p, NodoLista *n = nullptr) : vertice(v), peso(p), sig(n) {}
};

class GrafoListaAdy
{
private:
    NodoLista **grafo;
    int V;

public:
    GrafoListaAdy(int cantV) : V(cantV)
    {
        grafo = new NodoLista *[V + 1]();
    }

    ~GrafoListaAdy()
    {
        for (int i = 1; i <= V; ++i)
        {
            NodoLista *temp = grafo[i];
            while (temp != nullptr)
            {
                NodoLista *prev = temp;
                temp = temp->sig;
                delete prev;
            }
        }
        delete[] grafo;
    }

    void agregarArista(int v, int w, int peso = 1)
    {
        grafo[v] = new NodoLista(w, peso, grafo[v]);
        grafo[w] = new NodoLista(v, peso, grafo[w]); // Si el grafo es no dirigido
    }

    int dijkstra(int origen)
    {
        int *distancia = new int[V + 1];
        fill_n(distancia, V + 1, INF);
        distancia[origen] = 0;

        bool *visitados = new bool[V + 1]();
        for (int count = 0; count < V - 1; count++)
        {
            int u = -1;
            for (int i = 1; i <= V; i++)
                if (!visitados[i] && (u == -1 || distancia[i] < distancia[u]))
                    u = i;
            visitados[u] = true;

            NodoLista *temp = grafo[u];
            while (temp != nullptr)
            {
                int v = temp->vertice;
                int peso = temp->peso;
                if (!visitados[v] && distancia[u] + peso < distancia[v])
                {
                    distancia[v] = distancia[u] + peso;
                }
                temp = temp->sig;
            }
        }

        int maxDist = 0;
        for (int i = 1; i <= V; i++)
        {
            if (distancia[i] != INF && distancia[i] > maxDist)
            {
                maxDist = distancia[i];
            }
        }
        delete[] distancia;
        delete[] visitados;
        return maxDist;
    }
};

int main()
{
    int V;
    cin >> V;
    GrafoListaAdy *grafo = new GrafoListaAdy(V);
    int caminos;
    cin >> caminos;
    bool *paradasImportantes = new bool[V + 1](); // Inicializa todos los elementos a false
    for (int i = 0; i < caminos; i++)
    {
        int origen, destino;
        cin >> origen;
        while (true)
        {
            cin >> destino;
            if (destino == 0)
                break;
            grafo->agregarArista(origen, destino);
            origen = destino;
        }
    }

    int res = -1;
    int maxDist = -1;
    for (int i = 1; i <= V; i++)
    {
        if (paradasImportantes[i])
        {
            int dijkstraCaminoLargo = grafo->dijkstra(i);
            if (dijkstraCaminoLargo > maxDist)
            {
                maxDist = dijkstraCaminoLargo;
                res = i;
            }
        }
    }

    cout << "El fugitivo esta en " << res << endl;

    delete[] paradasImportantes;
    delete grafo;

    return 0;
}