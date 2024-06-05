#include <iostream>
#include <cmath>

using namespace std;

// Función para obtener el máximo de dos números
int maximo(int x, int y) {
    return (x > y) ? x : y;
}

// Función para generar números primos usando la criba de Eratóstenes
int* esPrimoEratostenes(int n, int& cant) {
    int* numeros = new int[n + 1]();
    for (int i = 0; i <= n; ++i) {
        numeros[i] = 1;
    }
    numeros[0] = numeros[1] = 0;

    for (int i = 2; i <= sqrt(n); ++i) {
        if (numeros[i]) {
            for (int j = i * i; j <= n; j += i) {
                numeros[j] = 0;
            }
        }
    }

    cant = 0;
    for (int i = 2; i <= n; ++i) {
        if (numeros[i]) {
            ++cant;
        }
    }

    int* primos = new int[cant]();
    int index = 0;
    for (int i = 2; i <= n; ++i) {
        if (numeros[i]) {
            primos[index++] = i;
        }
    }

    delete[] numeros;
    return primos;
}

int main() {
    int filas, columnas;
    cin >> filas;
    cin >> columnas;

    // Generamos los números primos necesarios
    int cant;
    int* primos = esPrimoEratostenes(maximo(filas, columnas), cant);

    // Inicializamos la matriz con ceros
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        matriz[i] = new int[columnas]();
    }

    // Establecemos las condiciones iniciales
    matriz[0][0] = 1;
    matriz[1][0] = 0;
    matriz[0][1] = 0;

    // Llenamos la matriz
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            for (int k = 0; k < cant; ++k) {
                int primo = primos[k];
                if (i - primo >= 0) {
                    matriz[i][j] += matriz[i - primo][j];
                }
                if (j - primo >= 0) {
                    matriz[i][j] += matriz[i][j - primo];
                }
            }
        }
    }

    // Mostramos el resultado
    cout << matriz[filas - 1][columnas - 1] << endl;

    // Liberamos la memoria
    for (int i = 0; i < filas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
    delete[] primos;

    return 0;
}
