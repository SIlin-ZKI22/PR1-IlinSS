#include "Transport.h"
#include <iomanip>

// Transport
Transport::Transport(int sp, int dist, const std::string& own)
    : speed(sp), distance(dist), owner(own) {
}

// Plane
Plane::Plane(int sp, int dist, const std::string& own, int rng, int pay)
    : Transport(sp, dist, own), range(rng), payload(pay) {
}

void Plane::print() const {
    std::cout << "Самолёт | Владелец: " << owner
        << " | Скорость: " << speed
        << " | Расстояние: " << distance
        << " | Дальность: " << range
        << " | Грузоподъёмность: " << payload << std::endl;
}

// Train
Train::Train(int sp, int dist, const std::string& own, int wgn)
    : Transport(sp, dist, own), wagons(wgn) {
}

void Train::print() const {
    std::cout << "Поезд   | Владелец: " << owner
        << " | Скорость: " << speed
        << " | Расстояние: " << distance
        << " | Вагонов: " << wagons << std::endl;
}

// Truck
Truck::Truck(int sp, int dist, const std::string& own, int cap, double vol)
    : Transport(sp, dist, own), capacity(cap), volume(vol) {
}

void Truck::print() const {
    std::cout << "Грузовик| Владелец: " << owner
        << " | Скорость: " << speed
        << " | Расстояние: " << distance
        << " | Грузоподъёмность: " << capacity
        << " | Объём кузова: " << std::fixed << std::setprecision(1) << volume << std::endl;
}