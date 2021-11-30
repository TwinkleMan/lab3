#include <iostream>

#include "menu.h"

void MenuEngine(menuItem *p_item, unsigned int item_quantity) {

    unsigned int selection;

    do {
        for (unsigned int i = 0; i < item_quantity; i++) {
            std::cout << p_item[i].number << ") " << p_item[i].text << "\n";
        }
        printf("\nВыберите пункт меню используя кнопки %d-%d\n", 0, item_quantity-1);
        std::cin >> selection;

        if (selection != 0) {
            for (unsigned int i = 0; i < item_quantity; i++) {
                if (selection == p_item[i].number) {
                    (p_item[i].p_processing_function)();
                    break;
                }
            }
            if (selection > item_quantity) {
                std::cout << "Несуществующий пункт!\n";
            }
        }
    } while (selection != 0);
}

void SettingsEngine(settingsMenuItem *p_item, unsigned int item_quantity, DWORD *resultAttributes) {
    char selection[MAX_PATH];
    std::string log[MAX_PATH];
    int flag = 0;
    int count = 0;

    do {
        system("CLS");
        for (unsigned int i = 0; i < item_quantity; i++) {
            std::cout << p_item[i].text << "\n";
        }
        std::cout << "\nlog: ";
        for (int i = 0; i < count;i++) {
            std::cout << log[i] << ", ";
        }
        printf("\nSelect option:\n");
        std::cin >> selection;

        if (strcmp(selection,"exit") != 0) {
            for (unsigned int i = 0; i < item_quantity; i++) {
                if (strcmp(selection,p_item[i].text) == 0) {
                    if (strcmp(selection,"normal") == 0) {
                        *resultAttributes = p_item[i].setting;
                    } else {
                        *resultAttributes = *resultAttributes | p_item[i].setting;
                    }
                    log[count++] = selection;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                std::cout << "Invalid option!\n";
            }
            flag = 0;
        }
    } while (strcmp(selection,"exit") != 0);
}
