#include "Entities.h"
#include <algorithm>

User::User(string name, string phone_number) : name(name), phone_number(phone_number) {}

string User::getName() { return name; }

void User::placeOrder(Pizzaria& pizzeria, vector<int> idPizzas) {
    orderIds.push_back(pizzeria.receiveOrder(idPizzas));
}

void User::pickUpAllReadyOrders(Pizzaria& pizzeria) {
    vector<int> reseivedOrders;
    vector<Pizza> pizzas = pizzeria.giveOrders(orderIds, reseivedOrders);
    inventory.insert(inventory.end(), pizzas.begin(), pizzas.end());

    sort(reseivedOrders.begin(), reseivedOrders.end());
    // Удаляем элементы из orderIds, которые также присутствуют в reseivedOrders
    orderIds.erase(remove_if(orderIds.begin(), orderIds.end(),
        [&reseivedOrders](int x) {
            return std::binary_search(reseivedOrders.begin(), reseivedOrders.end(), x);
        }),
        orderIds.end());
}

void User::printOrders() {
    cout << name << "'s orders:\n";
    for (int i = 0; i < orderIds.size(); i++) {
        cout << orderIds[i] << "; ";
    }
}

void User::printInventory() {
    cout << name << "'s inventory:\n";
    for (int i = 0; i < inventory.size(); i++) {
        cout << inventory[i] << '\n';
    }
}