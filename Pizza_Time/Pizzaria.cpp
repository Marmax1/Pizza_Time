#include "Entities.h"

Pizzaria::Pizzaria(string name) : name(name) {}

Pizzaria::Pizzaria(string name, vector<Pizza> pizzas) : name(name), allPizzas(pizzas) {}

bool Pizzaria::processOrders() {
    bool isSomeOrderReady = false;
    // ��������� ���������� ������� � ������� orders
    for (auto it = preperingOrders.begin(); it != preperingOrders.end(); ) {
        if (it->isOrderReady()) {
            isSomeOrderReady = true;
            // ���������� ������� ����� � ������ ������� �������
            readyOrders.push_back(move(*it));
            // ������� ������� ����� �� ������� orders
            it = preperingOrders.erase(it);
        }
        else {
            // ���� ����� �� �����, ��������� � ���������� ������
            ++it;
        }
    }
    return isSomeOrderReady;
}

int Pizzaria::receiveOrder(vector<int> idPizzas) {
    vector <Pizza> pizzas;
    for (const auto& id : idPizzas) {
        if (id < 0 || id >= allPizzas.size()) {
            throw "id " + to_string(id) + " is out of range"; // ����������
        }
        pizzas.push_back(Pizza(allPizzas[id]));
    }
    preperingOrders.emplace_back(pizzas);
    return preperingOrders.back().getId();
}

vector<Pizza> Pizzaria::giveOrder(int idOrder, bool& isOrderReceived) {
    for (auto it = readyOrders.begin(); it != readyOrders.end();) {
        auto order = *it;
        // ����� ����� ������ �����
        if (idOrder == order.getId()) {
            isOrderReceived = true;
            auto tmp = order.getPizzas();
            readyOrders.erase(it);
            return tmp;
        }
        ++it;
    }
    return {};
}

vector<Pizza> Pizzaria::giveOrders(vector<int> idOrders, vector<int>& idReceivedOrders) {
    vector<Pizza> pizzas;
    for (auto it = readyOrders.begin(); it != readyOrders.end();) {
        auto order = *it;
        // ����� ����� ������ �����
        if (find(idOrders.begin(), idOrders.end(), order.getId()) != idOrders.end()) {
            idReceivedOrders.push_back(order.getId());
            auto tmp = order.getPizzas();
            // ������� ����� � ����� pizzas
            pizzas.insert(pizzas.end(), tmp.begin(), tmp.end());
            it = readyOrders.erase(it);
        }
        else {
            ++it;
        }
    }
    return pizzas;
}

void Pizzaria::printMenu() {
    cout << "Menu:\n";
    for (int i = 0; i < allPizzas.size(); i++) {
        cout << "Id: " << i << "; " << allPizzas[i] << '\n';
    }
}

void Pizzaria::printIdReadyOrders() {
    cout << "ReadyOrders:\n";
    for (int i = 0; i < readyOrders.size(); i++) {
        cout << readyOrders[i].getId() << "; ";
    }
}