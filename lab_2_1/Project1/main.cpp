#include <iostream>
#include "Two_linked_list.h"

int main() {
	setlocale(LC_ALL, "RUS");
	Two_linked_list list;
	int n;
	std::cout << "¬ведите длину последовательности >>" << std::endl;
	std::cin >> n;
	int num;
	std::cout << "¬ведите числа:" << std::endl;
	for (int i = 0; i < n; i++) {
		std::cin >> num;
		list.push_back(num);
	}
	int c;
	std::cout << "¬ведите с>>" << std::endl;
	std::cin >> c;
	std::cout << "ѕерва€ :)" << std::endl;
	int i = 0;
	while (c != list[i]) {
		i++;
	}
	for (int j = (i-1); j >= 0; --j) {
		std::cout << list[j] << " ";
	}
	std::cout << std::endl;
	std::cout << "¬тора€ :)" << std::endl;
	for (int j = ++i; j < list.get_size(); j++) {
		std::cout << list[j] << " ";
	}
	Two_linked_list list2;
	list2.push_front(345);
	list2.push_front(345);
	list2.push_front(345);
	list2.push_front(345);
	list2.push_front(345);
	list2.pop_front();
	list2.print_list();




	return 0;
}