#include "Entities.h"

Pizza::Pizza(string name) : name(name), radius(25), weight(400) {}

Pizza::Pizza(string name, int radius, int weight, time_t preparationTime) : name(name), radius(radius), weight(weight), preparationTime(preparationTime){}

time_t Pizza::getPreparationTime() { return preparationTime; };

ostream& operator<< (ostream& out, const Pizza& pizza) {
    out << "Name: " << pizza.name << "; Rad: " << pizza.radius << " cm;" << "W: " << pizza.weight << " g;";
    return out;
}