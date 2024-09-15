#include "Entities.h"

Order::Order(vector<Pizza> pizzas) : id(counter), pizzas(pizzas) {
    preperingTime = 0;
    for (auto& pizza : pizzas) {
        if (pizza.getPreparationTime() > preperingTime) {
            preperingTime = pizza.getPreparationTime();
        }
    }
    startTime = time(NULL);
    counter++;
}

int Order::getId() { return id; }

vector<Pizza> Order::getPizzas() {
    return pizzas;
}

bool Order::isOrderReady() { 
    return time(NULL) - startTime - preperingTime > 0; 
}

int Order::counter = 0;