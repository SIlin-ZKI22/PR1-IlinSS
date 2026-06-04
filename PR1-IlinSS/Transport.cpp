#include "Transport.h"
#include <iomanip>

// Plane
Plane::Plane(int sp, int dist, const std::string& own, int rng, int pay)
    : Transport(sp, dist, own), range(rng), payload(pay) {
}

void Plane::print() const {
    std::cout << "[Самолёт] " << owner
        << " | скорость=" << speed
        << " | расстояние=" << distance
        << " | дальность=" << range
        << " | грузоподъёмность=" << payload << std::endl;
}

// Train
Train::Train(int sp, int dist, const std::string& own, int wgn)
    : Transport(sp, dist, own), wagons(wgn) {
}

void Train::print() const {
    std::cout << "[Поезд]   " << owner
        << " | скорость=" << speed
        << " | расстояние=" << distance
        << " | вагонов=" << wagons << std::endl;
}

// Truck
Truck::Truck(int sp, int dist, const std::string& own, int cap, double vol)
    : Transport(sp, dist, own), capacity(cap), volume(vol) {
}

void Truck::print() const {
    std::cout << "[Грузовик] " << owner
        << " | скорость=" << speed
        << " | расстояние=" << distance
        << " | грузоподъёмность=" << capacity
        << " | объём кузова=" << std::fixed << std::setprecision(1) << volume << std::endl;
}