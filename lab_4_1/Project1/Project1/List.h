#pragma once
#include<string>
#include<iostream>

using namespace std;

template<typename T, typename D>
class List {
public:
	List();
	~List();

	void push_back(T data, D key);
	void print();
	void pop_front();
	T search(D key);
	void remove(D key);
	int getSize();

private:

	//template<typename T>
	class Node {
	public:
		Node* pNext;
		T data;
		D key;
		Node(T data, D key, Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
			this->key = key;
		}
	};

	int Size;
	Node* head;
};


template<typename T, typename D>
List<T, D>::List() {
	Size = 0;
	head = nullptr;
}

template<typename T, typename D>
List<T, D>::~List() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->pNext;
		delete current;
		current = next;
	}
}

template<typename T, typename D>
void List<T, D>::print()
{
	cout << endl;
	Node* current = this->head;
	while (current != nullptr) {
		cout << current->data << "  " << current->key << endl;
		current = current->pNext;
	}
}

template<typename T, typename D>
T List<T, D>::search(D key)
{
	Node* current = this->head;
	while (current != nullptr) {
		if (current->key == key) {
			return current->data;
		}
		current = current->pNext;
	}
}

template<typename T, typename D>
void List<T, D>::push_back(T data, D key)
{
	if (head == nullptr) {
		head = new Node(data, key);
	}
	else {
		Node* current = this->head;

		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new Node(data, key);
	}
	Size++;
}
template<typename T, typename D>
void List<T, D>::pop_front()
{
	Node* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}
template<typename T, typename D>
int List<T, D>::getSize() {
	return Size;
}

template<typename T, typename D>
void List<T, D>::remove(D key) {
	Node* previous = this->head;
	Node* current = previous->pNext;
	Node* first = previous;
	while (previous != nullptr) {
		if (first->key == key) {
			pop_front();
			Size--;
			break;
		}
		else
			if (current->key == key) {
				Node* DeleteNode = previous->pNext;
				previous->pNext = DeleteNode->pNext;
				delete DeleteNode;
				Size--;
				break;
			}
		previous = previous->pNext;
		current = current->pNext;
	}

}

