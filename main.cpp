#include <iostream>
#include <windows.h>
#include "testsystem.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    loadTestsFromFile(); 

    bool isAdmin;
    while (!authorize(isAdmin)) {}

    if (isAdmin) {
        while (true) {
            std::cout << "\n--- Меню Администратора ---\n";
            std::cout << "1. Добавить тест\n";
            std::cout << "2. Выход\n";
            std::cout << "Ваш выбор: ";
            int choice;
            std::cin >> choice;

            if (choice == 1) addTest();
            else if (choice == 2) break;
            else std::cout << "Неверный выбор.\n";
        }
    }
    else {
        while (true) {
            std::cout << "\n--- Меню Пользователя ---\n";
            std::cout << "1. Пройти тест\n";
            std::cout << "2. Выход\n";
            std::cout << "Ваш выбор: ";
            int choice;
            std::cin >> choice;

            if (choice == 1) takeTest();
            else if (choice == 2) break;
            else std::cout << "Неверный выбор.\n";
        }
    }

    saveTestsToFile(); 

    std::cout << "До свидания!\n";
    return 0;
}
