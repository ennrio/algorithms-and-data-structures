#include <iostream>
#include<ctime>

using namespace std;

void fill_array(int* arr, const int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % n + 1 - n / 2;
	}
}
void print_array(int* arr, const int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << endl;
	}
}

int change_array(int* arr, const int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] < 0) {
			arr[i] = arr[i] * -1;
		}
	}
	return sum;
}

int odd_null(int* arr, const int n) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] == 0) {
			count++;
		}
	}
	return count;
}

int main() {
	setlocale(LC_ALL, "RU");
	srand(time(0));
	int n = -1;
	cout << "������� ������ �������>>";
	while (true) {
		cin >> n;
		if (n <= 0) {
			cout << "����� ������� �� ����� ���� ������������� ��� ����� ����!!!" << endl
				<< "��������� ����>>";
		}
		else {
			break;
		}

	}
	int* arr = new int[n];
	fill_array(arr, n);
	print_array(arr, n);
	cout << endl;

	int choice;
	cout << "1 - �������� ��� ������������� �������� ��������� �� ������ �� ��������  " << endl;
	cout << "2 - ���������� ���������� ��������� � ������� ���������" << endl;
	cout << ">>>>";
	cin >> choice;

	if (choice == 1) {
		change_array(arr, n);
		print_array(arr, n);
	}
	else {
		int count;
		count = odd_null(arr, n);
		cout << "������� ��������� = " << count;
	}




	delete[]arr;
	return 0;
}