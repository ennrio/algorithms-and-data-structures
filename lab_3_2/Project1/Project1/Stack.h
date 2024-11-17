#pragma once
#include<iostream>
class Stack {
public:
    Stack(int capacity);
    ~Stack();
    void push(int data);
    int pop();
    bool isEmpty();
    bool isFull();
    int size();
    void print();

private:
    int* stack;
    int capacity;
    int top;
};
