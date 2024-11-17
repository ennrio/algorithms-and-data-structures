#include<iostream>
using namespace std;
void swap(int* arr, int pos1, int pos2) {
	int temp;
	temp = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = temp;
}

int partition(int* arr, int low, int high, int pivot, int& count_permutation, int& count_comparison) {
	int i = low;
	int j = low;
	while (i <= high) {
		if (arr[i] > pivot) {
			i++;
		}
		else {
			count_permutation++;
			swap(arr, i, j);
			i++;
			j++;
		}
		count_comparison += 2;
	}
	return j - 1;
}

void quickSort(int* arr, int low, int high, int& count_permutation, int& count_comparison) {
	if (low < high) {
		int pivot = arr[high];
		int pos = partition(arr, low, high, pivot, count_permutation, count_comparison);

		quickSort(arr, low, pos - 1, count_permutation, count_comparison);
		quickSort(arr, pos + 1, high, count_permutation, count_comparison);
		count_comparison++;
	}
}
int searchContent(int* arr,const int size, const int content, int& count_comparison) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == content) {
			return i;
			break;
		}
		count_comparison += 2;
	}
	cout << "Элемент не был найден, возвращено значение 0" << endl;
	return 0;
}

int searchIndex(int* arr, const int index) {
	return arr[index];
}

void insert(int*& arr, int &size, const int index, const int data, int& count_comparison) {
	int* temp = new int[++size];
	for (int i = 0; i < index; i++) {
		temp[i] = arr[i];
		count_comparison++;
	}
	temp[index] = data;
	for (int i = (index + 1); i < size; i++) {
		temp[i] = arr[i-1];
		count_comparison++;
	}
	delete[]arr;
	arr = temp;
}

void pop(int*& arr, int& size, int index,int& count_comparison) {
	int* temp = new int[--size];
	for (int i = 0; i < index; i++) {
		temp[i] = arr[i];
		count_comparison++;
	}
	for (int i = index; i < size; i++) {
		temp[i] = arr[i + 1];
		count_comparison++;
	}
	delete[]arr;
	arr = temp;
}

void print_arr(int* arr, const int size, int& count_comparison) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << "\t";
		count_comparison++;
	}
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	int size;
	int count_permutation = 0;
	int count_comparison = 0;
	cout << "Введите размер массива>>>>";
	cin >> size;
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		int data;
		cout << "введите " << i << "-ый элемент массива>>";
		cin >> data;
		arr[i] = data;
	}
	quickSort(arr, 0, size-1, count_permutation, count_comparison);
	print_arr(arr,size,count_comparison);
	while (true) {
		int p;
		cout << "1 - Поиск элемента по содержимому" << endl;
		cout << "2 - Поиск элемента по порядковой позиции" << endl;
		cout << "3 - Добавление элемента" << endl;
		cout << "4 - Удаление элемента" << endl;
		cout << "5 - Вывести кол-во сравнений и перестановок" << endl;
		cout << "6 - Вывести массив" << endl;
		cout << "Любая дргугая клавиша завершит программу" << endl;
		cout << ">>>>";
		cin >> p;
		if (p == 1) {
			int content;
			cout << "Введите инерисующую вас переменную>>>>";
			cin >> content;
			cout << searchContent(arr, size, content, count_comparison) << endl;
		}
		else if (p == 2) {
			int index;
			cout << "Введите индекс >>>>";
			cin >> index;
			cout << searchIndex(arr, index) << endl;
		}
		else if (p == 3) {
			int data;
			cout << "Введите данные >>>>";
			cin >> data;
			cout << endl;
			int index;
			cout << "Введите индекс >>>>";
			cin >> index;
			cout << endl;
			insert(arr, size, index, data, count_comparison);
		}
		else if (p == 4) {
			int index;
			cout << "Введите индекс>>>>";
			cin >> index;
			cout << endl;
			pop(arr, size, index, count_comparison);
		}
		else if (p == 5) {
			cout << "Количество сравнений - " << count_comparison << endl;
			cout << "Количество перестановок - " << count_permutation << endl;
		}
		else if (p == 6) {
			print_arr(arr, size, count_comparison);
		}		
	}
}