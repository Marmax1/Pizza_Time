#pragma once
#include <algorithm>
#include <ctime>
#include <vector>
#include <iostream>
#include <string>
using namespace std;


class Pizza
{
private:
    string name;
    int radius;
    int weight;
    // врем€ приготовлени€
    time_t preparationTime;
public:
    Pizza(string name);
    Pizza(string name, int radius, int weight, time_t preparationTime);

    time_t getPreparationTime();

    friend ostream& operator<<(ostream& out, const Pizza& pizza);
};


class Order {
private:
    int id;
    vector<Pizza> pizzas;
    //врем€ готовки заказа
    time_t preperingTime;
    //врем€ начала заказа
    time_t startTime;
    static int counter;
public:
    Order(vector<Pizza> pizzas);
    int getId();
    vector<Pizza> getPizzas();
    bool isOrderReady();
};


class Pizzaria
{
private:
    string name;
    vector<Order> preperingOrders;
    vector<Order> readyOrders;
    vector<Pizza> allPizzas;
public:
    Pizzaria(string name);
    Pizzaria(string name, vector<Pizza> pizzas);

    // обработать заказы - переместить готовые
    bool processOrders();
    // прин€ть заказ
    int receiveOrder(vector<int> idPizzas);
    // отдать заказ
    vector<Pizza> giveOrder(int idOrder, bool& isOrderReceived);
    // отдать все готовые заказы
    vector<Pizza> giveOrders(vector<int> idOrders, vector<int>& idReceivedOrders);
    void printMenu();
    void printIdReadyOrders();
};


class User {
private:
    string name;
    string phone_number;
    vector<int> orderIds;
    vector <Pizza> inventory;
public:
    User(string name, string phone_number);

    string getName();

    // —делать заказ
    void placeOrder(Pizzaria& pizzeria, vector<int> idPizzas);
    // «абрать все готовые заказы
    void pickUpAllReadyOrders(Pizzaria& pizzeria);
    void printOrders();
    void printInventory();
};