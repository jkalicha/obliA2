#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

// es un problema trivial cuando hay menos de 3 elementos
bool esSolucionTrivial(int n){
	return n <= 2;
}

int solucionTrivial(int *vector)
{
	return vector[0];
}

int * dividir(int * vector, int inicio, int fin){
	int tamanioProblema = (fin - inicio) + 1;
	int * problema = new int[tamanioProblema];
	for (int i = 0; i < tamanioProblema; i++)
	{
		problema[i] = vector[inicio + i];
	}
	return problema;
}

// combinar es una funcion que toma dos soluciones y devuelve una
// se fija si se repite la solucion en ambos lados, si se repite y es la unica en ambas, la devuelve.
// si se repite y no es la unica, la solucion es la que no se repite.
// si solo encuentra una solucion en ambos lados, la devuelve.
int combinar(int*a, int*b) {
	if (a[0] == b[0]){ //encontro una solucion en ambos lados
        if (a[1] != -1) return a[1]; // Encontro dos soluciones en a, y la primera no es.
        if (b[1] != -1) return b[1]; 
        else return a[0];
    }
    if (a[0] == b[1]){ //encontro una solucion en ambos lados
        return b[0]; //encontro dos soluciones en b
    }
    if (a[1] == b[0]){
        return a[0];
    }
    if (a[0] == -1){
        return b[0];
    }
    if (b[0] == -1){
        return a[0];
    }

}

int DivideAndConquer(int * vector, int n){
	if (esSolucionTrivial(n))	return solucionTrivial(vector);

	int inicio = 0;
	int fin = n - 1;
	int medio =  fin / 2;

	int *problemaIzq = dividir(vector, inicio, medio);
	int tamIzq = (medio - inicio) + 1;
	int *problemaDer = dividir(vector, medio + 1, fin);
	int tamDer = fin - (medio + 1) + 1;

	int solucionIzquierda = DivideAndConquer(problemaIzq, tamIzq);
	int solucionDerecha = DivideAndConquer(problemaDer, tamDer);

	return combinar(solucionIzquierda, solucionDerecha);	
}

int main()
{
    int cant;
    cin >> cant;
    int * numeros = new int[cant];

    return 0;
}