#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

    int maximo(int x, int y){
        if (x > y){
            return x;
        }
        return y;
    }
    //preguntar si esta bien la logica de la funcion esPrimoEratostenes
    int* esPrimoEratostenes (int n){
        int * numeros = new int[n+1]();
        for (int i = 0; i < n+1; i++){
            numeros[i] = i;
        }
        int cant = n-1;
        for (int i = 2; i <= sqrt(n); i++){
            if (numeros[i] != -1){
                for (int j = i; j<(n/i); j++){
                    numeros[i*j] = -1;
                    cant--;
                }
            }
        }
        int* primos = new int[cant]();
        int j = 0;
        for (int i = 2; i < n+1 ; i++){
            if (numeros[i] != -1){
                primos[j] = i;
                j++;
            }
        }
        return primos;
    }

    //preguntar como resolver el ejercicio despues de obtener los primos.
    //como obtener todas las combinaciones posibles de llegar de una esquina a la otra
    //acordarse de usar long long

int main()
{
    int x;
    int y;	
    cin >> x;
    cin >> y;

    int* primos = esPrimoEratostenes(maximo(x,y));


    return 0;
}