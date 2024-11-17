#pragma once
#include <iostream>
class Two_linked_list
{
public:
	Two_linked_list();
	void push_front(int data);
	void push_back(int data);
	void print_list();
	void insert(int data, int index);
	void pop(int index);
	void pop_front();
	int& operator[] (const int index);
	int get_size();
private:
	class Node {
	public:
		int data;
		Node* next;
		Node* prev;
		Node(int data) {
			this->data = data;
			this->next = next;
			this->prev = prev;
		};
	};
	int size;
	Node* head;
};

