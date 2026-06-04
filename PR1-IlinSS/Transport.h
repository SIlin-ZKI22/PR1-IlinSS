#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <string>
#include <stdexcept>

class Transport {
protected:
    int speed;
    int distance;
    std::string owner;

public:
    Transport(int sp, int dist, const std::string& own)
        : speed(sp), distance(dist), owner(own)
    {
        if (sp <= 0) {
            throw std::invalid_argument("Скорость должна быть положительной");
        }
        if (dist < 0) {
            throw std::invalid_argument("Расстояние не может быть отрицательным");
        }
        if (own.empty()) {
            throw std::invalid_argument("Имя владельца не может быть пустым");
        }
    }

    virtual ~Transport() = default;  // виртуальный деструктор

    virtual void print() const = 0;

    int getSpeed() const { return speed; }
    int getDistance() const { return distance; }
    std::string getOwner() const { return owner; }
};

class Plane : public Transport {
private:
    int range;
    int payload;
public:
    Plane(int sp, int dist, const std::string& own, int rng, int pay);
    void print() const override;
};

// Train
class Train : public Transport {
private:
    int wagons;
public:
    Train(int sp, int dist, const std::string& own, int wgn);
    void print() const override;
};

// Truck
class Truck : public Transport {
private:
    int capacity;
    double volume;
public:
    Truck(int sp, int dist, const std::string& own, int cap, double vol);
    void print() const override;
};

#endif