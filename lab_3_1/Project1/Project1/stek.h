#pragma once
class stek
{
public:
	stek();
	void push_front(int data);
	int get_front();
private:
	class Node {
		int data;
		Node* next;
		Node(int data) {
			this->data = data;
			this->next = next;
		}
	};
	int size;
	Node* head;
};

