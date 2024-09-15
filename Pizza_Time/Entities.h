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
    // ����� �������������
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
    //����� ������� ������
    time_t preperingTime;
    //����� ������ ������
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

    // ���������� ������ - ����������� �������
    bool processOrders();
    // ������� �����
    int receiveOrder(vector<int> idPizzas);
    // ������ �����
    vector<Pizza> giveOrder(int idOrder, bool& isOrderReceived);
    // ������ ��� ������� ������
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

    // ������� �����
    void placeOrder(Pizzaria& pizzeria, vector<int> idPizzas);
    // ������� ��� ������� ������
    void pickUpAllReadyOrders(Pizzaria& pizzeria);
    void printOrders();
    void printInventory();
};