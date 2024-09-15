#include "Entities.h"
#include <conio.h>
#include <sstream>
#include <thread>
#include <chrono>
#include <mutex>

mutex inputMutex;
mutex outputMutex;

void printDescription(shared_ptr<Pizzaria> curPizziria, shared_ptr<User> curUser) {
    system("cls");
    curPizziria->printMenu();
    cout << '\n';
    curUser->printOrders();
    cout << '\n';
    curUser->printInventory();
    cout << '\n';
    curPizziria->printIdReadyOrders();
    cout << '\n';

    cout << "Select the command:\n";
    cout << "1. Place an order\n";
    cout << "2. Pick up all your ready orders\n";
    cout << "3. Reload\n";
    cout << "0. Exit\n";
}

vector<int> splitStr(string str) {
    std::vector<int> nums;
    std::istringstream iss(str);
    int num;
    while (iss >> num){
        nums.push_back(num);
    }
    return nums;
}

int main() {

    Pizzaria pizzeria("Pizza Hut", { Pizza("Chicken", 50, 600, 5), Pizza("Peperone", 30, 500, 2), Pizza("Carbonara", 40, 550, 10) });

    shared_ptr<Pizzaria> curPizziria = make_shared<Pizzaria>(pizzeria);

    User user("John", "89005553535");

    shared_ptr<User> curUser = make_shared<User>(user);

    thread orderProcessor([curPizziria, curUser]() {
        while (true) {
            {
                unique_lock<mutex> lock(inputMutex);
                if (curPizziria->processOrders()) {
                    printDescription(curPizziria, curUser);
                }
            }
            this_thread::sleep_for(chrono::seconds(3));
        }
        });

    int input = 1;

    while (input != 0) {
        unique_lock<mutex> lock(outputMutex);
        curPizziria->processOrders();
        printDescription(curPizziria, curUser);
        lock.unlock();
        
        string inpStr;
        vector<int> numbers;
        try {
            (cin >> input).get();
            if (input == 1) {
                std::unique_lock<std::mutex> lock(inputMutex);
                cout << "Enter the pizza id separated by a space:\n";
                getline(cin, inpStr);
                numbers = splitStr(inpStr);
                curUser->placeOrder(*curPizziria, numbers);
            }
            else if (input == 2) {
                curUser->pickUpAllReadyOrders(*curPizziria);
            }
        }
        catch (string errorMessage) {
            cout << errorMessage << '\n';
            this_thread::sleep_for(chrono::seconds(2));
        }
    }

    orderProcessor.join();

    return 0;
}