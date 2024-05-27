#include <iostream>
using namespace std;

int encontrarUnico(int arr[], int low, int high) {
    if (low > high) {
        return -1;
    }

    if (low == high) {
        return arr[low];
    }

    int mid = low + (high - low) / 2;

    // Para que la división y el cálculo de posiciones sea correcto, ajustamos mid a la izquierda más cercana donde mid % 3 == 0
    if (mid % 3 == 1) {
        mid--;
    } else if (mid % 3 == 2) {
        mid -= 2;
    }

    // Si mid es el inicio de un triplete
    if (mid + 2 <= high && arr[mid] == arr[mid + 1] && arr[mid] == arr[mid + 2]) {
        // El número único está a la derecha de este triplete
        return encontrarUnico(arr, mid + 3, high);
    } else {
        // El número único está a la izquierda de este triplete (incluyendo mid)
        return encontrarUnico(arr, low, mid);
    }
}

int main() {
    int N;
    cin >> N;

    int* arr = new int[N];
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    int result = encontrarUnico(arr, 0, N - 1);
    cout << result << endl;

    delete[] arr;
    return 0;
}
