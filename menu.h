#ifndef OS_LAB1_MENU_H
#define OS_LAB1_MENU_H

#include <fileapi.h>
typedef void (*menu_processing_function_ptr)();

struct menuItem {
    unsigned int number;
    const char *text;
    menu_processing_function_ptr p_processing_function;
};

struct settingsMenuItem {
    const char *text;
    DWORD setting;
};

void MenuEngine(menuItem *p_item, unsigned int item_quantity);
void SettingsEngine(settingsMenuItem *p_item, unsigned int item_quantity, DWORD *resultAttributes);

#endif //OS_LAB1_MENU_H
