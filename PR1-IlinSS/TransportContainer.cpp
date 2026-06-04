#include "TransportContainer.h"
#include "Constants.h"        // ← ЭТО БЫЛО ПРОПУЩЕНО!
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace Constants;

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

    // Собираем оставшуюся часть как значение
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

        // Проверка по скорости (используем константы из Constants.h)
        if (field == SPEED_RU || field == SPEED_EN) {
            try {
                int val = std::stoi(valueStr);
                int current = (*it)->getSpeed();
                if (op == OP_GT && current > val) shouldDelete = true;
                else if (op == OP_LT && current < val) shouldDelete = true;
                else if (op == OP_EQ || op == OP_EQ2) shouldDelete = (current == val);
                else if (op == OP_GE) shouldDelete = (current >= val);
                else if (op == OP_LE) shouldDelete = (current <= val);
            }
            catch (const std::exception& e) {
                std::cerr << "Ошибка парсинга числа: " << valueStr << std::endl;
                ++it;
                continue;
            }
        }
        // Проверка по расстоянию
        else if (field == DISTANCE_RU || field == DISTANCE_EN) {
            try {
                int val = std::stoi(valueStr);
                int current = (*it)->getDistance();
                if (op == OP_GT && current > val) shouldDelete = true;
                else if (op == OP_LT && current < val) shouldDelete = true;
                else if (op == OP_EQ || op == OP_EQ2) shouldDelete = (current == val);
                else if (op == OP_GE) shouldDelete = (current >= val);
                else if (op == OP_LE) shouldDelete = (current <= val);
            }
            catch (const std::exception& e) {
                std::cerr << "Ошибка парсинга числа: " << valueStr << std::endl;
                ++it;
                continue;
            }
        }
        // Проверка по владельцу
        else if (field == OWNER_RU || field == OWNER_EN) {
            std::string val = valueStr;
            std::string current = (*it)->getOwner();
            if (op == OP_EQ || op == OP_EQ2) {
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