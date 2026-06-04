#include "TransportContainer.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

TransportContainer::~TransportContainer() {
    for (auto* v : vehicles) {
        delete v;
    }
}

void TransportContainer::add(Transport* vehicle) {
    vehicles.push_back(vehicle);
}

void TransportContainer::printAll() const {
    if (vehicles.empty()) {
        std::cout << "(контейнер пуст)" << std::endl;
        return;
    }
    for (const auto* v : vehicles) {
        v->print();
    }
}

void TransportContainer::remove(const std::string& condition) {
    if (condition.empty() || vehicles.empty()) return;

    std::cout << "Условие: '" << condition << "'" << std::endl;

    // Парсим условие: "поле оператор значение"
    std::istringstream iss(condition);
    std::string field, op, valueStr;
    iss >> field >> op;

    // Собираем оставшуюся часть как значение (для случая "владелец = Ivanov")
    std::getline(iss, valueStr);

    // Убираем пробелы в начале значения
    size_t start = valueStr.find_first_not_of(" \t");
    if (start != std::string::npos) {
        valueStr = valueStr.substr(start);
    }

    // Убираем возможные кавычки в значении
    if (!valueStr.empty() && valueStr.front() == '"' && valueStr.back() == '"') {
        valueStr = valueStr.substr(1, valueStr.length() - 2);
    }

    std::cout << " field='" << field << "', op='" << op << "', value='" << valueStr << "'" << std::endl;

    int removedCount = 0;
    auto it = vehicles.begin();
    while (it != vehicles.end()) {
        bool shouldDelete = false;

        // Проверка по скорости
        if (field == "скорость" || field == "speed") {
            int val = std::stoi(valueStr);
            int current = (*it)->getSpeed();
            if (op == ">" && current > val) shouldDelete = true;
            else if (op == "<" && current < val) shouldDelete = true;
            else if (op == "=" || op == "==") shouldDelete = (current == val);
            else if (op == ">=") shouldDelete = (current >= val);
            else if (op == "<=") shouldDelete = (current <= val);
        }
        // Проверка по расстоянию
        else if (field == "расстояние" || field == "distance") {
            int val = std::stoi(valueStr);
            int current = (*it)->getDistance();
            if (op == ">" && current > val) shouldDelete = true;
            else if (op == "<" && current < val) shouldDelete = true;
            else if (op == "=" || op == "==") shouldDelete = (current == val);
            else if (op == ">=") shouldDelete = (current >= val);
            else if (op == "<=") shouldDelete = (current <= val);
        }
        // Проверка по владельцу
        else if (field == "владелец" || field == "owner") {
            std::string val = valueStr;
            std::string current = (*it)->getOwner();
            if (op == "=" || op == "==") {
                shouldDelete = (current == val);
            }
        }

        if (shouldDelete) {
            std::cout << "Удаляем: ";
            (*it)->print();
            delete* it;
            it = vehicles.erase(it);
            removedCount++;
        }
        else {
            ++it;
        }
    }

    std::cout << "Удалено объектов: " << removedCount << std::endl;
}