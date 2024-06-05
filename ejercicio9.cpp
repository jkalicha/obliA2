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
    //encontramos los primos
    int* primosFila = esPrimoEratostenes(x);
    int* primosCol = esPrimoEratostenes(y);
    //inicializamos la matriz
    int ** mat = new int*[y];
    for (int i=0; i<y; i++){
        mat[i] = new int[x];
    }
    int actual = 0;
    //dibujamos la matriz
    for (int i = 0; i<x; i++){
        for (int j=0; j<y; j++){
            if (j == 0 && i == 0){
                mat[i][j] = 1;
            }
            if (i-primosFila[actual]>=0){
                mat[i][j] += mat[i-primosFila[actual]]; 
            }
            actual++;

        }
    }

    return 0;
}