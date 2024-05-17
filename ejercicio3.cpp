#include <cassert>
#include <iostream>
#include <string>

using namespace std;

class AVL
{
private:
    int dato;
    int cant;
    AVL *izq;
    AVL *der;
    int alt;

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    int altura(AVL *raiz)
    {
        if (raiz == nullptr)
            return 0;
        return 1 + max(altura(raiz->izq), altura(raiz->der));
    }

    int obtenerBalance(AVL *raiz)
    {
        if (raiz == nullptr)
            return 0;
        return altura(raiz->izq) - altura(raiz->der);
    }

    AVL *rotacionHoraria(AVL *A)
    {
        AVL *B = A->izq;
        AVL *T2 = B->der;
        B->der = A;
        A->izq = T2;
        A->alt = altura(A);
        B->alt = altura(B);
        return B;
    }

    AVL *rotacionAntihoraria(AVL *A)
    {
        AVL *B = A->der;
        AVL *T2 = B->izq;
        B->izq = A;
        A->der = T2;
        A->alt = altura(A);
        B->alt = altura(B);
        return B;
    }

    AVL *insertarAux(AVL *raiz, int valor)
    {
        if (raiz == nullptr)
        {
            return new AVL(valor);
        }
        if (valor < raiz->dato)
        {
            raiz->izq = insertarAux(raiz->izq, valor);
        }
        else if (valor > raiz->dato)
        {
            raiz->der = insertarAux(raiz->der, valor);
        }
        else
        {
            raiz->cant++;
            return raiz;
        }

        raiz->alt = altura(raiz);
        int balance = obtenerBalance(raiz);

        // Rotaciones para mantener el árbol balanceado
        if (balance > 1 && valor < raiz->izq->dato)
        {
            return rotacionHoraria(raiz);
        }
        if (balance < -1 && valor > raiz->der->dato)
        {
            return rotacionAntihoraria(raiz);
        }
        if (balance > 1 && valor > raiz->izq->dato)
        {
            raiz->izq = rotacionAntihoraria(raiz->izq);
            return rotacionHoraria(raiz);
        }
        if (balance < -1 && valor < raiz->der->dato)
        {
            raiz->der = rotacionHoraria(raiz->der);
            return rotacionAntihoraria(raiz);
        }

        return raiz;
    }

public:
    AVL(int valor) : dato(valor), cant(1), izq(nullptr), der(nullptr), alt(1) {}

    AVL *insertar(AVL *raiz, int dato)
    {
        return insertarAux(raiz, dato);
    }

    bool buscar(AVL *raiz, int buscado)
    {
        if (raiz == nullptr)
            return false;
        if (buscado < raiz->dato)
            return buscar(raiz->izq, buscado);
        else if (buscado > raiz->dato)
            return buscar(raiz->der, buscado);
        return true;
    }

    int getCantidad(AVL *raiz, int buscado)
    {
        if (raiz == nullptr)
            return 0;
        if (buscado < raiz->dato)
            return getCantidad(raiz->izq, buscado);
        else if (buscado > raiz->dato)
            return getCantidad(raiz->der, buscado);
        return raiz->cant;
    }
};

int main()
{
    int N, M, K;
    cin >> N;
    AVL *avlN = nullptr;
    int temp;
    for (int i = 0; i < N; i++)
    {
        cin >> temp;
        if (avlN == nullptr)
            avlN = new AVL(temp);
        else
            avlN = avlN->insertar(avlN, temp);
    }
    cin >> M;
    int *listaM = new int[M];
    for (int i = 0; i < M; i++)
    {
        cin >> listaM[i];
    }
    cin >> K;
    int contador = 0;
    for (int i = 0; i < M; i++)
    {
        int complemento = K - listaM[i];
        if (avlN && avlN->buscar(avlN,complemento))
        {
            contador += avlN->getCantidad(avlN,complemento);
        }
    }
    cout << contador << endl;
    delete[] listaM;
    delete avlN;
    return 0;
}
