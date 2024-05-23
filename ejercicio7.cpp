#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

//aplicar minHeap
//tengo que ordenar el vector de virus e insertarlo en el minHeap
class MinheapVirus{
    private:
        int * virus;
        int largo;
        int ultimoLibre;

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
            return x < y;
        }

        void flotar(int nodo){
            if (nodo != 1){
                int posPadre = padre(nodo);
                if (comparar(virus[nodo], virus[posPadre])){
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

                if (posDer < ultimoLibre && comparar(virus[posDer], virus[posIzq])){
                    hijoMenor = posDer;
                }

                if (comparar(virus[hijoMenor], virus[nodo])){
                    intercambiar(hijoMenor, nodo);
                    hundir(hijoMenor);
                }
            }
        }

    public:
        MinheapVirus(int tamanio){
            int * virus = new int [tamanio + 1];
            largo = tamanio + 1;
            ultimoLibre = 1;
        }

        ~MinheapVirus(){
            delete[] virus;
        }

        bool esVacio(){
            return ultimoLibre == 1;
        }

        bool estaLleno(){
            return ultimoLibre == largo;
        }

        void insertar(int v) {
            assert(!estaLleno());
            virus[ultimoLibre] = v;
            flotar(ultimoLibre);
            ultimoLibre++;
        }

        int obtenerMinimo() {
            assert(!esVacio());
            return virus[1];
        }

        void eliminarTope(){
            assert(!esVacio());
            this->virus[1] = this->virus[ultimoLibre - 1];
            this->ultimoLibre--;
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
            return 0;
        }
        
    }
    cout << "true" << endl;
    // return true;
    return 0;
}