#include <iostream>
#include <windows.h>
#include "menu.h"
#include "prog1.h"
#include "prog2.h"


menuItem mainMenu[] {
        {1,"���������� ����� �� (������� 1)",mainFirst},
        {2,"���������� ����� �� � �������������� ��������� OpenMP (������� 2)",mainSecond},
        {0,"�����"}
};
static const unsigned int mainMenuSize = sizeof(mainMenu) / sizeof(mainMenu[0]);


int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    system("CLS");
    MenuEngine(&mainMenu[0], mainMenuSize);

    return 0;
}
