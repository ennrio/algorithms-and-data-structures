#pragma once
#include<iostream>
class Queue {
public:
    Queue(int capacity);
    ~Queue();
     void push(int data);
     int getLast();
     bool isEmpty();
     bool isFull();
     int getSize();
     void print();
private:
    int* queue;
    int capacity;
    int front;
    int rear;      // Индекс конца очереди
    int size;
};

