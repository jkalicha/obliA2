#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Pedido
{
    string elem;
    int id;
    bool entregado;
};

struct NodoLista
{
    Pedido ped;
    NodoLista *sig;

    NodoLista(Pedido pedido, NodoLista *siguiente = NULL)
        : ped(pedido), sig(siguiente) {}
};

class TablaHashAbierta
{
private:
    NodoLista **tabla;
    int tamanio;
    int cantPedidos;

    int fnHash(int key, int tam)
    {
        return key % tam;
    }

    void rehash()
    {
        int nuevoTamanio = this->tamanio * 2;
        NodoLista **nuevaTabla = new NodoLista*[nuevoTamanio]();
        
        for (int i = 0; i < this->tamanio; ++i)
        {
            NodoLista *nodo = this->tabla[i];
            while (nodo)
            {
                NodoLista *siguiente = nodo->sig;
                int nuevaPos = fnHash(nodo->ped.id, nuevoTamanio);
                nodo->sig = nuevaTabla[nuevaPos];
                nuevaTabla[nuevaPos] = nodo;
                nodo = siguiente;
            }
        }

        delete[] this->tabla;
        this->tabla = nuevaTabla;
        this->tamanio = nuevoTamanio;
    }

    float factorDeCarga()
    {
        return (float)this->cantPedidos / this->tamanio;
    }

public:
    TablaHashAbierta(int cant)
    {
        this->tamanio = cant;
        this->cantPedidos = 0;
        this->tabla = new NodoLista*[this->tamanio]();
    }

    void insertarEnTablaHash(Pedido *pedido)
    {
        int pos = abs(this->fnHash(pedido->id, this->tamanio));
        Pedido* ped = buscarEnLista(pos,pedido->id);
        if (ped)
        {
            ped->elem = pedido->elem;
            ped->entregado = false;
        }
        else
        {
            NodoLista *aux = new NodoLista(*pedido, tabla[pos]);
            tabla[pos] = aux;
            this->cantPedidos++;
        }
        if (this->factorDeCarga() > 0.7)
            this->rehash();
    }

    Pedido* buscarEnLista(int index, int id)
    {
        NodoLista *nodo = this->tabla[index];
        while (nodo)
        {
            if (nodo->ped.id == id)
            {
                return &nodo->ped;
            }
            nodo = nodo->sig;
        }
        return NULL;
    }

    void actualizarPedido(int id)
    {
        int index = fnHash(id, this->tamanio);
        Pedido *pedido = buscarEnLista(index, id);
        if (pedido)
        {
            pedido->entregado = true;
        }
    }

    void consultarPedido(int id)
    {
        int index = fnHash(id, this->tamanio);
        Pedido *pedido = buscarEnLista(index, id);
        if (pedido)
        {
            if (pedido->entregado)
            {
                cout << "Entregado" << endl;
            }
            else
            {
                cout << pedido->elem << endl;
            }
        }
        else
        {
            cout << "Pedido no encontrado" << endl;
        }
    }
};

int main()
{
    int cantOp;
    cin >> cantOp;
    TablaHashAbierta *mitabla = new TablaHashAbierta(cantOp);
    while (cantOp > 0)
    {
        string accion;
        cin >> accion;
        if (accion == "A")
        {
            int id;
            cin >> id;
            string elementos;
            cin.ignore();
            getline(cin, elementos);
            Pedido* ped = new Pedido();
            ped->elem = elementos;
            ped->id = id;
            ped->entregado = false;
            mitabla->insertarEnTablaHash(ped);
        }
        else if (accion == "E")
        {
            int id;
            cin >> id;
            mitabla->actualizarPedido(id);
        }
        else if (accion == "Q")
        {
            int id;
            cin >> id;
            mitabla->consultarPedido(id);
        }
        cantOp--;
    }
    return 0;
}
