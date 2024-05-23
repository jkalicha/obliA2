#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

class MinheapVirus{
    private:
        int * virus;
        int largo;
        int primerlibre;

        int izq(int nodo){
            return nodo * 2;
        }

        int der(int nodo){
            return nodo * 2 + 1;
        }

        int padre(int nodo){
            return nodo / 2;
        }

        void intercambiar(int x, int y){
            int temp = virus[x];
            virus[x] = virus[y];
            virus[y] = temp;
        }
        
        bool comparar(int x, int y){
            return virus[x] < virus[y];
        }

        void flotar(int nodo){
            if (nodo != 1){
                int posPadre = padre(nodo);
                if (comparar(nodo, posPadre)){
                    intercambiar(nodo, posPadre);
                    flotar(posPadre);
                }
            }
        }

        void hundir(int nodo){
            if (izq(nodo) < primerlibre){ // Si tiene al menos un hijo
                int posIzq = izq(nodo);
                int posDer = der(nodo);
                int hijoMenor = posIzq;

                if (posDer < primerlibre && comparar(posDer, posIzq)){
                    hijoMenor = posDer;
                }

                if (comparar(hijoMenor, nodo)){
                    intercambiar(hijoMenor, nodo);
                    hundir(hijoMenor);
                }
            }
        }

    public:
        MinheapVirus(int tamanio){
            virus = new int [tamanio + 1];
            largo = tamanio + 1;
            primerlibre = 1;
        }

        ~MinheapVirus(){
            delete[] virus;
        }

        bool esVacio(){
            return primerlibre == 1;
        }

        bool estaLleno(){
            return primerlibre == largo;
        }

        void insertar(int v) {
            assert(!estaLleno());
            virus[primerlibre] = v;
            flotar(primerlibre);
            primerlibre++;
        }

        int obtenerMinimo() {
            assert(!esVacio());
            return virus[1];
        }

        void eliminarTope(){
            assert(!esVacio());
            this->virus[1] = this->virus[primerlibre - 1];
            this->primerlibre--;
            hundir(1);
        }
};

int main(){
    int potencia;
    cin >> potencia;
    int N;
    cin >> N;
    MinheapVirus * virusMinHeap = new MinheapVirus(N);
    for (int i = 0; i < N; i++){
        int v;
        cin >> v;
        if (v <= potencia){
            potencia += v;
        }
        else {
            virusMinHeap->insertar(v);
        }
    }
    while (!virusMinHeap->esVacio()){
        if(virusMinHeap->obtenerMinimo() <= potencia){
            potencia += virusMinHeap->obtenerMinimo();
            virusMinHeap->eliminarTope();
        }else{
            cout << "false" << endl;
            // return false;
            delete virusMinHeap;
            return 0;
        }
    }
    cout << "true" << endl;
    // return true;
    delete virusMinHeap;
    return 0;
}