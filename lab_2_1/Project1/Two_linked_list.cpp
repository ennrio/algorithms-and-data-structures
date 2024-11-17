#include "Two_linked_list.h"
Two_linked_list::Two_linked_list()
{
	head = nullptr;
	size = 1;
}
void Two_linked_list::push_front(int data) {
	Node* newNode = new Node(data);
	if (head == nullptr) {
		head = newNode;
		return;
	}
	newNode->next = head;
	head->prev = newNode;
	head = newNode;
	size++;
}
void Two_linked_list::push_back(int data) {
	Node* newNode = new Node(data);

	if (head == nullptr) {
		head = newNode;
		return;
	}

	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->prev = temp;
	size++;
}
void Two_linked_list::print_list() {
	Node* temp = head;
	while (temp != nullptr) {
		std::cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
	std::cout << "������ = " << this->size << std::endl;
}

void Two_linked_list::insert(int data, int index)
{
	if (index < 0) {
		std::cout << "������� �� ����� ���� ������ 1!!!" << std::endl;
		return;
	}
	if (index == 0) {
		push_front(data);
		return;
	}

	Node* newNode = new Node(data);
	Node* temp = head;

	for (int i = 0; temp != nullptr && i < index; i++) {
		temp = temp->next;
	}

	if (temp == nullptr) {
		std::cout << "������� ��������� �� �������!!!, �������� ��� �������� � �����" << std::endl;
		push_back(data);
		return;
	}

	newNode->next = temp->next;
	newNode->prev = temp;
	if (temp->next != nullptr) {
		temp->next->prev = newNode;
	}
	temp->next = newNode;
	size++;
}

void Two_linked_list::pop_front()
{
	if (head == nullptr) {
		std::cout << "������ ����" << std::endl;
		return;
	}

	Node* temp = head;
	head = head->next;
	if (head != nullptr) {
		head->prev = nullptr;
	}
	delete temp;
}

int& Two_linked_list::operator[](const int index)
{
	Node* temp = head;
	for (int i = 0; i < (index); i++) {
		temp = temp->next;
	}
	return temp->data;
	// TODO: �������� ����� �������� return
}

int Two_linked_list::get_size()
{
	return this->size;
}

void Two_linked_list::pop(int index)
{
	if (head == nullptr) {
		std::cout << "�������� ����������, �� ������� ���������� ���������" << std::endl;
		return;
	}
	if (index == 0) {
		pop_front();
		return;
	}

	Node* temp = head;
	if (index > size - 1) {
		std::cout << "������ ��������� ���������� ���������, ��� ����� ��������� �������" << std::endl;
		index = size - 1;
	}

	for (int i = 0; temp != nullptr && i < index; i++) {
		temp = temp->next;
	}

	if (temp->next != nullptr) {
		temp->next->prev = temp->prev;
	}
	if (temp->prev != nullptr) {
		temp->prev->next = temp->next;
	}
	delete temp;
}



