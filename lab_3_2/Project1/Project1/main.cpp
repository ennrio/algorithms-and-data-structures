#include<iostream>
#include<thread>
#include<chrono>
#include <time.h> 
#include <vector>
#include"Queue.h"
#include"Stack.h"


void ProcessorP0(int task) {
    std::cout << "Задача " << task << " поступила в процессор P0" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50 * task));
    std::cout << "Процессор P0 закончил выполнение задачи " << task << std::endl;
}

void ProcessorP1(int task) {
    std::cout << "Задача " << task << " поступила в процессор P1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * task));
    std::cout << "Процессор P1 закончил выполнение задачи " << task << std::endl;
}

using namespace std;
int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(0));
    Stack S(20);
    Queue F(20);
    vector<thread> threadsP0;
    vector<thread> threadsP1;


    int p = 0;
    cout << "Генерировать задачи" << endl << "1 - В ручном режиме" << endl << "2 - В автоматическом" << endl;
    cout << ">>>>";
    cin >> p;
    if (p == 1) {
        int x = 0;
        int i = 0;
        cout << "Сколько задач вы хотите ввести?" << endl << ">>>>";
        cin >> i;
        for (; i >= 0; --i) {
            cout << "Введите задачу>>";
            cin >> x;
            F.push(x);
            int x = F.getLast();
            threadsP0.emplace_back(ProcessorP0, x);
            S.push(x);
            threadsP1.emplace_back(ProcessorP1, S.pop());
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
        }
    }
    else {
        for (int i = 0; i < 5; i++) {
            int x = rand() % (20 - 0 + 1) + 0;
            F.push(x);
        }
        while (!F.isEmpty()) {
            int x = F.getLast();
            threadsP0.emplace_back(ProcessorP0, x);
            S.push(x);
            threadsP1.emplace_back(ProcessorP1, S.pop());
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
        }
    }

    for (auto& t : threadsP0) {
        t.join();
    }

    for (auto& t : threadsP1) {
        t.join();
    }




    return 0;
}