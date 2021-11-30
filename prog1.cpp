#include <iostream>
#include <windows.h>

#define N 100000000
#define blockSize 9305160

using namespace std;

const double invN = 1.0 / N;
int numOfThreads;

typedef struct {
    volatile long *count;
    double pi;
} threadStruct;

DWORD WINAPI countIter(LPVOID lpData) {

    threadStruct* temp = (threadStruct*)lpData;

    bool flag = true;
    int start = 0;
    int end = 0;
    double result = 0;
    double iter = 0;
    double x_i = 0;
    long blockNum = 0;

    while (flag)
    {
        blockNum = InterlockedIncrement(temp->count) - 1; //Инкрементирование волатильной переменной и переменной функции
        start = blockSize * blockNum;                      //Начало текущего блока
        end   = blockSize * (blockNum + 1);                //Конец текущего блока

        //Вычисление числа Пи

        if (start < N)
        {
            iter = 0;
            x_i = 0;
            for (int i = start; (i < N) && (i < end); ++i)
            {
                x_i = (i + 0.5) * invN;
                iter += 4 / (1 + x_i * x_i);
            }

            result += iter;
        }
        else
        {
            flag = !flag;   //Флаг, определяющий конец вычислений
        }
    }

    temp->pi = result;

    return 0;

}

void mainFirst() {

    system("cls");
    cout << "Введите количество потоков: ";
    cin >> numOfThreads;

    threadStruct** structs = new threadStruct * [numOfThreads];   //Массив структур
    HANDLE* threads = new HANDLE[numOfThreads];      //Массив дескрипторов потоков
    DWORD* threadsID = new DWORD[numOfThreads];       //Массив ID потоков

    long *counter = new long;
    *counter = 0;


    for (int i = 0; i < numOfThreads; ++i)
    {
        structs[i] = new threadStruct{counter, 0 };

        threads[i] = CreateThread(NULL, 0, countIter, structs[i],
                                  CREATE_SUSPENDED, &threadsID[i]);
    }

    DWORD startTime = GetTickCount();
    for (int i = 0; i < numOfThreads; ++i)
    {
        ResumeThread(threads[i]);
    }
    WaitForMultipleObjects(numOfThreads, threads, TRUE, INFINITE);    //Ожидание изменения состояния потоков
    double res = 0;
    for (int i = 0; i < numOfThreads; ++i)
    {
        res += structs[i]->pi;
    }
    res = res * invN;
    DWORD endTime = GetTickCount();

    cout << "Время вычислений: " << endTime - startTime << " мс" << '\n';
    cout.precision(10);
    cout << "Результат вычислений: " << res << '\n' << "\n0) Выход\n";
    char a;
    cin >> a;

    for (int i = 0; i < numOfThreads; ++i)
    {
        CloseHandle(threads[i]);
    }
    delete[] structs;
    system("cls");
}