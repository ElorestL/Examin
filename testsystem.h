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

//�����������
bool authorize(bool& isAdmin) {
    string login, password;
    cout << "������� �����: ";
    cin >> login;
    cout << "������� ������: ";
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
        cout << "�������� ����� ��� ������!\n";
        return false;
    }
}

//�������� ���� (��� ��������������)
void addTest() {
    Test test;
    cout << "������� �������� �����: ";
    cin.ignore();
    getline(cin, test.name);

    int questionCount;
    cout << "������� �������� � �����? ";
    cin >> questionCount;

    for (int i = 0; i < questionCount; ++i) {
        Question q;
        cout << "������ #" << (i + 1) << ": ";
        cin.ignore();
        getline(cin, q.text);

        int optionsCount;
        cout << "������� ��������� ������? ";
        cin >> optionsCount;

        q.options.resize(optionsCount);
        for (int j = 0; j < optionsCount; ++j) {
            cout << "������� " << j + 1 << ": ";
            cin.ignore();
            getline(cin, q.options[j]);
        }

        cout << "����� ����������� �������� (� 1): ";
        cin >> q.correctIndex;
        q.correctIndex--; // ������� � ������� � 0

        test.questions.push_back(q);
    }

    tests.push_back(test);
    cout << "���� ������� ��������!\n";
}

//������ ���� (��� ������������)
void takeTest() {
    if (tests.empty()) {
        cout << "��� ��������� ������.\n";
        return;
    }

    cout << "��������� �����:\n";
    for (size_t i = 0; i < tests.size(); ++i) {
        cout << i + 1 << ") " << tests[i].name << endl;
    }

    int choice;
    cout << "�������� ����: ";
    cin >> choice;

    if (choice < 1 || choice > tests.size()) {
        cout << "�������� �����.\n";
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
        cout << "��� �����: ";
        cin >> answer;

        if (answer - 1 == q.correctIndex) {
            score++;
        }
    }

    cout << "\n��� ���������: " << score << " �� " << test.questions.size() << "\n";
}

//���������� ���� ������ � ����
void saveTestsToFile() {
    ofstream out("tests.txt");
    if (!out) {
        cerr << "������ ��� ���������� ������.\n";
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

// �������� ������ �� �����
void loadTestsFromFile() {
    ifstream in("tests.txt");
    if (!in) return; // ����� ��� � ������ �� ���������

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

