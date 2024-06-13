#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Pedido{
    string elementos;
    bool entregado;
    int key;

    Pedido() : entregado(false) {}
};

class tablaPed{
    private:
        Pedido **array;
        int tamanio;
        int cantPedidos;

        int fnHash(int clave, int tamanio){
            return clave % tamanio;
        }

        int obtenerPos(int clave, int tamanio){
            int i = 1;
            int pos = fnHash(clave, tamanio);
            while (this->array[pos] != NULL && i <= tamanio){
                pos = fnHash(pos + i ^ 32, tamanio);
                i++;
            }
            return pos;
        }

        int buscarPedido(int clave){
            int i = 1;
            int pos = fnHash(clave, this->tamanio);
            while (i <= this->tamanio && (this->array[pos] == nullptr || this->array[pos]->key != clave)){  
                pos = fnHash(pos + i ^ 32, this->tamanio);
                i++;
            }
            if (this->array[pos] == nullptr || this->array[pos]->key != clave){
                return -1;
            }
            return pos;
        }

        float factorDeCarga(){
            return (float)this->cantPedidos / this->tamanio;
        }

        void actualizarPedido(int clave, string elementos){
            int pedidoAnterior = buscarPedido(clave);
            if (pedidoAnterior != -1)
                this->array[pedidoAnterior]->elementos = elementos;
        }

        bool esPrimo(int num){
            if (num <= 1){
                return false;
            }
            for (int i = 2; i * i <= num; ++i){
                if (num % i == 0){
                    return false;
                }
            }
            return true;
        }

        int siguientePrimo(int N){
            int siguiente = N + 1;
            while (true){
                if (esPrimo(siguiente)){
                    return siguiente;
                }
                siguiente++;
            }
        }

        void rehash(){
            //int nuevo_tamanio = siguientePrimo(tamanio);
            int nuevo_tamanio = tamanio*2;
            Pedido **nuevo_array = new Pedido *[nuevo_tamanio]();
            for (int i = 0; i < tamanio; ++i){
                if (array[i] != NULL){
                    int pos = obtenerPos(array[i]->key, nuevo_tamanio);
                    nuevo_array[pos] = array[i];
                }
            }
            delete[] array;
            this->array = nuevo_array;
            this->tamanio = nuevo_tamanio;
        }

        void destruir(){
            for (int i = 0; i < this->tamanio; ++i){
                if (this->array[i] != nullptr){
                    delete array[i];
                    this->array[i] = nullptr;
                }
            }
            delete[] array;
        }

    public:
        tablaPed(int tamanioInicial){
            this->tamanio = this->siguientePrimo(tamanioInicial);
            this->cantPedidos = 0;
            this->array = new Pedido *[this->tamanio]();
        }

        ~tablaPed(){
            destruir();
        }

        void agregarPedido(int id, string elementos){
            int pos = buscarPedido(id);
            if (pos != -1){ // Si el pedido ya existe
                actualizarPedido(id, elementos);
            }
            else{                                        
                // Si no existe, agregamos un nuevo pedido
                pos = obtenerPos(id, this->tamanio); // Recalcular posición para un nuevo pedido
                Pedido *pedido = new Pedido();
                pedido->elementos = elementos;
                pedido->key = id;
                this->array[pos] = pedido;
                this->cantPedidos++;
                if (factorDeCarga() > 0.75)
                    rehash();
            }
        }

        void marcarEntregado(int ID){
            int pos = buscarPedido(ID);
            if (pos != -1 && this->array[pos]->key == ID){
                this->array[pos]->entregado = true;
            }
        }

        void consultarPedido(int ID){
            int pos = buscarPedido(ID);
            if (pos == -1){
                cout << "Pedido no encontrado" << endl;
            }
            else{
                Pedido *pedido = this->array[pos];
                if (pedido->entregado)
                {
                    cout << "Entregado" << endl;
                }
                else
                {
                    cout << pedido->elementos << endl;
                }
            }
        }
};

int main(){
    int cantOp;
    cin >> cantOp;
    tablaPed *mitabla = new tablaPed(cantOp);
    while (cantOp > 0) {
        string accion;
        cin >> accion;
        if (accion == "A"){
            int id;
            cin >> id;
            string elementos;
            getline(cin, elementos);
            elementos.erase(0, 1);
            mitabla->agregarPedido(id, elementos);
        }
        else if (accion == "E"){
            int Id;
            cin >> Id;
            mitabla->marcarEntregado(Id);
        }
        else if (accion == "Q"){
            int Id;
            cin >> Id;
            mitabla->consultarPedido(Id);
        }
        cantOp--;
    }
    return 0;
}