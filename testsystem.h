#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

struct Question {
    string text;
    vector<string> options;
    int correctIndex;
};

struct Test {
    string name;
    vector<Question> questions;
};

vector<Test> tests;

//Авторизация
bool authorize(bool& isAdmin) {
    string login, password;
    cout << "Введите логин: ";
    cin >> login;
    cout << "Введите пароль: ";
    cin >> password;

    if (login == "admin" && password == "admin123") {
        isAdmin = true;
        return true;
    }
    else if (login == "user" && password == "user123") {
        isAdmin = false;
        return true;
    }
    else {
        cout << "Неверный логин или пароль!\n";
        return false;
    }
}

//Добавить тест (для администратора)
void addTest() {
    Test test;
    cout << "Введите название теста: ";
    cin.ignore();
    getline(cin, test.name);

    int questionCount;
    cout << "Сколько вопросов в тесте? ";
    cin >> questionCount;

    for (int i = 0; i < questionCount; ++i) {
        Question q;
        cout << "Вопрос #" << (i + 1) << ": ";
        cin.ignore();
        getline(cin, q.text);

        int optionsCount;
        cout << "Сколько вариантов ответа? ";
        cin >> optionsCount;

        q.options.resize(optionsCount);
        for (int j = 0; j < optionsCount; ++j) {
            cout << "Вариант " << j + 1 << ": ";
            cin.ignore();
            getline(cin, q.options[j]);
        }

        cout << "Номер правильного варианта (с 1): ";
        cin >> q.correctIndex;
        q.correctIndex--; // переход к индексу с 0

        test.questions.push_back(q);
    }

    tests.push_back(test);
    cout << "Тест успешно добавлен!\n";
}

//Пройти тест (для пользователя)
void takeTest() {
    if (tests.empty()) {
        cout << "Нет доступных тестов.\n";
        return;
    }

    cout << "Доступные тесты:\n";
    for (size_t i = 0; i < tests.size(); ++i) {
        cout << i + 1 << ") " << tests[i].name << endl;
    }

    int choice;
    cout << "Выберите тест: ";
    cin >> choice;

    if (choice < 1 || choice > tests.size()) {
        cout << "Неверный выбор.\n";
        return;
    }

    const Test& test = tests[choice - 1];
    int score = 0;

    for (size_t i = 0; i < test.questions.size(); ++i) {
        const Question& q = test.questions[i];
        cout << "\n" << i + 1 << ") " << q.text << endl;
        for (size_t j = 0; j < q.options.size(); ++j) {
            cout << j + 1 << ". " << q.options[j] << endl;
        }

        int answer;
        cout << "Ваш ответ: ";
        cin >> answer;

        if (answer - 1 == q.correctIndex) {
            score++;
        }
    }

    cout << "\nВаш результат: " << score << " из " << test.questions.size() << "\n";
}

//Сохранение всех тестов в файл
void saveTestsToFile() {
    ofstream out("tests.txt");
    if (!out) {
        cerr << "Ошибка при сохранении тестов.\n";
        return;
    }

    out << tests.size() << "\n";
    for (const auto& test : tests) {
        out << test.name << "\n";
        out << test.questions.size() << "\n";
        for (const auto& q : test.questions) {
            out << q.text << "\n";
            out << q.options.size() << "\n";
            for (const auto& opt : q.options) {
                out << opt << "\n";
            }
            out << q.correctIndex << "\n";
        }
    }
    out.close();
}

// Загрузка тестов из файла
void loadTestsFromFile() {
    ifstream in("tests.txt");
    if (!in) return; // файла нет — ничего не загружаем

    size_t testCount;
    in >> testCount;
    in.ignore();

    for (size_t i = 0; i < testCount; ++i) {
        Test test;
        getline(in, test.name);

        size_t questionCount;
        in >> questionCount;
        in.ignore();

        for (size_t j = 0; j < questionCount; ++j) {
            Question q;
            getline(in, q.text);

            size_t optionCount;
            in >> optionCount;
            in.ignore();

            for (size_t k = 0; k < optionCount; ++k) {
                string opt;
                getline(in, opt);
                q.options.push_back(opt);
            }

            in >> q.correctIndex;
            in.ignore();

            test.questions.push_back(q);
        }

        tests.push_back(test);
    }
}

