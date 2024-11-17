#include "Stack.h"

Stack::Stack(int capacity)
{
    if (capacity <= 0) {
        std::cout << "Емкость должна быть больше 0!!! Текущая емкость 100" << std::endl;
        capacity = 100;
    }
    this->capacity = capacity;
    this->top = -1;
    this->stack = new int[capacity];
}

Stack::~Stack()
{
    delete[] stack;
}

void Stack::push(int data)
{
    if (isFull()) {
        //throw std::overflow_error("Переполнение стека: не удается создать полный стек.");
        std::cout << "Стек переполнен, элемент не был добавлен!!!" << std::endl;
        return;
    }
    stack[++top] = data;
}
int Stack::pop()
{
    if (isEmpty()) {
        std::cout << "Стек пуст, не удадлось извлечь элемент!!!" << std::endl;
        return 0;
    }
    return stack[top--];
}

bool Stack::isEmpty()
{
    return top == -1;
}

bool Stack::isFull()
{
    return top == capacity - 1;
}

int Stack::size()
{
    return top + 1;
}

void Stack::print()
{
    for (int i = top; i >= 0; i--) {
        std::cout << stack[i] << "\t";
    }
    std::cout << std::endl;
}
