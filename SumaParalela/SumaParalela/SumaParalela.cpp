#include <iostream>
#include <omp.h>
#include <iomanip>

using namespace std;

const int ARRAY_SIZE = 1000;

void inicializarArreglo(int arr[], int size, int minVal, int maxVal) {
    for (int i = 0; i < size; i++) {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    }
}

void imprimirArreglo(const char* nombre, int arr[]) {
    int inicio1 = 0;
    int fin1 = 9;

    for (int i = inicio1; i <= fin1 && i < ARRAY_SIZE; i++) {
        cout << setw(5) << arr[i] << " ";
    }
    cout << " ... ";

    int inicio2 = ARRAY_SIZE - 10;
    int fin2 = ARRAY_SIZE - 1;
    for (int i = inicio2; i <= fin2 && i < ARRAY_SIZE; i++) {
        cout << setw(5) << arr[i] << " ";
    }
    cout << endl;
}

void sumaParalela(int A[], int B[], int R[], int size) {
#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        R[i] = A[i] + B[i];
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int* A = new int[ARRAY_SIZE];
    int* B = new int[ARRAY_SIZE];
    int* R_paralelo = new int[ARRAY_SIZE];

    inicializarArreglo(A, ARRAY_SIZE, 1, 100);
    inicializarArreglo(B, ARRAY_SIZE, 1, 100);
    
    cout << "Array generado" << endl;
    cout << "Tamano de arreglos: " << ARRAY_SIZE << endl;
    imprimirArreglo("A", A);
    imprimirArreglo("B", B);
    
    cout << "Procesadores disponibles: " << omp_get_num_procs() << endl;

    sumaParalela(A, B, R_paralelo, ARRAY_SIZE);

    cout << "Resultados de suma:" << endl;
    imprimirArreglo("A", A);
    imprimirArreglo("B", B);
    imprimirArreglo("R", R_paralelo);
}