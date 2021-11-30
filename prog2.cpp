#include "prog2.h"
#include <omp.h>
#include <windows.h>
#include <iostream>

#define N 100000000
#define blockSize 9305160

using namespace std;

void mainSecond() {
    int numOfThreads;
    long double pi = 0.0;
    long double x_i;
    double invN = 1.0 / N;

    system("cls");
    cout << "Введите количество потоков: ";
    cin >> numOfThreads;

    DWORD startTime = GetTickCount();

    #pragma omp parallel for schedule(dynamic,blockSize) default(none) private(x_i) shared(invN) num_threads(numOfThreads) reduction (+ : pi)
    for (long long i = 0; i < N; i++)
    {
        x_i = (i + 0.5) * invN;
        pi += 4 / (1 + x_i * x_i);
    }

    pi *= invN;
    DWORD endTime = GetTickCount();

    cout << "Время вычислений: " << endTime - startTime << " мс" << '\n';
    cout.precision(10);
    cout << "Результат вычислений: " << pi << '\n' << "\n0) Выход\n";
    char a;
    cin >> a;

    system("cls");
}
