#include "Queue.h"

Queue::Queue(int capacity)
{
    if (capacity <= 0) {
        std::cout << "Размер очереди не может быть <=0!!! Установлено значение 100" << std::endl;
        capacity = 100;
    }
    this->capacity = capacity;
    this->queue = new int[capacity];
    this->front = 0;
    this->rear = -1;
    this->size = 0;
}

Queue::~Queue()
{
    delete[] queue;
}

void Queue::push(int data)
{
    if (isFull()) {
        std::cout << "очередь переполнена, элемент не был добавлен" << std::endl;
        return;
    }
    rear = (rear + 1) % capacity;
    queue[rear] = data;
    ++size;
}

int Queue::getLast()
{
    if (isEmpty()) {
        std::cout << "Очередь пустая, возвращено значение 0";
        return 0;
    }
    int data = queue[front];
    front = (front + 1) % capacity;
    --size;
    return data;
}

bool Queue::isEmpty()
{
    return size == 0;
}

bool Queue::isFull()
{
    return size == capacity;
}

int Queue::getSize()
{
    return size;
}

void Queue::print()
{
    for (int i = 0; i < size; ++i) {
        std::cout << queue[(front + i) % capacity] << "\t";
    }
    std::cout << std::endl;
}
