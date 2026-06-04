#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <string>

// Базовый абстрактный класс
class Transport {
protected:
    int speed;          // скорость
    int distance;       // расстояние
    std::string owner;  // имя владельца

public:
    Transport(int sp, int dist, const std::string& own);
    virtual ~Transport() = default;

    // Чисто виртуальный метод (делает класс абстрактным)
    virtual void print() const = 0;

    // Геттеры
    int getSpeed() const { return speed; }
    int getDistance() const { return distance; }
    std::string getOwner() const { return owner; }
};

// Самолёт
class Plane : public Transport {
private:
    int range;      // дальность полёта
    int payload;    // грузоподъёмность

public:
    Plane(int sp, int dist, const std::string& own, int rng, int pay);
    void print() const override;
};

// Поезд
class Train : public Transport {
private:
    int wagons;     // количество вагонов

public:
    Train(int sp, int dist, const std::string& own, int wgn);
    void print() const override;
};

// Грузовик
class Truck : public Transport {
private:
    int capacity;   // грузоподъёмность
    double volume;  // объём кузова

public:
    Truck(int sp, int dist, const std::string& own, int cap, double vol);
    void print() const override;
};

#endif