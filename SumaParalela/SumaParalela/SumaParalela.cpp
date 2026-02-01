#include <iostream>
#include <omp.h>
#include <iomanip>
#include <ctime>
#include <cstdlib>

const int ARRAY_SIZE = 1000;

void inicializarArreglo(int arr[], int size, int minVal, int maxVal) {
    for (int i = 0; i < size; i++) {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    }
}

void imprimirArreglo(const char* nombre, int arr[]) {
    int inicio1 = 0;
    int fin1 = 9;

    std::cout << std::setw(5) << nombre << ":";
    for (int i = inicio1; i <= fin1 && i < ARRAY_SIZE; i++) {
        std::cout << std::setw(5) << arr[i] << " ";
    }
    std::cout << " ... ";

    int inicio2 = ARRAY_SIZE - 10;
    int fin2 = ARRAY_SIZE - 1;
    for (int i = inicio2; i <= fin2 && i < ARRAY_SIZE; i++) {
        std::cout << std::setw(5) << arr[i] << " ";
    }
    std::cout << std::endl;
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
    
    std::cout << "Array generado" << std::endl;
    std::cout << "Tamano de arreglos: " << ARRAY_SIZE << std::endl;
    imprimirArreglo("A", A);
    imprimirArreglo("B", B);
    
    std::cout << "Procesadores disponibles: " << omp_get_num_procs() << std::endl;

    sumaParalela(A, B, R_paralelo, ARRAY_SIZE);

    std::cout << "Resultados de suma:" << std::endl;
    imprimirArreglo("A", A);
    imprimirArreglo("B", B);
    imprimirArreglo("R", R_paralelo);

    delete[] A;
    delete[] B;
    delete[] R_paralelo;
}