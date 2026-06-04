#include "FileCommandReader.h"
#include "Transport.h"
#include "TransportContainer.h"
#include "Constants.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace Constants;

FileCommandReader::FileCommandReader(const string& fname) : filename(fname) {}

void FileCommandReader::processAdd(istringstream& iss, TransportContainer& container) {
    string type;
    iss >> type;

    int speed, distance;
    string owner;
    iss >> speed >> distance >> owner;

    try {
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
    catch (const exception& e) {
        cerr << "Ошибка при добавлении: " << e.what() << endl;
    }
}

void FileCommandReader::processCommand(const string& line, TransportContainer& container) {
    istringstream iss(line);
    string command;
    iss >> command;

    if (command == "ADD") {
        processAdd(iss, container);
    }
    else if (command == "REM") {
        string condition;
        getline(iss, condition);
        size_t start = condition.find_first_not_of(" \t");
        if (start != string::npos) {
            condition = condition.substr(start);
        }
        cout << "Удаление по условию: " << condition << endl;
        container.remove(condition);
    }
    else if (command == "PRINT") {
        cout << "\n=== Содержимое контейнера ===" << endl;
        container.printAll();
        cout << "================================" << endl << endl;
    }
    else {
        cout << "Неизвестная команда: " << command << endl;
    }
}

void FileCommandReader::readAndExecute(TransportContainer& container) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    string line;
    int lineNum = 0;
    cout << "=== Обработка команд из файла " << filename << " ===" << endl << endl;

    while (getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        // Удаляем пробелы в начале и конце
        size_t first = line.find_first_not_of(" \t\n\r");
        if (first == string::npos) continue;
        size_t last = line.find_last_not_of(" \t\n\r");
        line = line.substr(first, last - first + 1);

        processCommand(line, container);
    }

    file.close();
    cout << "\n=== Обработка завершена ===" << endl;
}