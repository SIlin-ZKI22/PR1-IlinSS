#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TransportContainer.h"
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// Функция для удаления пробелов в начале и конце строки
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

// Обработка команды ADD
void processAdd(istringstream& iss, TransportContainer& container) {
    string type;
    iss >> type;

    int speed, distance;
    string owner;
    iss >> speed >> distance >> owner;

    if (type == "Plane" || type == "Самолёт" || type == "самолет") {
        int range, payload;
        iss >> range >> payload;
        container.add(new Plane(speed, distance, owner, range, payload));
        cout << "Добавлен самолёт владельца " << owner << endl;
    }
    else if (type == "Train" || type == "Поезд" || type == "поезд") {
        int wagons;
        iss >> wagons;
        container.add(new Train(speed, distance, owner, wagons));
        cout << "Добавлен поезд владельца " << owner << endl;
    }
    else if (type == "Truck" || type == "Грузовик" || type == "грузовик") {
        int capacity;
        double volume;
        iss >> capacity >> volume;
        container.add(new Truck(speed, distance, owner, capacity, volume));
        cout << "Добавлен грузовик владельца " << owner << endl;
    }
    else {
        cout << "Ошибка: неизвестный тип транспорта '" << type << "'" << endl;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    setlocale(LC_ALL, "ru_RU.UTF-8");
    TransportContainer container;

    string filename = "commands.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        cerr << "Создайте файл commands.txt в папке с программой" << endl;
        system("pause");
        return 1;
    }

    string line;
    int lineNum = 0;

    cout << "=== Обработка команд из файла " << filename << " ===" << endl << endl;

    while (getline(file, line)) {
        lineNum++;
        line = trim(line);
        if (line.empty()) continue;

        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "ADD") {
            processAdd(iss, container);
        }
        else if (command == "REM") {
            string condition;
            getline(iss, condition);
            condition = trim(condition);
            cout << "Удаление по условию: " << condition << endl;
            container.remove(condition);
        }
        else if (command == "PRINT") {
            cout << "\n=== Содержимое контейнера ===" << endl;
            container.printAll();
            cout << "================================" << endl << endl;
        }
        else {
            cout << " Строка " << lineNum << ": неизвестная команда '" << command << "'" << endl;
        }
    }

    file.close();
    cout << "\n=== Обработка завершена ===" << endl;
    system("pause");
    return 0;
}