#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

class MaxHeap_Piedras
{
private:
	int posTope;
	int capacidad;
	int *piedras;

	int izq(int pos)
	{
		return pos * 2;
	}

	int der(int pos)
	{
		return (pos * 2) + 1;
	}

	int padre(int pos)
	{
		return pos / 2;
	}

	void intercambiar(int pos1, int pos2)
	{
		int aux = this->piedras[pos1];
		this->piedras[pos1] = this->piedras[pos2];
		this->piedras[pos2] = aux;
	}

	void flotar(int pos)
	{
		// trato de flotar si no soy la raiz
		if (pos > 1)
		{
			int posPadre = padre(pos);
			if (funcionComparadora(this->piedras[posPadre], this->piedras[pos]) < 0)
			{
				intercambiar(posPadre, pos);
				flotar(posPadre);
			}
		}
	}

	void hundir(int pos)
	{
		int posHijoIzq = izq(pos);
		int posHijoDer = der(pos);
		// si tengo mis dos hijos
		if (posHijoIzq < posTope && posHijoDer < posTope)
		{
			int posHijoMayor = funcionComparadora(piedras[posHijoIzq], piedras[posHijoDer]) > 0 ? posHijoIzq : posHijoDer;
			if (funcionComparadora(piedras[pos], piedras[posHijoMayor]) < 0)
			{
				intercambiar(pos, posHijoMayor);
				hundir(posHijoMayor);
			}
		}
		// si tengo solo hijo izquierdo
		else if (posHijoIzq < posTope)
		{
			if (funcionComparadora(piedras[pos], piedras[posHijoIzq]) < 0)
			{
				intercambiar(pos, posHijoIzq);
				hundir(posHijoIzq);
			}
		}
	}

public:
	MaxHeap_Piedras(int unaCapacidad)
	{
		this->piedras = new int[unaCapacidad + 1]();
		this->posTope = 1;
		this->capacidad = unaCapacidad;
	}

	int funcionComparadora(int a, int b)
	{
		return a - b;
	}

	int tope()
	{
		assert(!estaVacio());
		return this->piedras[1];
	}

	void eliminarTope()
	{
		if (this->obtenerPosTope() > 1)
		{
			this->piedras[1] = this->piedras[posTope - 1];
			this->posTope--;
			hundir(1);
		}
	}

	void insertar(int e)
	{
		assert(!estaLleno());
		this->piedras[posTope] = e;
		posTope++;
		flotar(posTope - 1);
	}
	bool estaLleno()
	{
		return this->posTope > this->capacidad;
	}

	bool estaVacio()
	{
		return this->posTope == 1;
	}

	int obtenerPiedra(int pos)
	{
		if (pos < this->obtenerPosTope())
			return piedras[pos];
		return 0;
	}

	int obtenerPosTope()
	{
		return this->posTope;
	}
};

int main()
{
	int cantidad_Piedras;
	cin >> cantidad_Piedras;
	MaxHeap_Piedras *miHeap = new MaxHeap_Piedras(cantidad_Piedras);
	int peso;
	for (int i = 0; i < cantidad_Piedras; i++)
	{
		cin >> peso;
		miHeap->insertar(peso);
	}
	while (!miHeap->estaVacio())
	{
		int primera = miHeap->tope(); // Primera piedra más pesada.
		miHeap->eliminarTope();		// Elimina la primera piedra más pesada.
		if (miHeap->estaVacio())
		{
			cout << primera << endl; // Si no quedan más piedras, imprime la última y sale.
			break;
		}
		int segunda = miHeap->tope(); // Segunda piedra más pesada.
		miHeap->eliminarTope();		 // Elimina la segunda piedra más pesada.
		if (miHeap->estaVacio())
		{
			cout << abs(primera - segunda)<< endl;
			break;
		}
		else if (primera != segunda)
		{
			int resultado_enfrentamiento = abs(primera - segunda);
			miHeap->insertar(resultado_enfrentamiento); // Inserta el resultado de la resta si no son iguales.
		}
	}
	delete miHeap;
	return 0;
}
