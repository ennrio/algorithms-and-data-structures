#include<iostream>
#include<thread>
#include<chrono>
#include <time.h> 
#include <vector>


class Stack {
public:
    Stack(int capacity) {
        if (capacity <= 0) {
            std::cout << "������� ������ ���� ������ 0!!! ������� ������� 100" << std::endl;
            capacity = 100;
        }
        this->capacity = capacity;  
        this->top = -1;            
        this->stack = new int[capacity];  
    }

    ~Stack() {
        delete[] stack; 
    }

    void push(int data) {
        if (isFull()) {
            //throw std::overflow_error("������������ �����: �� ������� ������� ������ ����.");
            std::cout << "���� ����������, ������� �� ��� ��������!!!" << std::endl;
            return;
        }
        stack[++top] = data; 
    }

    int pop() {
        if (isEmpty()) {
            std::cout << "���� ����, �� �������� ������� �������!!!" << std::endl;
            return 0;
        }
        return stack[top--];  
    }

    bool isEmpty() const {
        return top == -1; 
    }

    bool isFull() const {
        return top == capacity - 1;  
    }

    int size() const {
        return top + 1; 
    }
    void print() {
        for (int i = top; i >= 0; i--) {
            std::cout << stack[i] << "\t";
        }
        std::cout << std::endl;
    }

private:
    int* stack;      
    int capacity;   
    int top;       
};


class Queue {
public:
    Queue(int capacity) {
        if (capacity <= 0) {
            std::cout << "������ ������� �� ����� ���� <=0!!! ����������� �������� 100" << std::endl;
            capacity = 100;
        }
        this->capacity = capacity;
        this->queue = new int[capacity];
        this->front = 0;
        this->rear = -1;
        this->size = 0;
    }

    ~Queue() {
        delete[] queue;
    }

    void push(int data) {
        if (isFull()) {
            std::cout << "������� �����������, ������� �� ��� ��������" << std::endl;
            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear] = data;
        ++size;
    }

    int getLast() {
        if (isEmpty()) {
            std::cout << "������� ������, ���������� �������� 0";
            return 0;
        }
        int data = queue[front];
        front = (front + 1) % capacity; 
        --size;
        return data;
    }


    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == capacity;
    }

    int getSize() const {
        return size;
    }
    
    void print() {
        for (int i = 0; i < size; ++i) {
            std::cout << queue[(front + i) % capacity] << "\t";
        }
        std::cout << std::endl;
    }

private:
    int* queue;
    int capacity;
    int front; 
    int rear;      // ������ ����� �������
    int size;
};

void ProcessorP0(int task) {
    std::cout << "������ " << task << " ��������� � ��������� P0" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50*task));
    std::cout << "��������� P0 �������� ���������� ������ " << task << std::endl;
}

void ProcessorP1(int task) {
    std::cout << "������ " << task << " ��������� � ��������� P1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * task));
    std::cout << "��������� P1 �������� ���������� ������ " << task << std::endl;
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
    cout << "������������ ������" << endl << "1 - � ������ ������" << endl << "2 - � ��������������" << endl;
    cout << ">>>>";
    cin >> p;
    if (p == 1) {
        int x = 0;
        int i = 0;
        cout << "������� ����� �� ������ ������?" << endl << ">>>>";
        cin >> i;
        for (; i >= 0; --i) {
            cout << "������� ������>>";
            cin >> x;
            F.push(x);
            int x = F.getLast();
            threadsP0.emplace_back(ProcessorP0, x);
            S.push(x);
            threadsP1.emplace_back(ProcessorP1, S.pop());
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
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