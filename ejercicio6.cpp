#include <cassert>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct NodoArista {
    int id;
    int origen;
    int dest;
    int dist;
    int flujo;
    int estado;
    NodoArista *sig;
    NodoArista(int id, int origen, int dest, int dist, int flujo, int estado)
        : id(id), origen(origen), dest(dest), dist(dist), flujo(flujo), estado(estado), sig(NULL) {}
};

class MinHeap {
private:
    NodoArista** aristas;
    int largo;
    int ultimoLibre;

    int izq(int nodo) {
        return nodo * 2;
    }

    int der(int nodo) {
        return nodo * 2 + 1;
    }

    int padre(int nodo) {
        return nodo / 2;
    }

    void intercambiar(int x, int y) {
        NodoArista* aux = aristas[x];
        aristas[x] = aristas[y];
        aristas[y] = aux;
    }

    bool comparar(NodoArista* a, NodoArista* b) {
        if (a->dist != b->dist)
            return a->dist < b->dist;
        if (a->estado != b->estado)
            return a->estado > b->estado;
        if (a->flujo != b->flujo)
            return a->flujo > b->flujo;
        return a->id < b->id;
    }

    void flotar(int nodo) {
        if (nodo != 1) {
            int posPadre = padre(nodo);
            if (comparar(aristas[nodo], aristas[posPadre])) {
                intercambiar(nodo, posPadre);
                flotar(posPadre);
            }
        }
    }

    void hundir(int nodo) {
        if (izq(nodo) < ultimoLibre) {  // Si tiene al menos un hijo
            int posIzq = izq(nodo);
            int posDer = der(nodo);
            int hijoMenor = posIzq;

            if (posDer < ultimoLibre && comparar(aristas[posDer], aristas[posIzq])) {
                hijoMenor = posDer;
            }

            if (comparar(aristas[hijoMenor], aristas[nodo])) {
                intercambiar(hijoMenor, nodo);
                hundir(hijoMenor);
            }
        }
    }

    void insertarAux(NodoArista* nuevaArista) {
        if (!estaLleno()) {
            aristas[ultimoLibre] = nuevaArista;
            flotar(ultimoLibre);
            ultimoLibre++;
        }
    }

public:
    MinHeap(int tamanio) {
        aristas = new NodoArista*[tamanio + 1];
        largo = tamanio;
        ultimoLibre = 1;
    }

    ~MinHeap() {
        delete[] aristas;
    }

    bool esVacio() {
        return ultimoLibre == 1;
    }

    bool estaLleno() {
        return ultimoLibre == largo;
    }

    NodoArista* obtenerMinimo() {
        if (!esVacio()) {
            NodoArista* ret = aristas[1];
            aristas[1] = aristas[ultimoLibre - 1];
            ultimoLibre--;
            hundir(1);
            return ret;
        }
        return NULL;
    }

    void imprimirHeap() {
        cout << "Array: " << endl;
        for (int i = 1; i < ultimoLibre; i++) {
            cout << aristas[i]->id << " ";
        }
        cout << endl;
        cout << "Arbol:" << endl;
        int cantidadPorNivel = 1;
        int impresosDelNivel = 0;
        for (int i = 1; i < ultimoLibre; i++) {
            cout << aristas[i]->id << " ";
            impresosDelNivel++;
            if (cantidadPorNivel == impresosDelNivel) {
                cout << endl;
                cantidadPorNivel *= 2;
                impresosDelNivel = 0;
            }
        }
    }

    void insertar(NodoArista* nuevaArista) {
        this->insertarAux(nuevaArista);
    }
};

/*void kruskal()
{
    ColaPrioridad cp(); // imp. heap
    insertarAristas(cp); // inserto todas las aristas del grafo
    List<Arista> solucion(); // guardo las aristas que serán parte de la solución
    MFset mfset(V+1); // Merge-Find Set de V+1 elementos
    int aristasAceptadas = 0;

    while(!cp.estaVacia() || aristasAceptadas < V-1)
    {
        Arista a = cp.pop(); // obtenemos la misma arista sin procesar
        if(mfset.find(a.origen) != mfset.find(a.destino)) // !formaCiclo(solucion, a)
        {
            mfset.merge(a.origen, a.destino);
            solucion.agregar(a);
            aristasAceptadas++;
        }
    }
}*/

int main()
{

    return 0;
}
