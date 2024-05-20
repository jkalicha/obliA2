#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

class AVL {
private:
    int dato;
    AVL *izq;
    AVL *der;
    int alt;

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int altura(AVL *raiz) {
        if (raiz == NULL) return 0;
        return raiz->alt;
    }

    int obtenerBalance(AVL *raiz) {
        if (raiz == NULL) return 0;
        return altura(raiz->izq) - altura(raiz->der);
    }

    AVL *rotacionHoraria(AVL *A) {
        AVL *B = A->izq;
        AVL *T2 = B->der;
        B->der = A;
        A->izq = T2;
        A->alt = 1 + max(altura(A->izq), altura(A->der));
        B->alt = 1 + max(altura(B->izq), altura(B->der));
        return B;
    }

    AVL *rotacionAntihoraria(AVL *B) {
        AVL *A = B->der;
        AVL *T2 = A->izq;
        A->izq = B;
        B->der = T2;
        B->alt = 1 + max(altura(B->izq), altura(B->der));
        A->alt = 1 + max(altura(A->izq), altura(A->der));
        return A;
    }

    AVL* insertarAux(AVL *raiz, int e) {
        if (raiz == NULL) {
            return new AVL(e);
        }
        if (e < raiz->dato) {
            raiz->izq = insertarAux(raiz->izq, e);
        } else if (e > raiz->dato) {
            raiz->der = insertarAux(raiz->der, e);
        } else {
            return raiz;
        }
        raiz->alt = 1 + max(altura(raiz->izq), altura(raiz->der));
        int balance = obtenerBalance(raiz);
        if (balance > 1 && e < raiz->izq->dato) {
            return rotacionHoraria(raiz);
        }
        if (balance < -1 && e > raiz->der->dato) {
            return rotacionAntihoraria(raiz);
        }
        if (balance > 1 && e > raiz->izq->dato) {
            raiz->izq = rotacionAntihoraria(raiz->izq);
            return rotacionHoraria(raiz);
        }
        if (balance < -1 && e < raiz->der->dato) {
            raiz->der = rotacionHoraria(raiz->der);
            return rotacionAntihoraria(raiz);
        }
        return raiz;
    }

public:
    AVL(int e) {
        this->dato = e;
        this->izq = NULL;
        this->der = NULL;
        this->alt = 1;
    }

    AVL* insertar(AVL *raiz, int dato) {
        return insertarAux(raiz, dato);
    }

    bool buscar(AVL *raiz, int buscado) {
        if (raiz == NULL) {
            return false;
        }
        if (buscado < raiz->dato) {
            return buscar(raiz->izq, buscado);
        } if (buscado > raiz->dato) {
            return buscar(raiz->der, buscado);
        } else {
            return true;
        }
    }
};

int main() {
    int N;
    cin >> N;
    int* listaN = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> listaN[i];
    }
    int M;
    cin >> M;
    int temp;
    cin >> temp;
    AVL *avlM = new AVL(temp);
    for (int i = 0; i < M - 1; i++) {
        cin >> temp;
        avlM = avlM->insertar(avlM, temp);
    }
    int K;
    cin >> K;
    int contador = 0;
    for (int i = 0; i < N; i++) {
        int buscador = (K - listaN[i]);
        if (buscador < 0) {
            continue;
        } else {
            if (avlM->buscar(avlM, buscador)) {
                contador++;
            }
        }
    }
    cout << contador << endl;
    delete[] listaN;
    return contador;
}
