#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

//aplicar minHeap
//tengo que ordenar el vector de virus e insertarlo en el minHeap

int main()
{
    int potencia;
    cin >> potencia;
    int N;
    cin >> N;
    int *virus = new int[N];
    for (int i = 0; i < N; i++)
    {
        int v;
        cin >> v;
        virus[i] = v;
        if (virus[i] <= potencia)
        {
            potencia += virus[i];
        }
        else
        {
            return false;
        }
    }
    return true;
}