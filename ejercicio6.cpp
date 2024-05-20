#include <cassert>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct NodoArista
{
    int id;
    int origen;
    int dest;
    int dist;
    int flujo;
    int estado;
    NodoArista *sig;
    NodoArista(int id, int origen, int dest, int dist, int flujo, int estado): id(id), origen(origen), dest(dest), dist(dist), flujo(flujo), estado(estado), sig(NULL) {}
};

typedef NodoArista *Lista;

class MinHeap
{
private:
    Lista *aristas;
    int largo;
    int ultimoLibre;

    int izq(int nodo)
    {
        return nodo * 2;
    }

    int der(int nodo)
    {
        return nodo * 2 + 1;
    }

    int padre(int nodo)
    {
        return nodo / 2;
    }

    void intercambiar(int x, int y)
    {
        NodoArista *aux = aristas[x];
        aristas[x] = aristas[y];
        aristas[y] = aux;
    }

    bool comparar(NodoArista *a, NodoArista *b)
    {
        if (a->dist != b->dist)
            return a->dist < b->dist;
        if (a->estado != b->estado)
            return a->estado < b->estado;
        if (a->flujo != b->flujo)
            return a->flujo > b->flujo;
        return a->id < b->id;
    }

    void flotar(int nodo){
        if (nodo != 1){
            int posPadre = padre(nodo);
            if (comparar(aristas[nodo], aristas[posPadre])){
                intercambiar(nodo, posPadre);
                flotar(posPadre);
            }
        }
    }

    void hundir(int nodo){
        if (izq(nodo) < ultimoLibre){ // Si tiene al menos un hijo
            int posIzq = izq(nodo);
            int posDer = der(nodo);
            int hijoMenor = posIzq;

            if (posDer < ultimoLibre && comparar(aristas[posDer], aristas[posIzq])){
                hijoMenor = posDer;
            }

            if (comparar(aristas[hijoMenor], aristas[nodo])){
                intercambiar(hijoMenor, nodo);
                hundir(hijoMenor);
            }
        }
    }

    void insertarAux(NodoArista *nuevaArista)
    {
        if (!estaLleno()){
            aristas[ultimoLibre] = nuevaArista;
            flotar(ultimoLibre);
            ultimoLibre++;
        }
    }

public:
    MinHeap(int tamanio)
    {
        aristas = new NodoArista *[tamanio + 1];
        largo = tamanio;
        ultimoLibre = 1;
    }

    ~MinHeap()
    {
        delete[] aristas;
    }

    bool esVacio()
    {
        return ultimoLibre == 1;
    }

    bool estaLleno()
    {
        return ultimoLibre == largo;
    }

    NodoArista *obtenerMinimo()
    {
        if (!esVacio())
        {
            NodoArista *ret = aristas[1];
            aristas[1] = aristas[ultimoLibre - 1];
            ultimoLibre--;
            hundir(1);
            return ret;
        }
        return NULL;
    }

    void insertar(NodoArista *nuevaArista)
    {
        this->insertarAux(nuevaArista);
    }
};

class MFSet
{
    int *altura, *parent, n;

public:
    MFSet(int n)
    {
        parent = new int[n];
        altura = new int[n];
        this->n = n;
        makeSet();
    }

    void makeSet()
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            // aplanamos el arbol
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void merge(int x, int y)
    {
        int xset = find(x);
        int yset = find(y);
        // si estan dentro del mismo set terminamos
        if (xset == yset)
            return;
        // evitamos aumentar la altura del arbol
        if (altura[xset] < altura[yset])
        {
            parent[xset] = yset;
        }
        else if (altura[xset] > altura[yset])
        {
            parent[yset] = xset;
        }
        // si ambas alturas con la misma usamos cualquiera y actualizamos la altura
        else
        {
            parent[yset] = xset;
            altura[xset] = altura[xset] + 1;
        }
    }
};

MinHeap *kruskal(int cantA, int cantV, MinHeap *aristas)
{
    MinHeap *solucion = new MinHeap(cantA);
    MFSet mfset(cantV + 1);
    int aceptadas = 0;
    while (!aristas->esVacio() || aceptadas < cantV - 1) //capaz va && en ves de ||
    {
        //cout << "Entro al while" << endl;
        //cout << "Aceptadas: " << aceptadas << endl;
        NodoArista *a = aristas->obtenerMinimo();
        if (mfset.find(a->origen) != mfset.find(a->dest))
        {
            //cout << "Entro al if" << endl;
            mfset.merge(a->origen, a->dest);
            solucion->insertar(a);
            aceptadas++;
        }
    }
    /* 
    if(aceptadas < cantV - 1){
        cout << "NO ES CONEXO. No se puede reparar la ciudad" << endl;
        return NULL;
    }
    */
    //cout << "Salio del while" << endl;
    return solucion;
}

int main()
{
    int cantV, cantA;
    cin >> cantV;
    cin >> cantA;
    MinHeap *aristas = new MinHeap(cantA);
    int origen, destino, flujo, estado, dist, id;
    for (int i = 0; i < cantA; i++)
    {
        cin >> origen;
        cin >> destino;
        cin >> id;
        cin >> dist;
        cin >> flujo;
        cin >> estado;
        NodoArista *nueva = new NodoArista(id, origen, destino, dist, flujo, estado);
        aristas->insertar(nueva);
    }
    MinHeap *resultado = kruskal(cantA, cantV, aristas);
    int sumaDist = 0;
    int promedioEstado = 0;
    for (int i = 0; i < (cantV - 1); i++)
    {
        NodoArista* min = resultado->obtenerMinimo();
        cout << min->origen << " " << min->dest << " " << min->id << " " 
        << min->dist << " " << min->flujo << " " << min->estado << endl;
        sumaDist += min->dist;
        promedioEstado += min->estado;
    }
    promedioEstado = promedioEstado/(cantV-1);
    cout << "Distancia total a reparar: " << sumaDist << endl;
    cout << "Estado promedio de las calles reparadas: " << promedioEstado << endl;
    delete aristas;
    delete resultado;
    return 0;
}
