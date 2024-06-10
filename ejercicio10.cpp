#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

// verifica que la celda este dentro del tablero
bool esCoordenadaValida(int fila, int col, int tamanio){
	return fila >= 0 && fila < tamanio && col >= 0 && col < tamanio;
}

// verifica que no haya pasado por la celda
bool pasePorCelda(int fila, int col, int **tablero){
	return tablero[fila][col] > 0;
}

// es valido si la celda esta dentro del tablero y no fue visitada
bool esMovimientoValido(int fila, int col, int ** tablero, int tamanio) {
	return esCoordenadaValida(fila, col, tamanio) && !pasePorCelda(fila, col, tablero);
}

// queremos guardar el numero del paso dado
void realizarMovimiento(int fila, int col, int ** tablero) {
	tablero[fila][col] = 1;
}

// deshacemos el movimiento, ponemos en 0 la celda
void deshacerMovimiento(int fila, int col, int ** tablero) {
	tablero[fila][col] = 0;
}

// verifica si el tablero esta recorrido completamente
bool esSolucion(int ** tablero, int tamanio){
    for (int i = 0; i < tamanio; i++){
        for (int j = 0; j < tamanio; j++){
            if (tablero[i][j] != 1){
                return false;
            }
        }
    }
    return true;
}

void caballoDecision(int filaActual, int colActual, int ** tablero, int tamanio, bool & encontreSolucion){
	if (!encontreSolucion){
		if (esSolucion(tablero, tamanio)){
			encontreSolucion = true;
        }
		else{
			int movimientosFila[] = {-2, -1, 1, 2, 2, 1, -1, -2};
			int movimientosCol[] = {-1, -2, -2, -1, 1, 2, 2, 1};
			for (int opcionMovimiento = 0; opcionMovimiento < 8; opcionMovimiento++){
				int nuevaFila = filaActual + movimientosFila[opcionMovimiento];
				int nuevaCol = colActual + movimientosCol[opcionMovimiento];
				if (esMovimientoValido(nuevaFila, nuevaCol, tablero, tamanio)){
					realizarMovimiento(nuevaFila, nuevaCol, tablero);
					caballoDecision(nuevaFila, nuevaCol, tablero, tamanio, encontreSolucion);
					deshacerMovimiento(nuevaFila, nuevaCol, tablero);
				}
			}
		}
	}
}

int main()
{
    int tamanio;
    cin >> tamanio;
    int posX, posY;
    cin >> posX >> posY;

    int ** tablero = new int*[tamanio];
	for (int fila = 0; fila < tamanio; fila++) {
		tablero[fila] = new int[tamanio]();
	}
    tablero[posX][posY] = 1;

    bool encontreSolucion = false;
    caballoDecision(posX, posY, tablero, tamanio, encontreSolucion);

    if (encontreSolucion){
        cout << "SI" << endl;
    }
    else{
        cout << "NO" << endl;
    }
    return 0;
}