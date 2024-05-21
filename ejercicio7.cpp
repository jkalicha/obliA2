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
            //completar
        }
        
        bool comparar(int * x, int * y){
            //completar
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

        void insertarAux(int virus){
            //completar
        }

    public:
        MinheapVirus(int tamanio){
            int * virus = new int *[tamanio + 1];
            largo = tamanio;
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

        void insertar(int virus){
            //completar
        }

        int obtenerMinimo(){
            //completar
        }

        void eliminarTope(){
            //completar
        }
};

int main(){
    int potencia;
    cin >> potencia;
    int N;
    cin >> N;
    MinheapVirus * virusMinHeap = new MinheapVirus[N];
    for (int i = 0; i < N; i++){
        int v;
        cin >> v;
        virusMinHeap->insertar(v);
    }
    while (!virusMinHeap->esVacio()){
        if(virusMinHeap->obtenerMinimo() <= potencia){
            potencia += virusMinHeap->obtenerMinimo();
            virusMinHeap->eliminarTope();
        }else{
            return false;
        }
        
    }
    return true;
}